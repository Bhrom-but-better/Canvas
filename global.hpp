#pragma once
#include <iostream>
#include "SFML\Graphics.hpp"

extern bool penSelected;
extern bool brushSelected;
extern bool eraserSelected;
extern bool fillSelected;
extern bool circleSelected;
extern bool polygonSelected;
extern bool colorPalatteSelected;
extern bool colorMixerSelected;
extern bool lineSelected;
extern bool rectangleSelected;
extern bool zoomSelected;
extern bool zoomedIn;

extern bool mousePressedDown;
extern bool last_cleared;
extern int lines_number;
extern int undo_count;
extern int artBoardWidth;
extern int artBoardHeight;

extern sf::Color curr_col;
extern sf::Color bg_col;
extern sf::Vector2i last_Mouse_pos;
extern std::vector<sf::VertexArray> vertices;

extern float brushSize;
extern float eraserSize;

extern float zoomCordX;
extern float zoomCordY;

void init_toolbar(sf::Vector2i artBoardPos);
void toolbar_action(sf::RenderWindow& artBoard);

void pen_action(sf::RenderWindow& artBoard, sf::Event& evnt);
void brush_action(sf::RenderWindow& artBoard, sf::Event& evnt, float radius);
void line_action(sf::RenderWindow& artBoard, sf::Event& evnt);
void colorPalatte_action(sf::Vector2i mouse_pos);
void colorMixer_action(sf::Vector2i mouse_pos);
float brushSize_action(sf::Vector2i mouse_pos, float currentSize);
void rectangle_action(sf::RenderWindow& artBoard, sf::Event& evnt);
void circle_action(sf::RenderWindow& artBoard, sf::Event& evnt);

void brushConnect(sf::Vector2i newPos, sf::Vector2i lastPos, float radius);
void circleConnect(sf::Vector2f center, float radius, sf::Color col);
sf::VertexArray fillSquare(sf::Vector2f center, float radius, sf::Color col);
sf::Vector2f getCoordinates(sf::Vector2f oldCord);

void canvas_draw(sf::RenderWindow& artBoard);
void mouseToggle(sf::Event& evnt);

int save(sf::RenderWindow& artBoard);