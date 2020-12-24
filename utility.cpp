#include "global.hpp"

void canvas_draw(sf::RenderWindow& artBoard)
{
	artBoard.clear(bg_col);

	if(!last_cleared)
		for(auto i = 0; i < (int)vertices.size() - undo_count; i++)
		{
			artBoard.draw(vertices[i]);
		}

}

void mouseToggle(sf::Event& evnt)
{
	if (evnt.type == sf::Event::MouseButtonPressed)
	{
		if (undo_count > 0) {
			while (undo_count){
				printf("Popping %d\n", vertices.size());
				vertices.pop_back();
				--lines_number;
				--undo_count;
			}
		}

		if (evnt.mouseButton.button == sf::Mouse::Left)
		{
			undo_count = 0;
			if (last_cleared) {
				vertices.clear();
				lines_number = -1;
				last_cleared = false;
			}
			if(penSelected || brushSelected){
				vertices.push_back(sf::VertexArray);
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


	vertices[lines_number].append(sf::Vertex(sf::Vector2f(newPos.x - mult, newPos.y - m * mult), curr_col));
	vertices[lines_number].append(sf::Vertex(sf::Vector2f(newPos.x + mult, newPos.y + m * mult), curr_col));
}