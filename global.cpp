#include "global.hpp"

int lines_number = 0;
bool mousePressedDown = false; // When a mouse button is pressed this will change to true until a mouse button is released again

std::vector<sf::VertexArray> vertices;
sf::Color curr_col = sf::Color::Black;
sf::Vector2i last_Mouse_pos(0, 0);