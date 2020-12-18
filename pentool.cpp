#include "global.hpp"

void pentool_action(sf::RenderWindow& artBoard, sf::Event& evnt)
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
			std::cout << "Mouse released\n";
			lines_number++;
			vertices.push_back(sf::VertexArray(sf::LineStrip));

			mousePressedDown = false;
		}
	}
	if (mousePressedDown)
	{
		if (last_Mouse_pos != sf::Mouse::getPosition(artBoard))
		{
			vertices[lines_number].append(sf::Vertex(sf::Vector2f(sf::Mouse::getPosition(artBoard)), curr_col));
			last_Mouse_pos = sf::Mouse::getPosition();
			std::cout << "X Y : " << vertices[lines_number][vertices[lines_number].getVertexCount() - 1].position.x << " " << vertices[lines_number][vertices[lines_number].getVertexCount() - 1].position.y << std::endl;
		}

		curr_col = sf::Color::Color(rand() % 255, rand() % 255, rand() % 255);
	}

	//(*artBoard).display();
}

void canvas_draw(sf::RenderWindow& artBoard)
{
	(artBoard).clear(sf::Color::White);
	for (auto i = 0; i < vertices.size(); i++)
	{
		printf("Pentool %d\n", i);
		(artBoard).draw(vertices[i]);
		//if(vertices[i].getVertexCount() > 0)
			//std::cout << "X Y : " << vertices[i][vertices[i].getVertexCount() - 1].position.x << " " << vertices[i][vertices[i].getVertexCount() - 1].position.y << std::endl;
	}
}