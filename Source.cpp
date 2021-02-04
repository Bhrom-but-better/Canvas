#include "SFML/Graphics.hpp"
#include "src/global.hpp"
#include <Windows.h>
#include <iostream>

int artBoardWidth = 1280; //temporary. untill prompting user for size
int artBoardHeight = 720; //temporary. untill prompting user for size

sf::RenderWindow artBoard(sf::VideoMode(artBoardWidth, artBoardHeight), "Canvas", sf::Style::Close, sf::ContextSettings(0, 0, 0));
sf::View vw(sf::Vector2f((float)artBoardWidth / 2.0f, (float)artBoardHeight / 2.0f), sf::Vector2f((float)artBoardWidth, (float)artBoardHeight));
int lines_number = 0;
int undo_count = 0;
bool last_cleared = false;
bool mousePressedDown = false; // When a mouse button is pressed this will change to true until a mouse button is released again
bool zoomedIn = false;

float brushSize = 2.0;
float eraserSize = 2.0;

float zoomCordX, zoomCordY;

std::vector<sf::VertexArray> vertices;
sf::Color curr_col = sf::Color::White; //temporary. untill prompting user for input
sf::Color bg_col = sf::Color::Black; //temporary. untill prompting user for input
sf::Vector2i last_Mouse_pos(0, 0);

int main()
{
	vertices.push_back(sf::VertexArray());
	vertices[0].setPrimitiveType(sf::LineStrip);

	init_toolbar(artBoard.getPosition());

	artBoard.setFramerateLimit(60);
	artBoard.setVerticalSyncEnabled(false);

	sf::Image icon;
	icon.loadFromFile("./Resources/img/canvasIcon.png");
	artBoard.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	artBoard.clear(bg_col);
	float lastTime = 0;
	sf::RectangleShape background(sf::Vector2f(artBoard.getSize()));
	background.setPosition(0.f, 0.f);
	background.setFillColor(bg_col);
	background.setOutlineColor(sf::Color::Yellow);
	background.setOutlineThickness(2.f);

	artBoard.draw(background);

	while (artBoard.isOpen())
	{
		toolbar_action(artBoard);

		sf::Event evnt;
		while (artBoard.pollEvent(evnt))
		{
			//printf("Current lines number %d Current undo_count %d Current vertices size %d\n", lines_number, undo_count, vertices.size());
			if (evnt.type == sf::Event::Closed) // Handling the closure of the artBoard
			{
				if (save(artBoard) == -1)  //if cancel is clicked
				{
					continue;
				}
				artBoard.close();
			}

			if (evnt.type == sf::Event::MouseButtonPressed)
			{
				if (evnt.mouseButton.button == sf::Mouse::Left)
				{
					if (zoomSelected && !zoomedIn)
					{
						zoomCordX = (float)sf::Mouse::getPosition(artBoard).x;
						zoomCordY = (float)sf::Mouse::getPosition(artBoard).y;
						zoomedIn = true;
					}
				}
				else if (evnt.mouseButton.button == sf::Mouse::Right)
				{
					if (zoomSelected && zoomedIn)
					{
						lineSelected = false;
						rectangleSelected = false;
						zoomSelected = false;
						zoomedIn = false;
					}
				}
			}

			if (evnt.type == sf::Event::KeyPressed)
			{
				if (evnt.key.code == sf::Keyboard::Key::O)
				{
					if (!open())
					{
						artBoard.setSize(sf::Vector2u(artBoardWidth, artBoardHeight));
						vw.setCenter(sf::Vector2f((float)artBoardWidth / 2.0f, (float)artBoardHeight / 2.0f));
						vw.setSize(sf::Vector2f((float)artBoardWidth, (float)artBoardHeight));
						lines_number = 0;
						undo_count = 0;
						last_cleared = false;
						mousePressedDown = false;
						zoomedIn = false;
						penSelected = false;
						brushSelected = false;
						eraserSelected = false;
						fillSelected = false;
						circleSelected = false;
						rectangleSelected = false;
						colorPalatteSelected = false;
						colorMixerSelected = false;
						lineSelected = false;
						zoomSelected = false;
						brushSize = 2.0;
						eraserSize = 2.0;
						vertices.clear();
						vertices.push_back(sf::VertexArray());
						vertices[0].setPrimitiveType(sf::LineStrip);
						background.setSize(sf::Vector2f(artBoard.getSize()));
						background.setFillColor(bg_col);
					}
				}
				if (evnt.key.code == sf::Keyboard::Key::Q)
				{
					saved = true;
					if (save(artBoard) == -1) //if cancel is clicked
						continue;
					//artBoard.close();
				}

				if (evnt.key.code == sf::Keyboard::Key::C)
				{
					last_cleared = true;
				}

				if (evnt.key.code == sf::Keyboard::Key::Z)
				{
					if (last_cleared) {
						last_cleared = false;
					}

					else if (undo_count < (int)vertices.size())
						++undo_count;
				}

				if (evnt.key.code == sf::Keyboard::Key::X)
				{
					if (undo_count > 0)
						--undo_count;
				}
				if (evnt.type == sf::Event::KeyPressed)
				{
					if (evnt.key.code == sf::Keyboard::Key::Period)
					{
						zoomCordX = (float)sf::Mouse::getPosition(artBoard).x;
						zoomCordY = (float)sf::Mouse::getPosition(artBoard).y;
						zoomSelected = true;
						zoomedIn = true;
					}
					else if (evnt.key.code == sf::Keyboard::Comma)
					{
						zoomSelected = false;
						zoomedIn = false;
					}
				}
			}

			if (penSelected)
			{
				pen_action(artBoard, evnt);
			}

			if (brushSelected)
			{
				brush_action(artBoard, evnt, brushSize);
			}

			if (eraserSelected)
			{
				sf::Color prev_col = curr_col;
				curr_col = bg_col;
				brush_action(artBoard, evnt, eraserSize);
				curr_col = prev_col;
			}

			if (lineSelected)
			{
				line_action(artBoard, evnt);
			}

			if (rectangleSelected)
			{
				rectangle_action(artBoard, evnt);
			}

			if (circleSelected)
			{
				circle_action(artBoard, evnt);
			}

			if (zoomedIn)
			{
				vw.setCenter(sf::Vector2f(zoomCordX, zoomCordY));
				vw.setSize(sf::Vector2f((float)artBoardWidth / 3.0f, (float)artBoardHeight / 3.0f));
			}
			else
			{
				vw.setCenter(sf::Vector2f((float)artBoardWidth / 2.0f, (float)artBoardHeight / 2.0f));
				vw.setSize(sf::Vector2f((float)artBoardWidth, (float)artBoardHeight));
			}

			if (fillSelected) {
				sf::Color col = sf::Color::Color(rand() % 255, rand() % 255, rand() % 255, 255);
				for (float i = 0; i < artBoardHeight; ++i) {
					for (float j = 0; j < artBoardWidth; ++j) {
						vertices[lines_number].append(sf::Vertex(sf::Vector2f(j, i), col));
					}
				}
				fillSelected = false;
			}
		}

		artBoard.setView(vw);
		artBoard.clear(sf::Color(60, 60, 60));
		artBoard.draw(background);
		canvas_draw(artBoard);
		init_menu(artBoard);
		menu_action(artBoard, evnt);
		artBoard.display();
		//std::cout << vertices.size() << " " << vertices[vertices.size() - 1].getVertexCount() << '\n';
	}

	return 0;
}