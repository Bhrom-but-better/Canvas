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

void brushConnect(sf::Vector2i newPos, sf::Vector2i lastPos, int radius)
{
	float m, mult;

	if (newPos.y != lastPos.y) {
		m = -(float)(newPos.x - lastPos.x) / (newPos.y - lastPos.y);
		mult = sqrt((radius * radius) / (m * m + 1));
	}

	else {
		m = 1; // m = 1/0
		mult = (float)radius;
	}

	std::cout << "Old pos: " << lastPos.x << " " << lastPos.y << '\n';
	std::cout << "New pos: " << newPos.x << " " << newPos.y << '\n';
	std::cout << newPos.x - mult << " " << lastPos.y - m * mult << '\n';
	std::cout << newPos.x + mult << " " << lastPos.y + m * mult << '\n';

	vertices[lines_number].append(sf::Vertex(sf::Vector2f(newPos.x - mult, newPos.y - m * mult), curr_col));
	vertices[lines_number].append(sf::Vertex(sf::Vector2f(newPos.x + mult, newPos.y + m * mult), curr_col));
}