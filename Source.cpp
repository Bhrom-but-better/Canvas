#include "SFML/Graphics.hpp"
#include "global.hpp"
#include <iostream>
#include <vector>

sf::RenderWindow artBoard(sf::VideoMode(1280, 720), "Canvas", sf::Style::Close, sf::ContextSettings(0, 0, 0));

int lines_number = 0;
bool mousePressedDown = false; // When a mouse button is pressed this will change to true until a mouse button is released again

std::vector<sf::VertexArray> vertices;
sf::Color curr_col = sf::Color::Black;
sf::Vector2i last_Mouse_pos(0, 0);

int main()
{
	vertices.push_back(sf::VertexArray());
	vertices[0].setPrimitiveType(sf::LineStrip);

	init_toolbar(artBoard.getPosition());

	artBoard.setFramerateLimit(60);
	artBoard.setVerticalSyncEnabled(false);

	artBoard.clear(sf::Color::White);

	while (artBoard.isOpen())
	{
		toolbar_action();

		sf::Event evnt;
		while (artBoard.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed) // Handling the closure of the artBoard
			{
				save(artBoard);
				artBoard.close();
			}

			if (penSelected)
			{
				pentool_action(artBoard, evnt);
			}

			if (brushSelected)
			{
				vertices[lines_number].setPrimitiveType(sf::TriangleStrip);
				brush_action(artBoard, evnt);
			}

			canvas_draw(artBoard);
			artBoard.display();
		}

	}	
	
	return 0;
}