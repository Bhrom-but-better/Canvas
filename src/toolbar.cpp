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
bool gradientSelected = false;
bool sizeSliderSelected = false;
bool eyedropperSelected = false;

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
sf::RectangleShape btn_bg_gradient(sf::Vector2f(40.0f, 40.0f));
sf::RectangleShape btn_bg_eyedropper(sf::Vector2f(40.0f, 40.0f));
sf::Texture icon_tools;

sf::RectangleShape bar_sizeSlider(sf::Vector2f(70.0f, 3.0f));
sf::CircleShape crcl_sizeSlider(8.0f);
sf::Vector2f pos_crcl_sizeSlider;
sf::Font font_arial;
sf::Text txt_sizeSlider(std::to_string((int)brushSize), font_arial, 16);

sf::ContextSettings settings;
sf::RenderWindow toolbar(sf::VideoMode(120, 200), "Toolbar", sf::Style::None);

void init_toolbar(sf::Vector2i artBoardPos)
{
	settings.antialiasingLevel = 8;

	toolbar.setPosition({ artBoardPos.x - 123, artBoardPos.y }); //temporary. untill prompting user for size

	if (!font_arial.loadFromFile("./Resources/fonts/arial.ttf"))
	{
		std::cout << "unable to load font\n";
	}

	icon_tools.loadFromFile("./Resources/img/tool_icons.png"); //NEED TO ERROR CHECK

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
	btn_bg_gradient.setPosition(0.0f, 120.0f);
	btn_bg_eyedropper.setPosition(40.0f, 120.0f);

	bar_sizeSlider.setPosition({ 16.0f, 179.0f });
	bar_sizeSlider.setFillColor(sf::Color(100, 100, 100));

	pos_crcl_sizeSlider = { bar_sizeSlider.getPosition().x, bar_sizeSlider.getPosition().y - crcl_sizeSlider.getRadius() + 1.5f };
	crcl_sizeSlider.setPosition(pos_crcl_sizeSlider);
	crcl_sizeSlider.setFillColor(sf::Color(90, 90, 90));
	crcl_sizeSlider.setOutlineThickness(1.5f);
	crcl_sizeSlider.setOutlineColor(sf::Color::White);

	txt_sizeSlider.setPosition({ 94.0f, 170.0f });
	txt_sizeSlider.setFillColor(sf::Color::White);

	sprt_icon_toolbar.setTexture(icon_tools);

	sprt_icon_toolbar.setScale(0.2f, 0.2f);
}

int map(int x, int in_min, int in_max, int out_min, int out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
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
					gradientSelected = false;
					eyedropperSelected = false;
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
					gradientSelected = false;
					eyedropperSelected = false;
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
					gradientSelected = false;
					eyedropperSelected = false;
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
					gradientSelected = false;
					eyedropperSelected = false;
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
					gradientSelected = false;
					eyedropperSelected = false;
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
					gradientSelected = false;
					eyedropperSelected = false;
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
						gradientSelected = false;
						eyedropperSelected = false;
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
					gradientSelected = false;
					eyedropperSelected = false;
				}
				//colorPickTool selection
				else if (toolbarMouseX >= 0 && toolbarMouseX < 40 && toolbarMouseY >= 80 && toolbarMouseY < 120)
				{
					colorPalatteSelected = true;
				}
				//gradientTool selection
				else if (toolbarMouseX >= 0 && toolbarMouseX < 40 && toolbarMouseY >= 120 && toolbarMouseY < 160)
				{
					gradientSelected = gradientSelected ? 0 : 1;
					fillSelected = false;
					penSelected = false;
					brushSelected = false;
					eraserSelected = false;
					rectangleSelected = false;
					circleSelected = false;
					lineSelected = false;
					eyedropperSelected = false;
				}
				//eyedropper selection
				else if (toolbarMouseX >= 40 && toolbarMouseX < 80 && toolbarMouseY >= 120 && toolbarMouseY < 160)
				{
					eyedropperSelected = eyedropperSelected ? 0 : 1;
					fillSelected = false;
					penSelected = false;
					brushSelected = false;
					eraserSelected = false;
					rectangleSelected = false;
					circleSelected = false;
					lineSelected = false;
					gradientSelected = false;
				}
				//size slider selection
				else if (toolbarMouseX >= pos_crcl_sizeSlider.x && toolbarMouseX < pos_crcl_sizeSlider.x + crcl_sizeSlider.getRadius() * 2 && toolbarMouseY >= pos_crcl_sizeSlider.y && toolbarMouseY < pos_crcl_sizeSlider.y + crcl_sizeSlider.getRadius() * 2)
				{
					sizeSliderSelected = true;
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
					gradientSelected = false;

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
					gradientSelected = false;

					//changing size
					brushSize = brushSize_action(sf::Mouse::getPosition(), brushSize);
				}
				else if (toolbarMouseX >= 0 && toolbarMouseX < 40 && toolbarMouseY >= 80 && toolbarMouseY < 120)
				{
					colorMixerSelected = true;
				}
			}
		}
		else if (evnt.type == sf::Event::MouseButtonReleased)
		{
			if (evnt.mouseButton.button == sf::Mouse::Left)
			{
				sizeSliderSelected = false;
			}
		}
	}

	if (sizeSliderSelected)
	{
		//float x = sf::Mouse::getPosition(toolbar).x - crcl_sizeSlider.getRadius();
		float x = sf::Mouse::getPosition(toolbar).x;
		float sliderPos = x - bar_sizeSlider.getPosition().x + 1.0f;
		if (x >= bar_sizeSlider.getPosition().x && x < bar_sizeSlider.getPosition().x + bar_sizeSlider.getSize().x)
		{
			pos_crcl_sizeSlider.x = x - 8.0f;
			brushSize = map(sliderPos, 0, bar_sizeSlider.getSize().x, 1, 30);
			//pos_crcl_sizeSlider.x = 6.0f + brushSize;
			txt_sizeSlider.setString(std::to_string((int)brushSize));
		}
		crcl_sizeSlider.setPosition(pos_crcl_sizeSlider);
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
	//bg handling for gradients
	if (gradientSelected)
	{
		btn_bg_gradient.setFillColor(sf::Color(46, 46, 46));
	}
	else if (!zoomSelected && toolbarMouseX >= 0 && toolbarMouseX < 40 && toolbarMouseY >= 120 && toolbarMouseY < 160)
	{
		btn_bg_gradient.setFillColor(sf::Color(60, 60, 60));
	}
	else
	{
		btn_bg_gradient.setFillColor(sf::Color(70, 70, 70));
	}
	//bg handling for eyedropper
	if (eyedropperSelected)
	{
		btn_bg_eyedropper.setFillColor(sf::Color(46, 46, 46));
	}
	else if (!zoomSelected && toolbarMouseX >= 40 && toolbarMouseX < 80 && toolbarMouseY >= 120 && toolbarMouseY < 160)
	{
		btn_bg_eyedropper.setFillColor(sf::Color(60, 60, 60));
	}
	else
	{
		btn_bg_eyedropper.setFillColor(sf::Color(70, 70, 70));
	}
	//handling colorPickTool
	btn_bg_colorPickTool.setFillColor(curr_col);
	if (colorPalatteSelected)
	{
		colorPalatte_action(sf::Mouse::getPosition());
	}
	if (colorMixerSelected)
	{
		curr_col = colorMixer_action(sf::Mouse::getPosition(), curr_col);
	}

	crcl_sizeSlider.setPosition(pos_crcl_sizeSlider);
	txt_sizeSlider.setString(std::to_string((int)brushSize));

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
	toolbar.draw(btn_bg_gradient);
	toolbar.draw(btn_bg_eyedropper);
	toolbar.draw(bar_sizeSlider);
	toolbar.draw(crcl_sizeSlider);
	toolbar.draw(txt_sizeSlider);

	toolbar.draw(sprt_icon_toolbar);
	toolbar.display();
}