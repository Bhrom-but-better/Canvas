#include "save.hpp"
#include<iostream>

sf::Texture tex;

void update(sf::RenderWindow &artBoard) {
	//sf::Texture tex;
	tex.create(1280, 720);
	
	//if(!tex.update(artBoard))
		//std::cout << "Fuck" << std::endl;
	
}

int save() {
	sf::Image image;
	if (!image.saveToFile("toto.png"))
	return -1;
}