#include "global.hpp"

void canvas_draw(sf::RenderWindow& artBoard)
{
	artBoard.clear(bg_col);

	if (!last_cleared)
		for (auto i = 0; i < (int)vertices.size() - undo_count; i++)
		{
			artBoard.draw(vertices[i]);
		}
}

void mouseToggle(sf::Event& evnt)
{
	if (evnt.type == sf::Event::MouseButtonPressed)
	{
		if (undo_count > 0)
		{
			while (undo_count)
			{
				vertices.pop_back();
				--lines_number;
				--undo_count;
			}
		}

		if (evnt.mouseButton.button == sf::Mouse::Left)
		{
			undo_count = 0;
			if (last_cleared)
			{
				vertices.clear();
				lines_number = -1;
				last_cleared = false;
			}

			if (penSelected || brushSelected || eraserSelected)
			{
				vertices.push_back(sf::VertexArray(sf::TriangleStrip));
				lines_number++;
			}

			mousePressedDown = true;
		}
	}
	if (evnt.type == sf::Event::MouseButtonReleased)
	{
		if (evnt.mouseButton.button == sf::Mouse::Left)
		{
			mousePressedDown = false;
			last_Mouse_pos.x = 0;
			last_Mouse_pos.y = 0;
		}
	}
}

void brushConnect(sf::Vector2i newPos, sf::Vector2i lastPos, float radius)
{
	float curr_slope, mult;

	if (newPos.y != lastPos.y)
	{
		curr_slope = -(float)(newPos.x - lastPos.x) / (newPos.y - lastPos.y);
		mult = sqrt((radius * radius) / (curr_slope * curr_slope + 1));

		vertices[lines_number].append(sf::Vertex(getCoordinates({ newPos.x - mult, newPos.y - curr_slope * mult }), curr_col));
		vertices[lines_number].append(sf::Vertex(getCoordinates({ newPos.x + mult, newPos.y + curr_slope * mult }), curr_col));
	}

	else
	{
		curr_slope = 1; // m = 1/0
		vertices[lines_number].append(sf::Vertex(getCoordinates({ newPos.x + radius, newPos.y - radius }), curr_col));
		vertices[lines_number].append(sf::Vertex(getCoordinates({ newPos.x + radius, newPos.y + radius }), curr_col));
	}
}

sf::Vector2f getCoordinates(sf::Vector2f oldCord)
{
	sf::Vector2f newCord;
	if (zoomSelected)
	{
		newCord.x = (oldCord.x / 3) + zoomCordX - artBoardWidth / 6;
		newCord.y = (oldCord.y / 3) + zoomCordY - artBoardHeight / 6;
	}
	else
	{
		newCord = oldCord;
	}
	return newCord;
}