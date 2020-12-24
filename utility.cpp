#include "global.hpp"

void canvas_draw(sf::RenderWindow& artBoard)
{
	artBoard.clear(bg_col);
	for (auto i = 0; i < (int)vertices.size(); i++)
	{
		artBoard.draw(vertices[i]);
	}
}

void mouseToggle(sf::Event& evnt)
{
	if (evnt.type == sf::Event::MouseButtonPressed)
	{
		if (evnt.mouseButton.button == sf::Mouse::Left)
		{
			mousePressedDown = true;
		}
	}
	if (evnt.type == sf::Event::MouseButtonReleased)
	{
		if (evnt.mouseButton.button == sf::Mouse::Left)
		{
			lines_number++;
			vertices.push_back(sf::VertexArray(sf::TriangleStrip));

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
		vertices[lines_number].append(sf::Vertex(sf::Vector2f(newPos.x - mult, newPos.y - curr_slope * mult), curr_col));
		vertices[lines_number].append(sf::Vertex(sf::Vector2f(newPos.x + mult, newPos.y + curr_slope * mult), curr_col));
	}

	else
	{
		curr_slope = 1; // m = 1/0
		vertices[lines_number].append(sf::Vertex(sf::Vector2f(newPos.x + radius, newPos.y - radius), curr_col));
		vertices[lines_number].append(sf::Vertex(sf::Vector2f(newPos.x + radius, newPos.y + radius), curr_col));
	}
}