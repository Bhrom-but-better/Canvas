#include "SFML/Graphics.hpp"
#include "global.hpp"
#include <iostream>
#include <vector>

sf::RenderWindow artBoard(sf::VideoMode(1280, 720), "Canvas", sf::Style::Close, sf::ContextSettings(0, 0, 0));

int lines_number = 0;
int undo_count = 0;
bool last_cleared = false;
bool mousePressedDown = false; // When a mouse button is pressed this will change to true until a mouse button is released again

float brushSize = 2.0;
float eraserSize = 2.0;

std::vector<sf::VertexArray> vertices;
sf::Color curr_col = sf::Color::Black; //temporary. untill prompting user for input
sf::Color bg_col = sf::Color::White; //temporary. untill prompting user for input
sf::Vector2i last_Mouse_pos(0, 0);

int main()
{
	//artBoard.setPosition({ 120, 90 }); //temporary. untill prompting user for size

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
			//printf("Current lines number %d Current undo_count %d Current vertices size %d\n", lines_number, undo_count, vertices.size());
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
					last_cleared = true;
				}

				if (evnt.key.code == sf::Keyboard::Key::Z) {
					if (last_cleared) {
						last_cleared = false;
					}

					else if(undo_count < (int)vertices.size())
						++undo_count;

				}
				if (evnt.key.code == sf::Keyboard::Key::X) {
					if(undo_count > 0)
						--undo_count;
				}

			}

			if (penSelected)
			{
				pen_action(artBoard, evnt);
			}

			if (brushSelected)
			{
				brush_action(artBoard, evnt, brushSize);
			}

			if (eraserSelected)
			{
				sf::Color prev_col = curr_col;
				curr_col = bg_col;
				brush_action(artBoard, evnt, eraserSize);
				curr_col = prev_col;
			}

			if (fillSelected) {
				line_action(artBoard, evnt);
			}
		}

	canvas_draw(artBoard);
	artBoard.display();

	}

	return 0;
}