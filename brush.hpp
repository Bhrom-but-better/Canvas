#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>

void brush_action(sf::RenderWindow& artBoard, sf::Event& evnt);
void brush_draw(sf::RenderWindow& artBoard);

extern std::vector<sf::VertexArray> vertices;