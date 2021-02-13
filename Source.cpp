#include "src/global.hpp"

int artBoardWidth = 1080;
int artBoardHeight = 720;

sf::RenderWindow artBoard(sf::VideoMode(artBoardWidth, artBoardHeight), "Canvas", sf::Style::Close, sf::ContextSettings(0, 0, 0));
sf::View vw(sf::Vector2f((float)artBoardWidth / 2.0f, (float)artBoardHeight / 2.0f), sf::Vector2f((float)artBoardWidth, (float)artBoardHeight));
sf::Texture txtr_importedBackground;
sf::Sprite sprt_importedBackground;
sf::RectangleShape background;
sf::Image icon;

int lines_number = 0;
int undo_count = 0;
bool last_cleared = false;
bool mousePressedDown = false; // When a mouse button is pressed this will change to true until a mouse button is released again
bool zoomedIn = false;
bool bgImported = false;
std::string fileLocation = "";

float brushSize = 2.0;

float zoomCordX, zoomCordY;

std::vector<sf::VertexArray> vertices;
sf::Color curr_col = sf::Color::White;
sf::Color grad_col = sf::Color::Black;
sf::Color bg_col = sf::Color::Black;
sf::Vector2i last_Mouse_pos(0, 0);

int main()
{
	vertices.push_back(sf::VertexArray());
	vertices[0].setPrimitiveType(sf::LineStrip);

	init_toolbar(artBoard.getPosition());

	artBoard.setFramerateLimit(60);
	artBoard.setVerticalSyncEnabled(false);

	icon.loadFromFile("./Resources/img/canvasIcon.png");
	artBoard.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	artBoard.clear(bg_col);
	float lastTime = 0;
	background.setSize(sf::Vector2f(artBoard.getSize()));
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
						init_artBoard();
					}
				}
				if (evnt.key.code == sf::Keyboard::Key::Q)
				{
					saved = true;
					if (save(artBoard) == -1) //if cancel is clicked
						continue;
					artBoard.close();
				}

				if (evnt.key.code == sf::Keyboard::Key::S)
				{
					saved = true;
					if (save(artBoard) == -1) //if cancel is clicked
						continue;
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
				//pentool selection
				if (evnt.key.code == sf::Keyboard::Key::P)
				{
					penSelected = penSelected ? 0 : 1;
					brushSelected = false;
					eraserSelected = false;
					fillSelected = false;
					circleSelected = false;
					rectangleSelected = false;
					lineSelected = false;
					gradientSelected = false;
					eyedropperSelected = false;
				}
				//brushtool selection
				else if (evnt.key.code == sf::Keyboard::Key::B)
				{
					brushSelected = brushSelected ? 0 : 1;
					penSelected = false;
					eraserSelected = false;
					fillSelected = false;
					circleSelected = false;
					rectangleSelected = false;
					lineSelected = false;
					gradientSelected = false;
					eyedropperSelected = false;
				}
				//erasertool selection
				else if (evnt.key.code == sf::Keyboard::Key::E)
				{
					eraserSelected = eraserSelected ? 0 : 1;
					penSelected = false;
					brushSelected = false;
					fillSelected = false;
					circleSelected = false;
					rectangleSelected = false;
					lineSelected = false;
					gradientSelected = false;
					eyedropperSelected = false;
				}
				//linetool selection
				else if (evnt.key.code == sf::Keyboard::Key::L)
				{
					lineSelected = lineSelected ? 0 : 1;
					penSelected = false;
					brushSelected = false;
					eraserSelected = false;
					fillSelected = false;
					circleSelected = false;
					rectangleSelected = false;
					gradientSelected = false;
					eyedropperSelected = false;
				}
				//rectangletool selection
				else if (evnt.key.code == sf::Keyboard::Key::R)
				{
					rectangleSelected = rectangleSelected ? 0 : 1;
					penSelected = false;
					brushSelected = false;
					eraserSelected = false;
					fillSelected = false;
					circleSelected = false;
					lineSelected = false;
					gradientSelected = false;
					eyedropperSelected = false;
				}
				//de-select if any tool is selected
				else if (evnt.key.code == sf::Keyboard::Key::Escape)
				{
					rectangleSelected = false;
					penSelected = false;
					brushSelected = false;
					eraserSelected = false;
					fillSelected = false;
					circleSelected = false;
					lineSelected = false;
					gradientSelected = false;
					eyedropperSelected = false;
				}

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
				if (evnt.key.code == sf::Keyboard::Key::LBracket)
				{
					if (brushSize > 1)
					{
						--brushSize;
						pos_crcl_sizeSlider.x = (float)map((int)brushSize, 1, 30, 16, 70);
					}
				}
				else if (evnt.key.code == sf::Keyboard::RBracket)
				{
					if (brushSize <= 30)
					{
						++brushSize;
						pos_crcl_sizeSlider.x = (float)map((int)brushSize, 1, 30, 16, 70);
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
				brush_action(artBoard, evnt, brushSize);
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
				fill_action(artBoard, evnt);
			}

			if (gradientSelected)
			{
				gradient_action(artBoard, evnt);
			}

			if (eyedropperSelected)
			{
				eyedropper_action(artBoard, evnt);
			}
		}

		artBoard.clear(sf::Color(60, 60, 60));
		background.setFillColor(bg_col);
		artBoard.draw(background);

		if (bgImported)
		{
			artBoard.draw(sprt_importedBackground);
		}

		canvas_draw(artBoard);

		if (!zoomedIn)
		{
			init_menu(artBoard);
			menu_action(artBoard, evnt);
		}

		artBoard.setView(vw);
		artBoard.display();
	}

	return 0;
}