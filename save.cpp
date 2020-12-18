#include "save.hpp"
#include<iostream>

int save(sf::RenderWindow &artBoard) {
	sf::Texture texture;
	texture.create(artBoard.getSize().x, artBoard.getSize().y);
	texture.update(artBoard);
	if (texture.copyToImage().saveToFile("../last drawing.png"))
	{
		std::cout << "Art saved to " << "last drawing.png" << std::endl;
		return 0;
	}
	else
		return -1;
}