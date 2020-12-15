#include "SFML\Graphics.hpp"
#include <iostream>
#include <vector>
#include "toolbar.hpp"

sf::RenderWindow artBoard(sf::VideoMode(1280, 720), "Canvas", sf::Style::Close, sf::ContextSettings(0, 0, 0));

int main()
{
	std::vector<sf::VertexArray> vertices;
	vertices.push_back(sf::VertexArray());
	vertices[0].setPrimitiveType(sf::LineStrip); //The end vertex of one line is used as the start vertex of the next one
	int lines_number = 0;
	int mousePressedDown = false; // When a mouse button is pressed this will change to true until a mouse button is released again

	sf::Color curr_col = sf::Color::Black;
	sf::Vector2i last_Mouse_pos(0, 0);

	init_toolbar(artBoard.getPosition());

	artBoard.setFramerateLimit(60);

	artBoard.clear(sf::Color::White);

	while (artBoard.isOpen())
	{
		toolbar_action();

		sf::Event event;
		while (artBoard.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed) // Handling the closure of the artBoard
				if (event.key.code == sf::Keyboard::Key::Escape)
					artBoard.close();
			if (event.type == sf::Event::Closed) // Handling the closure of the artBoard
				artBoard.close();

			if (penSelected) {
				if (event.type == sf::Event::MouseButtonPressed)
				{
					mousePressedDown = true;
				}

				if (event.type == sf::Event::MouseButtonReleased)
				{
					// Add a new Line
					lines_number++;
					vertices.push_back(sf::VertexArray());
					vertices[lines_number].setPrimitiveType(sf::LinesStrip);

					mousePressedDown = false; // Reseting mouse pressed status
				}
			}

			if (mousePressedDown)
			{
				if (last_Mouse_pos != sf::Mouse::getPosition()) // When the Mouse hasn't moved don't add any new Vertex (save memory)
				{
					std::cout << "mouseMove : " << event.mouseMove.x << " " << event.mouseMove.y << std::endl;
					//.append(Position, Color) : .append(MousePos - WindowPos + MouseOffset, curr_col)
					vertices[lines_number].append(sf::Vertex(sf::Vector2f(sf::Mouse::getPosition(artBoard).x, sf::Mouse::getPosition(artBoard).y), curr_col));
					//std::cout << "X Y : " << vertices[lines_number][vertices[lines_number].getVertexCount() - 1].position.x << " " << vertices[lines_number][vertices[lines_number].getVertexCount() - 1].position.y << std::endl;
					//std::cout << "Red value: " << unsigned(vertices[lines_number][vertices[lines_number].getVertexCount() - 1].color.r) << std::endl;
					//std::cout << "Blue value: " << unsigned(vertices[lines_number][vertices[lines_number].getVertexCount() - 1].color.g) << std::endl;
					//std::cout << "Green value: " << unsigned(vertices[lines_number][vertices[lines_number].getVertexCount() - 1].color.b) << std::endl;
					//std::cout << "Opacity value: " << unsigned(vertices[lines_number][vertices[lines_number].getVertexCount() - 1].color.a) << std::endl;

					last_Mouse_pos = sf::Mouse::getPosition();
				}
			}

			curr_col = sf::Color::Color(rand() % 255, rand() % 255, rand() % 255);

			//std::cout << "vertices in line " << lines_number << ": " << vertices[lines_number].getVertexCount() << std::endl;

			//std::cout << "getPos : " << sf::Mouse::getPosition().x - window.getPosition().x - Border_Offset.x << " " << sf::Mouse::getPosition().y - window.getPosition().y - Border_Offset.y << std::endl;
		}

		artBoard.clear(sf::Color::White);
		for (int i = 0; i < vertices.size(); i++)
		{
			artBoard.draw(vertices[i]);
			//if(vertices[i].getVertexCount() > 0)
				//std::cout << "X Y : " << vertices[i][vertices[i].getVertexCount() - 1].position.x << " " << vertices[i][vertices[i].getVertexCount() - 1].position.y << std::endl;
		}

		artBoard.display();
	}

	return 0;
}