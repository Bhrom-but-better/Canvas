#include "pentool.hpp"


void pentool_action() 
{
	std::vector<sf::VertexArray> vertices;
	vertices.push_back(sf::VertexArray(sf::LineStrip));
	int line_number = 0;
	bool mousePressed = false;
	
	sf::Color curr_col = sf::Color::Black;
	sf::Vector2i last_mouse_position(0, 0);

	sf::Event evnt2;
	while (artBoard.pollEvent(evnt2)) 
	{
		if (evnt2.type == sf::Event::MouseButtonPressed)
		{
			mousePressed = true;
		}
		if (evnt2.type == sf::Event::MouseButtonReleased)
		{
			if (evnt2.mouseButton.button == sf::Mouse::Left)
			{
				line_number++;
				vertices.push_back(sf::VertexArray(sf::LineStrip));

				mousePressed = false;
			}

		}

		if (mousePressed)
		{
			if (last_mouse_position != sf::Mouse::getPosition(artBoard))
			{
				vertices[line_number].append(sf::Vertex(sf::Vector2f(sf::Mouse::getPosition(artBoard)), curr_col));
				last_mouse_position = sf::Mouse::getPosition();
				std::cout << "X Y : " << vertices[line_number][vertices[line_number].getVertexCount() - 1].position.x << " " << vertices[line_number][vertices[line_number].getVertexCount() - 1].position.y << std::endl;
			}

			curr_col = sf::Color::Color(rand() % 255, rand() % 255, rand() % 255);

		}

	}
	artBoard.clear(sf::Color::White);
	for (auto i = 0; i < vertices.size(); i++)
	{
		artBoard.draw(vertices[i]);
		//if(vertices[i].getVertexCount() > 0)
			//std::cout << "X Y : " << vertices[i][vertices[i].getVertexCount() - 1].position.x << " " << vertices[i][vertices[i].getVertexCount() - 1].position.y << std::endl;
	}
	artBoard.display();
}