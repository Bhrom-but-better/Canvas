#include "SFML/Graphics.hpp"
#include "global.hpp"
#include <iostream>
#include <vector>

sf::RenderWindow artBoard(sf::VideoMode(1280, 720), "Canvas", sf::Style::Close, sf::ContextSettings(0, 0, 0));

int lines_number = 0;
bool mousePressedDown = false; // When a mouse button is pressed this will change to true until a mouse button is released again

std::vector<sf::VertexArray> vertices;
sf::Color curr_col = sf::Color::Black; //temporary. untill prompting user for input
sf::Color bg_col = sf::Color::White; //temporary. untill prompting user for input
sf::Vector2i last_Mouse_pos(0, 0);

int main()
{
	artBoard.setPosition({ 143, 90 }); //temporary. untill prompting user for size

	vertices.push_back(sf::VertexArray());
	vertices[0].setPrimitiveType(sf::LineStrip);

	init_toolbar(artBoard.getPosition());

	artBoard.setFramerateLimit(60);
	artBoard.setVerticalSyncEnabled(false);

	artBoard.clear(bg_col);

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

			if (evnt.type == sf::Event::KeyPressed) // Handling the closure of the artBoard
			{
				if (evnt.key.code == sf::Keyboard::Key::Q)
				{
					save(artBoard);
					artBoard.close();
				}
				if (evnt.key.code == sf::Keyboard::Key::C)
				{
					vertices.clear();
					lines_number = 0;
					vertices.push_back(sf::VertexArray());
				}
			}

			if (penSelected)
			{
				vertices[lines_number].setPrimitiveType(sf::LineStrip);
				pen_action(artBoard, evnt);
			}

			if (brushSelected)
			{
				vertices[lines_number].setPrimitiveType(sf::TriangleStrip);
				brush_action(artBoard, evnt);
			}

			if (eraserSelected)
			{
				sf::Color prev_col = curr_col;
				curr_col = bg_col;
				vertices[lines_number].setPrimitiveType(sf::TriangleStrip);
				brush_action(artBoard, evnt);
				curr_col = prev_col;
			}

			canvas_draw(artBoard);
			artBoard.display();
		}
	}

	return 0;
}