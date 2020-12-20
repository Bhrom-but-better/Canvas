#include "global.hpp"

void brush_action(sf::RenderWindow& artBoard, sf::Event& evnt)
{
	int radius = 5;

	mouseToggle(evnt);

	if (mousePressedDown)
	{
		if (last_Mouse_pos != sf::Mouse::getPosition(artBoard))
		{
			sf::Vector2i new_Mouse_pos = sf::Mouse::getPosition(artBoard);
			if (last_Mouse_pos.x != 0 && last_Mouse_pos.y != 0)
				brushConnect(new_Mouse_pos, last_Mouse_pos, radius);
			last_Mouse_pos = new_Mouse_pos;
			//std::cout << "X Y : " << vertices[lines_number][vertices[lines_number].getVertexCount() - 1].position.x << " " << vertices[lines_number][vertices[lines_number].getVertexCount() - 1].position.y << std::endl;
		}

		//curr_col = sf::Color::Color(rand() % 255, rand() % 255, rand() % 255);
	}

	//(*artBoard).display();
}

void pen_action(sf::RenderWindow& artBoard, sf::Event& evnt)
{

	mouseToggle(evnt);

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