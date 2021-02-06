#pragma once
#include <iostream>
#include "SFML\Graphics.hpp"

extern bool saved;

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
extern bool gradientSelected;
extern bool bgImported;

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

extern sf::Font font_arial;

extern std::string fileLocation;

extern sf::Vector2f pos_crcl_sizeSlider;
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
sf::Color colorMixer_action(sf::Vector2i mouse_pos, sf::Color old_col);
float brushSize_action(sf::Vector2i mouse_pos, float currentSize);
void rectangle_action(sf::RenderWindow& artBoard, sf::Event& evnt);
void circle_action(sf::RenderWindow& artBoard, sf::Event& evnt);
void gradient_action(sf::RenderWindow& artBoard, sf::Event& evnt);
void fill_action(sf::RenderWindow& artBoard, sf::Event& evnt);

void floodfill(sf::Vector2i start, const sf::Image& curr_state, const sf::Color& prevCol, sf::RenderWindow& artBoard);
void brushConnect(sf::Vector2i newPos, sf::Vector2i lastPos, float radius, sf::Color col);
void rectangleConnect(sf::Vector2f newPos, sf::Vector2f lastPos, float radius, sf::Color col, int pos);
void circleConnect(sf::Vector2f center, float radius, sf::Color col);
sf::VertexArray fillSquare(sf::Vector2f center, float radius, sf::Color col);
sf::Vector2f getCoordinates(sf::Vector2f oldCord);

void canvas_draw(sf::RenderWindow& artBoard);
void mouseToggle(sf::Event& evnt);

int save(sf::RenderWindow& artBoard);
int normal_save(sf::RenderWindow& artBoard);
bool open();
std::string import();

void init_artBoard(sf::RenderWindow& artBoard, sf::View& vw, sf::RectangleShape& background, sf::Sprite& sprt_importedBackground);
void init_menu(sf::RenderWindow& artBoard);
void menu_action(sf::RenderWindow& artBoard, sf::Event& evnt);