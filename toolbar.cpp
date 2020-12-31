#include "global.hpp"

bool penSelected = false;
bool brushSelected = false;
bool eraserSelected = false;
bool fillSelected = false;
bool circleSelected = false;
bool rectangleSelected = false;
bool colorPalatteSelected = false;
bool colorMixerSelected = false;
bool lineSelected = false;
bool zoomSelected = false;
int toolbarMouseX, toolbarMouseY;

sf::Sprite sprt_icon_toolbar;
sf::RectangleShape btn_bg_penTool(sf::Vector2f(40.0f, 40.0f));
sf::RectangleShape btn_bg_brushTool(sf::Vector2f(40.0f, 40.0f));
sf::RectangleShape btn_bg_eraserTool(sf::Vector2f(40.0f, 40.0f));
sf::RectangleShape btn_bg_lineTool(sf::Vector2f(40.0f, 40.0f));
sf::RectangleShape btn_bg_fillTool(sf::Vector2f(40.0f, 40.0f));
sf::RectangleShape btn_bg_circleTool(sf::Vector2f(40.0f, 40.0f));
sf::RectangleShape btn_bg_rectangleTool(sf::Vector2f(40.0f, 40.0f));
sf::RectangleShape btn_bg_zoomTool(sf::Vector2f(40.0f, 40.0f));
sf::RectangleShape btn_bg_colorPickTool(sf::Vector2f(40.0f, 40.0f));
sf::Texture icon_tools;

sf::RenderWindow toolbar(sf::VideoMode(120, 160), "Toolbar", sf::Style::None);

void init_toolbar(sf::Vector2i artBoardPos)
{
	toolbar.setPosition({ artBoardPos.x - 123, artBoardPos.y }); //temporary. untill prompting user for size

	icon_tools.loadFromFile("tool_icons.png");

	sprt_icon_toolbar.setPosition(0.0f, 0.0f);

	btn_bg_penTool.setPosition(0.0f, 0.0f);
	btn_bg_brushTool.setPosition(40.0f, 0.0f);
	btn_bg_eraserTool.setPosition(80.0f, 0.0f);
	btn_bg_lineTool.setPosition(0.0f, 40.0f);
	btn_bg_fillTool.setPosition(80.0f, 80.0f);
	btn_bg_circleTool.setPosition(40.0f, 40.0f);
	btn_bg_rectangleTool.setPosition(80.0f, 40.0f);
	btn_bg_zoomTool.setPosition(40.0f, 80.0f);
	btn_bg_colorPickTool.setPosition(0.0f, 80.0f);

	sprt_icon_toolbar.setTexture(icon_tools);

	sprt_icon_toolbar.setScale(0.2f, 0.2f);
}

void toolbar_action(sf::RenderWindow& artBoard)
{
	sf::Event evnt;

	toolbarMouseX = sf::Mouse::getPosition(toolbar).x;
	toolbarMouseY = sf::Mouse::getPosition(toolbar).y;

	while (toolbar.pollEvent(evnt))
	{
		if (evnt.type == sf::Event::MouseButtonPressed)
		{
			if (evnt.mouseButton.button == sf::Mouse::Left)
			{
				//pentool selection
				if (toolbarMouseX >= 0 && toolbarMouseX < 40 && toolbarMouseY >= 0 && toolbarMouseY < 40)
				{
					penSelected = penSelected ? 0 : 1;
					brushSelected = false;
					eraserSelected = false;
					fillSelected = false;
					circleSelected = false;
					rectangleSelected = false;
					lineSelected = false;
				}
				//brushtool selection
				else if (toolbarMouseX >= 40 && toolbarMouseX < 80 && toolbarMouseY >= 0 && toolbarMouseY < 40)
				{
					brushSelected = brushSelected ? 0 : 1;
					penSelected = false;
					eraserSelected = false;
					fillSelected = false;
					circleSelected = false;
					rectangleSelected = false;
					lineSelected = false;
				}
				//erasertool selection
				else if (toolbarMouseX >= 80 && toolbarMouseX < 120 && toolbarMouseY >= 0 && toolbarMouseY < 40)
				{
					eraserSelected = eraserSelected ? 0 : 1;
					penSelected = false;
					brushSelected = false;
					fillSelected = false;
					circleSelected = false;
					rectangleSelected = false;
					lineSelected = false;
				}
				//linetool selection
				else if (toolbarMouseX >= 0 && toolbarMouseX < 40 && toolbarMouseY >= 40 && toolbarMouseY < 80)
				{
					lineSelected = lineSelected ? 0 : 1;
					penSelected = false;
					brushSelected = false;
					eraserSelected = false;
					fillSelected = false;
					circleSelected = false;
					rectangleSelected = false;
				}
				//circletool selection
				else if (toolbarMouseX >= 40 && toolbarMouseX < 80 && toolbarMouseY >= 40 && toolbarMouseY < 80)
				{
					circleSelected = circleSelected ? 0 : 1;
					penSelected = false;
					brushSelected = false;
					eraserSelected = false;
					fillSelected = false;
					rectangleSelected = false;
					lineSelected = false;
				}
				//rectangletool selection
				else if (toolbarMouseX >= 80 && toolbarMouseX < 120 && toolbarMouseY >= 40 && toolbarMouseY < 80)
				{
					rectangleSelected = rectangleSelected ? 0 : 1;
					penSelected = false;
					brushSelected = false;
					eraserSelected = false;
					fillSelected = false;
					circleSelected = false;
					lineSelected = false;
				}
				//zoom selection
				else if (toolbarMouseX >= 40 && toolbarMouseX < 80 && toolbarMouseY >= 80 && toolbarMouseY < 120)
				{
					zoomSelected = zoomSelected ? 0 : 1;
					if (zoomedIn)
						zoomedIn = false;
					else
					{
						penSelected = false;
						brushSelected = false;
						eraserSelected = false;
						fillSelected = false;
						circleSelected = false;
						lineSelected = false;
						rectangleSelected = false;
					}
				}
				//filltool selection
				else if (toolbarMouseX >= 80 && toolbarMouseX < 120 && toolbarMouseY >= 80 && toolbarMouseY < 120)
				{
					fillSelected = fillSelected ? 0 : 1;
					penSelected = false;
					brushSelected = false;
					eraserSelected = false;
					rectangleSelected = false;
					circleSelected = false;
					lineSelected = false;
				}
				//colorPickTool selection
				else if (toolbarMouseX >= 0 && toolbarMouseX < 40 && toolbarMouseY >= 80 && toolbarMouseY < 120)
				{
					colorPalatteSelected = true;
				}
			}

			if (evnt.mouseButton.button == sf::Mouse::Right)
			{
				//handle brush size
				if (toolbarMouseX >= 40 && toolbarMouseX < 80 && toolbarMouseY >= 0 && toolbarMouseY < 40)
				{
					//auto selecting brushtool
					brushSelected = true;
					penSelected = false;
					eraserSelected = false;
					fillSelected = false;
					circleSelected = false;
					rectangleSelected = false;
					lineSelected = false;

					//changing size
					brushSize = brushSize_action(sf::Mouse::getPosition(), brushSize);
					std::cout << "brush size: " << brushSize * 2 << "\n";
				}
				//handle eraser aize
				else if (toolbarMouseX >= 80 && toolbarMouseX < 120 && toolbarMouseY >= 0 && toolbarMouseY < 40)
				{
					//auto selecting erasertool
					eraserSelected = true;
					penSelected = false;
					brushSelected = false;
					fillSelected = false;
					circleSelected = false;
					rectangleSelected = false;
					lineSelected = false;

					//changing size
					eraserSize = brushSize_action(sf::Mouse::getPosition(), eraserSize);
					std::cout << "eraser size: " << eraserSize * 2 << "\n";
				}
				else if (toolbarMouseX >= 0 && toolbarMouseX < 40 && toolbarMouseY >= 80 && toolbarMouseY < 120)
				{
					colorMixerSelected = true;
				}
			}
		}
	}

	//bg handling for penTool
	if (penSelected)
	{
		btn_bg_penTool.setFillColor(sf::Color(46, 46, 46));
	}
	else if (!penSelected && toolbarMouseX >= 0 && toolbarMouseX < 40 && toolbarMouseY >= 0 && toolbarMouseY < 40)
	{
		btn_bg_penTool.setFillColor(sf::Color(60, 60, 60));
	}
	else
	{
		btn_bg_penTool.setFillColor(sf::Color(70, 70, 70));
	}
	//bg handling for brushTool
	if (brushSelected)
	{
		btn_bg_brushTool.setFillColor(sf::Color(46, 46, 46));
	}
	else if (!brushSelected && toolbarMouseX >= 40 && toolbarMouseX < 80 && toolbarMouseY >= 0 && toolbarMouseY < 40)
	{
		btn_bg_brushTool.setFillColor(sf::Color(60, 60, 60));
	}
	else
	{
		btn_bg_brushTool.setFillColor(sf::Color(70, 70, 70));
	}
	//bg handling for eraserTool
	if (eraserSelected)
	{
		btn_bg_eraserTool.setFillColor(sf::Color(46, 46, 46));
	}
	else if (!eraserSelected && toolbarMouseX >= 80 && toolbarMouseX < 120 && toolbarMouseY >= 0 && toolbarMouseY < 40)
	{
		btn_bg_eraserTool.setFillColor(sf::Color(60, 60, 60));
	}
	else
	{
		btn_bg_eraserTool.setFillColor(sf::Color(70, 70, 70));
	}
	//bg handling for lineTool
	if (lineSelected)
	{
		btn_bg_lineTool.setFillColor(sf::Color(46, 46, 46));
	}
	else if (!lineSelected && toolbarMouseX >= 0 && toolbarMouseX < 40 && toolbarMouseY >= 40 && toolbarMouseY < 80)
	{
		btn_bg_lineTool.setFillColor(sf::Color(60, 60, 60));
	}
	else
	{
		btn_bg_lineTool.setFillColor(sf::Color(70, 70, 70));
	}
	//bg handling for circleTool
	if (circleSelected)
	{
		btn_bg_circleTool.setFillColor(sf::Color(46, 46, 46));
	}
	else if (!circleSelected && toolbarMouseX >= 40 && toolbarMouseX < 80 && toolbarMouseY >= 40 && toolbarMouseY < 80)
	{
		btn_bg_circleTool.setFillColor(sf::Color(60, 60, 60));
	}
	else
	{
		btn_bg_circleTool.setFillColor(sf::Color(70, 70, 70));
	}
	//bg handling for rectangleTool
	if (rectangleSelected)
	{
		btn_bg_rectangleTool.setFillColor(sf::Color(46, 46, 46));
	}
	else if (!rectangleSelected && toolbarMouseX >= 80 && toolbarMouseX < 120 && toolbarMouseY >= 40 && toolbarMouseY < 80)
	{
		btn_bg_rectangleTool.setFillColor(sf::Color(60, 60, 60));
	}
	else
	{
		btn_bg_rectangleTool.setFillColor(sf::Color(70, 70, 70));
	}
	//bg handling for zoomTool
	if (zoomSelected)
	{
		btn_bg_zoomTool.setFillColor(sf::Color(46, 46, 46));
	}
	else if (!zoomSelected && toolbarMouseX >= 40 && toolbarMouseX < 80 && toolbarMouseY >= 80 && toolbarMouseY < 120)
	{
		btn_bg_zoomTool.setFillColor(sf::Color(60, 60, 60));
	}
	else
	{
		btn_bg_zoomTool.setFillColor(sf::Color(70, 70, 70));
	}
	//bg handling for fillTool
	if (fillSelected)
	{
		btn_bg_fillTool.setFillColor(sf::Color(46, 46, 46));
	}
	else if (!zoomSelected && toolbarMouseX >= 80 && toolbarMouseX < 120 && toolbarMouseY >= 80 && toolbarMouseY < 120)
	{
		btn_bg_fillTool.setFillColor(sf::Color(60, 60, 60));
	}
	else
	{
		btn_bg_fillTool.setFillColor(sf::Color(70, 70, 70));
	}
	//handling colorPickTool
	btn_bg_colorPickTool.setFillColor(curr_col);
	if (colorPalatteSelected)
	{
		colorPalatte_action(sf::Mouse::getPosition());
	}
	if (colorMixerSelected)
	{
		colorMixer_action(sf::Mouse::getPosition());
	}

	toolbar.clear(sf::Color(70, 70, 70));

	toolbar.draw(btn_bg_penTool);
	toolbar.draw(btn_bg_brushTool);
	toolbar.draw(btn_bg_eraserTool);
	toolbar.draw(btn_bg_lineTool);
	toolbar.draw(btn_bg_fillTool);
	toolbar.draw(btn_bg_circleTool);
	toolbar.draw(btn_bg_rectangleTool);
	toolbar.draw(btn_bg_zoomTool);
	toolbar.draw(btn_bg_colorPickTool);

	toolbar.draw(sprt_icon_toolbar);
	toolbar.display();
}