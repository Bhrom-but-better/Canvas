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

void check(sf::Vector2i start, const sf::Image& curr_state, const sf::Color& prevCol, std::map<std::pair<int, int>, bool>& mp, sf::RenderWindow& artBoard)
{
	std::cout << vertices[lines_number].getVertexCount() << std::endl;
	int x = start.x; int y = start.y;

	std::cout << "Map size " << mp.size() << std::endl;

	//sf::CircleShape circle;
	//circle.setRadius(1);
	//circle.setPosition(x, y);
	//circle.setFillColor(sf::Color::Red);

	std::cout << x << " " << y << std::endl;

	if (x < 0 || x >= artBoardWidth || y < 0 || y >= artBoardHeight)
		return;

	if (curr_state.getPixel(x, y) != prevCol) {
		std::cout << "not sem" << std::endl;
		return;
	}

	if (mp[{x, y}] == 1) {
		std::cout << "also not sem" << std::endl;
		return;
	}

	mp[{x, y}] = 1;

	//artBoard.draw(circle);
	//artBoard.display();

	check(sf::Vector2i{ x + 1, y }, curr_state, prevCol, mp, artBoard);
	check(sf::Vector2i{ x , y + 1 }, curr_state, prevCol, mp, artBoard);
	check(sf::Vector2i{ x , y - 1 }, curr_state, prevCol, mp, artBoard);
	check(sf::Vector2i{ x - 1, y }, curr_state, prevCol, mp, artBoard);
}

void floodfill(sf::Vector2i start, const sf::Image& curr_state, const sf::Color& prevCol, std::map<std::pair<int, int>, bool>& mp)
{
	int x = start.x; int y = start.y;

	if (x < 0 || x >= artBoardWidth || y < 0 || y >= artBoardHeight)
		return;

	if (curr_state.getPixel(x, y) != prevCol)
		return;
	if (curr_state.getPixel(x, y) == curr_col || mp[{x, y}] == 1)
		return;

	std::cout << "Current position: " << x << " " << y << " " << (unsigned)curr_state.getPixel(x, y).r << " " << (unsigned)curr_state.getPixel(x, y).g << " " << (unsigned)curr_state.getPixel(x, y).b << std::endl;
	std::cout << "prevCol: " << (unsigned)prevCol.r << " " << (unsigned)prevCol.g << " " << (unsigned)prevCol.b << std::endl;

	mp[{x, y}] = 1;
	vertices[lines_number].append(sf::Vertex((sf::Vector2f)start, curr_col));

	floodfill(sf::Vector2i{ x + 1, y }, curr_state, prevCol, mp);
	floodfill(sf::Vector2i{ x + 1, y - 1 }, curr_state, prevCol, mp);
	floodfill(sf::Vector2i{ x + 1, y + 1 }, curr_state, prevCol, mp);
	floodfill(sf::Vector2i{ x , y + 1 }, curr_state, prevCol, mp);
	floodfill(sf::Vector2i{ x , y - 1 }, curr_state, prevCol, mp);
	floodfill(sf::Vector2i{ x - 1, y }, curr_state, prevCol, mp);
	floodfill(sf::Vector2i{ x - 1, y + 1 }, curr_state, prevCol, mp);
	floodfill(sf::Vector2i{ x - 1, y - 1 }, curr_state, prevCol, mp);
}