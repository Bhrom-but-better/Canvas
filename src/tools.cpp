#include "global.hpp"

sf::Vector2f first_position;
sf::Vector2f firstPoint;

bool brushTap = false;
bool penTap = false;

void brush_action(sf::RenderWindow& artBoard, sf::Event& evnt, float radius)
{
	mouseToggle(evnt);

	if (mousePressedDown)
	{
		brushTap = true;
		sf::Vector2i curr_Mouse_pos = sf::Mouse::getPosition(artBoard);

		if (last_Mouse_pos != curr_Mouse_pos)
		{
			vertices[lines_number].setPrimitiveType(sf::TriangleStrip);
			sf::Vector2i new_Mouse_pos = curr_Mouse_pos;
			if (last_Mouse_pos.x != 0 && last_Mouse_pos.y != 0) {
				brushConnect(last_Mouse_pos, new_Mouse_pos, radius, curr_col);
				//brushConnect(new_Mouse_pos, last_Mouse_pos, radius, curr_col);
			}
			last_Mouse_pos = new_Mouse_pos;
			//std::cout << "X Y : " << vertices[lines_number][vertices[lines_number].getVertexCount() - 1].position.x << " " << vertices[lines_number][vertices[lines_number].getVertexCount() - 1].position.y << std::endl;
		}

		//curr_col = sf::Color::Color(rand() % 255, rand() % 255, rand() % 255);
	}

	else if (!mousePressedDown && brushTap && vertices[lines_number].getVertexCount() == 0) {
		vertices[lines_number] = fillSquare((sf::Vector2f)last_Mouse_pos, brushSize, curr_col);
	}

	if (!mousePressedDown)
	{
		last_Mouse_pos.x = 0;
		last_Mouse_pos.y = 0;
		brushTap = false;
	}
}

void pen_action(sf::RenderWindow& artBoard, sf::Event& evnt)
{
	mouseToggle(evnt);

	if (mousePressedDown)
	{
		penTap = true;
		vertices[lines_number].setPrimitiveType(sf::LineStrip);
		if (last_Mouse_pos != sf::Mouse::getPosition(artBoard))
		{
			vertices[lines_number].append(sf::Vertex(getCoordinates((sf::Vector2f)sf::Mouse::getPosition(artBoard)), curr_col));
			last_Mouse_pos = sf::Mouse::getPosition();
		}

		//curr_col = sf::Color::Color(rand() % 255, rand() % 255, rand() % 255);
	}

	else if (!mousePressedDown && penTap && vertices[lines_number].getVertexCount() <= 2)
	{
		vertices[lines_number].setPrimitiveType(sf::PrimitiveType::Points);
		vertices[lines_number][0] = sf::Vertex(getCoordinates((sf::Vector2f)sf::Mouse::getPosition(artBoard)), curr_col);
	}

	if (!mousePressedDown)
	{
		last_Mouse_pos.x = 0;
		last_Mouse_pos.y = 0;
		penTap = false;
	}

	//(*artBoard).display();
}

void colorPalatte_action(sf::Vector2i mouse_pos)
{
	int x, y;

	sf::RenderWindow colorPalette(sf::VideoMode(80, 40), "", sf::Style::None);
	sf::Texture tex_colorPalette;
	sf::Sprite spt_colorPalette;
	sf::Event evnt;

	tex_colorPalette.loadFromFile("./Resources/img/ColorPalette.png");
	spt_colorPalette.setTexture(tex_colorPalette);

	colorPalette.setPosition(mouse_pos);

	while (colorPalette.isOpen())
	{
		x = sf::Mouse::getPosition(colorPalette).x;
		y = sf::Mouse::getPosition(colorPalette).y;

		if (x < 0 || y < 0 || x > 80 || y > 40)
		{
			colorPalatteSelected = false;
			colorPalette.close();
			break;
		}

		while (colorPalette.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::MouseButtonPressed)
			{
				if (evnt.mouseButton.button == sf::Mouse::Left)
				{
					if (x >= 0 && x < 20 && y >= 0 && y < 20)
					{
						curr_col = sf::Color::White;
					}
					else if (x >= 20 && x < 40 && y >= 0 && y < 20)
					{
						curr_col = sf::Color::Cyan;
					}
					else if (x >= 40 && x < 60 && y >= 0 && y < 20)
					{
						curr_col = sf::Color::Yellow;
					}
					else if (x >= 60 && x < 80 && y >= 0 && y < 20)
					{
						curr_col = sf::Color::Magenta;
					}
					else if (x >= 0 && x < 20 && y >= 20 && y < 40)
					{
						curr_col = sf::Color::Black;
					}
					else if (x >= 20 && x < 40 && y >= 20 && y < 40)
					{
						curr_col = sf::Color::Red;
					}
					else if (x >= 40 && x < 60 && y >= 20 && y < 40)
					{
						curr_col = sf::Color::Blue;
					}
					else if (x >= 60 && x < 80 && y >= 20 && y < 40)
					{
						curr_col = sf::Color::Green;
					}
					colorPalatteSelected = false;
					colorPalette.close();
				}
			}
		}
		colorPalette.clear(sf::Color::White);
		colorPalette.draw(spt_colorPalette);
		colorPalette.display();
	}
}

void colorMixer_action(sf::Vector2i mouse_pos, bool pick)
{
	int mixerX, mixerY;

	bool redSelected = false;
	bool greenSelected = false;
	bool blueSelected = false;
	bool alphaSelected = false;
	bool mousePressedDown = false;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow colorMixer(sf::VideoMode(438, 110), "testSFML", sf::Style::None, settings);
	
	sf::Color new_col = curr_col;
	sf::Color new_bg = bg_col;

	sf::CircleShape crcl_red(8);
	sf::CircleShape crcl_green(8);
	sf::CircleShape crcl_blue(8);
	sf::CircleShape crcl_alpha(8);

	sf::RectangleShape bar_r(sf::Vector2f(255.0f, 3.0f));
	sf::RectangleShape bar_g(sf::Vector2f(255.0f, 3.0f));
	sf::RectangleShape bar_b(sf::Vector2f(255.0f, 3.0f));
	sf::RectangleShape bar_a(sf::Vector2f(255.0f, 3.0f));
	sf::RectangleShape rect_currCol(sf::Vector2f(80.0f, 47.0f));
	sf::RectangleShape rect_newCol(sf::Vector2f(80.0f, 47.0f));

	colorMixer.setPosition(mouse_pos);

	sf::Font font;
	if (!font.loadFromFile("./Resources/fonts/arial.ttf"))
	{
		std::cout << "unable to load font\n";
	}

	sf::Text tb_r("R", font, 16);
	tb_r.setPosition({ 8, 8 });
	tb_r.setFillColor(sf::Color(180, 180, 180));
	sf::Text tb_rVal; 
	
	if (pick)
		tb_rVal.setString(std::to_string((int)curr_col.r));
	else 
		tb_rVal.setString(std::to_string((int)bg_col.r));
	tb_rVal.setFont(font);
	tb_rVal.setCharacterSize(16);
	tb_rVal.setPosition({ 310, 8 });
	tb_rVal.setFillColor(sf::Color(180, 180, 180));
	
	sf::Text tb_g("G", font, 16);
	tb_g.setPosition({ 8, 33 });
	tb_g.setFillColor(sf::Color(180, 180, 180));
	sf::Text tb_gVal;
	
	if (pick)
		tb_gVal.setString(std::to_string((int)curr_col.g));
	else
		tb_gVal.setString(std::to_string((int)bg_col.g));
	tb_gVal.setFont(font);
	tb_gVal.setCharacterSize(16);
	tb_gVal.setPosition({ 310, 8 });
	tb_gVal.setFillColor(sf::Color(180, 180, 180));

	sf::Text tb_b("B", font, 16);
	tb_b.setPosition({ 8, 58 });
	tb_b.setFillColor(sf::Color(180, 180, 180));
	sf::Text tb_bVal; 
	if (pick)
		tb_bVal.setString(std::to_string((int)curr_col.b));
	else
		tb_bVal.setString(std::to_string((int)bg_col.b));
	tb_bVal.setFont(font);
	tb_bVal.setCharacterSize(16);
	tb_bVal.setPosition({ 310, 8 });
	tb_bVal.setFillColor(sf::Color(180, 180, 180));

	sf::Text tb_a("A", font, 16);
	tb_a.setPosition({ 8, 83 });
	tb_a.setFillColor(sf::Color(180, 180, 180));
	sf::Text tb_aVal;
	if (pick)
		tb_aVal.setString(std::to_string((int)curr_col.a));
	else
		tb_aVal.setString(std::to_string((int)bg_col.a));
	tb_aVal.setFont(font);
	tb_aVal.setCharacterSize(16);
	tb_aVal.setPosition({ 310, 8 });
	tb_aVal.setFillColor(sf::Color(180, 180, 180));

	if (pick)
	{
		crcl_red.setPosition((float)curr_col.r + 30.0f, 10.0f);
		crcl_red.setFillColor(sf::Color(curr_col.r, 0, 0, 255));
	}
	else
	{
		crcl_red.setPosition((float)bg_col.r + 30.0f, 10.0f);
		crcl_red.setFillColor(sf::Color(bg_col.r, 0, 0, 255));
	}
	crcl_red.setOutlineThickness(2);
	crcl_red.setOutlineColor(sf::Color(200, 200, 200));

	if (pick)
	{
		crcl_green.setPosition((float)curr_col.g + 30.0f, 35.0f);
		crcl_green.setFillColor(sf::Color(0, curr_col.g, 0, 255));
	}
	else
	{
		crcl_green.setPosition((float)bg_col.g + 30.0f, 35.0f);
		crcl_green.setFillColor(sf::Color(0, bg_col.g, 0, 255));
	}
	crcl_green.setOutlineThickness(2);
	crcl_green.setOutlineColor(sf::Color(200, 200, 200));
	
	if (pick)
	{
		crcl_blue.setPosition((float)curr_col.b + 30.0f, 60.0f);
		crcl_blue.setFillColor(sf::Color(0, 0, curr_col.b, 255));
	}
	else
	{
		crcl_blue.setPosition((float)bg_col.b + 30.0f, 60.0f);
		crcl_blue.setFillColor(sf::Color(0, 0, bg_col.b, 255));
	}
	crcl_blue.setOutlineThickness(2);
	crcl_blue.setOutlineColor(sf::Color(200, 200, 200));
	
	if (pick)
	{
		crcl_alpha.setPosition((float)curr_col.a + 30.0f, 85.0f);
		crcl_alpha.setFillColor(sf::Color(0, 0, 0, curr_col.a));
	}
	else
	{
		crcl_alpha.setPosition((float)bg_col.a + 30.0f, 85.0f);
		crcl_alpha.setFillColor(sf::Color(0, 0, 0, bg_col.a));
	}
	crcl_alpha.setOutlineThickness(2);
	crcl_alpha.setOutlineColor(sf::Color(200, 200, 200));

	rect_newCol.setPosition(350.0, 8.0);
	if (pick)
		rect_newCol.setFillColor(new_col);
	else
		rect_newCol.setFillColor(new_bg);
	
	rect_currCol.setPosition(350.0, 55.0);
	if (pick)
		rect_currCol.setFillColor(curr_col);
	else
		rect_currCol.setFillColor(bg_col);
	
	bar_r.setPosition(38.0, 17.0);
	bar_r.setFillColor(sf::Color::Red);

	bar_g.setPosition(38.0, 42.0);
	bar_g.setFillColor(sf::Color::Green);

	bar_b.setPosition(38.0, 67.0);
	bar_b.setFillColor(sf::Color::Blue);

	bar_a.setPosition(38.0, 92.0);
	bar_a.setFillColor(sf::Color::White);

	while (colorMixer.isOpen())
	{
		mixerX = sf::Mouse::getPosition(colorMixer).x;
		mixerY = sf::Mouse::getPosition(colorMixer).y;

		if (mixerX < 0 || mixerY < 0 || mixerX > 438 || mixerY > 110)
		{
			if (pick)
				curr_col = new_col;
			else
				bg_col = new_bg;
			colorMixerSelected = false;
			colorMixer.close();
			break;
		}

		sf::Event evnt;
		while (colorMixer.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				colorMixer.close();
			}
			else if (evnt.type == sf::Event::MouseButtonPressed)
			{
				if (evnt.mouseButton.button == sf::Mouse::Left)
				{
					mousePressedDown = true;
					int x = sf::Mouse::getPosition(colorMixer).x;
					int y = sf::Mouse::getPosition(colorMixer).y;
					int redX = (int)crcl_red.getPosition().x;
					int redY = (int)crcl_red.getPosition().y;
					int greenX = (int)crcl_green.getPosition().x;
					int greenY = (int)crcl_green.getPosition().y;
					int blueX = (int)crcl_blue.getPosition().x;
					int blueY = (int)crcl_blue.getPosition().y;
					int alphaX = (int)crcl_alpha.getPosition().x;
					int alphaY = (int)crcl_alpha.getPosition().y;
					if ((x >= redX && x <= redX + 16 && y >= redY && y <= redY + 16) || (x >= 38 && x <= 293 && y >= 10 && y <= 27))
					{
						redSelected = true;
						greenSelected = false;
						blueSelected = false;
						alphaSelected = false;
					}
					else if ((x >= greenX && x <= greenX + 16 && y >= greenY && y <= greenY + 16) || (x >= 38 && x <= 293 && y >= 35 && y <= 52))
					{
						redSelected = false;
						greenSelected = true;
						blueSelected = false;
						alphaSelected = false;
					}
					else if ((x >= blueX && x <= blueX + 16 && y >= blueY && y <= blueY + 16) || (x >= 38 && x <= 293 && y >= 60 && y <= 77))
					{
						redSelected = false;
						greenSelected = false;
						blueSelected = true;
						alphaSelected = false;
					}
					else if ((x >= alphaX && x <= alphaX + 16 && y >= alphaY && y <= alphaY + 16) || (x >= 38 && x <= 293 && y >= 85 && y <= 102))
					{
						redSelected = false;
						greenSelected = false;
						blueSelected = false;
						alphaSelected = true;
					}
				}
			}
			else if (evnt.type == sf::Event::MouseButtonReleased)
			{
				if (evnt.mouseButton.button == sf::Mouse::Left)
				{
					mousePressedDown = false;
					redSelected = false;
					greenSelected = false;
					blueSelected = false;
					alphaSelected = false;
				}
			}
			else if (evnt.type == sf::Event::KeyPressed)
			{
				if (evnt.key.code == sf::Keyboard::Key::Escape)
				{
					colorMixerSelected = false;
					colorMixer.close();
					break;
				}
				else if (evnt.key.code == sf::Keyboard::Key::Enter)
				{
					if (pick)
						curr_col = new_col;
					else
						bg_col = new_bg;

					colorMixerSelected = false;
					colorMixer.close();
					break;
				}
			}
		}
		if (redSelected)
		{
			float x = sf::Mouse::getPosition(colorMixer).x - crcl_red.getRadius() / 2;
			float sliderPos = (float)x - 30.0f;
			if (x >= 30.0 && x < 286.0)
			{
				crcl_red.setPosition({ x, 10.0 });
				crcl_red.setFillColor(sf::Color((int)sliderPos % 256, 0, 0, 255));
				if (pick)
				{
					new_col.r = (int)sliderPos % 256;
					tb_rVal.setString(std::to_string((int)new_col.r));
				}	
				else
				{
					new_bg.r = (int)sliderPos % 256;
					tb_rVal.setString(std::to_string((int)new_bg.r));
				}
			}
		}
		if (greenSelected)
		{
			float x = sf::Mouse::getPosition(colorMixer).x - crcl_green.getRadius() / 2;
			float sliderPos = (float)x - 30.0f;
			if (x >= 30.0 && x < 286.0)
			{
				crcl_green.setPosition({ x, 35.0 });
				crcl_green.setFillColor(sf::Color(0, (int)sliderPos % 256, 0, 255));
				if (pick)
				{
					new_col.g = (int)sliderPos % 256;
					tb_gVal.setString(std::to_string((int)new_col.g));
				}
				else
				{
					new_bg.g = (int)sliderPos % 256;
					tb_gVal.setString(std::to_string((int)new_bg.g));
				}
			}
		}
		if (blueSelected)
		{
			float x = sf::Mouse::getPosition(colorMixer).x - crcl_blue.getRadius() / 2;
			float sliderPos = (float)x - 30.0f;
			if (x >= 30.0 && x < 286.0)
			{
				crcl_blue.setPosition({ x, 60.0 });
				crcl_blue.setFillColor(sf::Color(0, 0, (int)sliderPos % 256, 255));
				if (pick)
				{
					new_col.b = (int)sliderPos % 256;
					tb_bVal.setString(std::to_string((int)new_col.b));
				}
				else
				{
					new_bg.b = (int)sliderPos % 256;
					tb_bVal.setString(std::to_string((int)new_bg.b));
				}
			}
		}
		if (alphaSelected)
		{
			float x = sf::Mouse::getPosition(colorMixer).x - crcl_alpha.getRadius() / 2;
			float sliderPos = (float)x - 30.0f;
			if (x >= 30.0 && x < 286.0)
			{
				crcl_alpha.setPosition({ x, 85.0 });
				crcl_alpha.setFillColor(sf::Color(0, 0, 0, (int)sliderPos % 256));
				if (pick)
				{
					new_col.a = (int)sliderPos % 256;
					tb_aVal.setString(std::to_string((int)new_col.a));
				}
				else
				{
					new_bg.a = (int)sliderPos % 256;
					tb_aVal.setString(std::to_string((int)new_bg.a));
				}
			}
		}

		if (pick)
			rect_newCol.setFillColor(new_col);
		else
			rect_newCol.setFillColor(new_bg);


		colorMixer.clear(sf::Color(60, 60, 60));

		colorMixer.draw(tb_r);
		colorMixer.draw(tb_rVal);
		colorMixer.draw(tb_g);
		colorMixer.draw(tb_gVal);
		colorMixer.draw(tb_b);
		colorMixer.draw(tb_bVal);
		colorMixer.draw(tb_a);
		colorMixer.draw(tb_aVal);
		colorMixer.draw(bar_r);
		colorMixer.draw(bar_g);
		colorMixer.draw(bar_b);
		colorMixer.draw(bar_a);
		colorMixer.draw(crcl_red);
		colorMixer.draw(crcl_green);
		colorMixer.draw(crcl_blue);
		colorMixer.draw(crcl_alpha);
		colorMixer.draw(rect_newCol);
		colorMixer.draw(rect_currCol);
		colorMixer.display();
	}
}

void line_action(sf::RenderWindow& artBoard, sf::Event& evnt)
{
	//if((int)vertices[lines_number].getVertexCount() > 1)
	sf::Color guide_col = curr_col;
	guide_col.a = curr_col.a / 2;

	if (evnt.type == sf::Event::MouseButtonPressed)
	{
		if (undo_count > 0) {
			while (undo_count) {
				vertices.pop_back();
				--lines_number;
				--undo_count;
			}
		}

		if (evnt.mouseButton.button == sf::Mouse::Left)
		{
			undo_count = 0;
			if (last_cleared) {
				vertices.clear();
				lines_number = -1;
				last_cleared = false;
			}

			vertices.push_back(sf::VertexArray(sf::TriangleStrip, 4));
			lines_number++;
			//printf("Current line number %d vector size %d\n", lines_number, vertices.size());
			first_position = (sf::Vector2f)sf::Mouse::getPosition(artBoard);
			mousePressedDown = true;
		}
	}

	if (evnt.type == sf::Event::MouseButtonReleased)
	{
		if (evnt.mouseButton.button == sf::Mouse::Left)
		{
			mousePressedDown = false;
			last_Mouse_pos.x = 0;
			last_Mouse_pos.y = 0;
		}
	}

	if (mousePressedDown)
	{
		if (last_Mouse_pos != sf::Mouse::getPosition(artBoard))
		{
			rectangleConnect((sf::Vector2f)sf::Mouse::getPosition(artBoard), first_position, brushSize, guide_col, 0);
			rectangleConnect(first_position, (sf::Vector2f)sf::Mouse::getPosition(artBoard), brushSize, guide_col, 1);
			last_Mouse_pos = sf::Mouse::getPosition();
		}
	}
	if (evnt.type == sf::Event::MouseButtonReleased)
	{
		rectangleConnect((sf::Vector2f)sf::Mouse::getPosition(artBoard), first_position, brushSize, curr_col, 0);
		rectangleConnect(first_position, (sf::Vector2f)sf::Mouse::getPosition(artBoard), brushSize, curr_col, 1);
	}
}

float brushSize_action(sf::Vector2i mouse_pos, float current)
{
	int x, y;
	float size = current;

	sf::RenderWindow sizePicker(sf::VideoMode(80, 30), "", sf::Style::None);
	sf::Texture tex_sizePicker;
	sf::Sprite spt_sizePicker;
	sf::Event evnt;

	tex_sizePicker.loadFromFile("./Resources/img/size_icons.png");
	spt_sizePicker.setTexture(tex_sizePicker);

	sizePicker.setPosition(mouse_pos);

	while (sizePicker.isOpen())
	{
		x = sf::Mouse::getPosition(sizePicker).x;
		y = sf::Mouse::getPosition(sizePicker).y;

		if (x < 0 || y < 0 || x > 80 || y > 30)
		{
			sizePicker.close();
			break;
		}

		while (sizePicker.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::MouseButtonPressed)
			{
				if (evnt.mouseButton.button == sf::Mouse::Left)
				{
					if (x >= 0 && x < 26 && y >= 0 && y < 30)
					{
						size = 4.0;
					}
					else if (x >= 26 && x < 53 && y >= 0 && y < 30)
					{
						size = 8.0;
					}
					else if (x >= 53 && x < 80 && y >= 0 && y < 30)
					{
						size = 10.5;
					}
					sizePicker.close();
				}
			}
		}
		sizePicker.clear(sf::Color(50, 50, 50));
		sizePicker.draw(spt_sizePicker);
		sizePicker.display();
	}
	return size;
}

void rectangle_action(sf::RenderWindow& artBoard, sf::Event& evnt)
{
	sf::Color guide_col = curr_col;
	guide_col.a = curr_col.a / 4;

	sf::Vector2f pos0, pos1, pos2, pos3, apos0, aapos0, apos1, apos2, aapos2, apos3, aapos3;

	if (evnt.type == sf::Event::MouseButtonPressed)
	{
		if (undo_count > 0) {
			while (undo_count) {
				vertices.pop_back();
				--lines_number;
				--undo_count;
			}
		}

		if (evnt.mouseButton.button == sf::Mouse::Left)
		{
			undo_count = 0;
			if (last_cleared) {
				vertices.clear();
				lines_number = -1;
				last_cleared = false;
			}

			vertices.push_back(sf::VertexArray(sf::TriangleStrip, 16));
			lines_number++;
			first_position = sf::Vector2f(sf::Mouse::getPosition(artBoard));
			//vertices[lines_number][0] = sf::Vertex(getCoordinates((sf::Vector2f)sf::Mouse::getPosition(artBoard)), guide_col);
			mousePressedDown = true;
		}
	}

	if (mousePressedDown)
	{
		if (last_Mouse_pos != sf::Mouse::getPosition(artBoard))
		{
			pos2 = (sf::Vector2f)sf::Mouse::getPosition(artBoard);
			pos0 = first_position;
			pos1.x = pos2.x; pos1.y = pos0.y;
			pos3.x = pos0.x; pos3.y = pos2.y;

			apos0.x = pos0.x - 2 * brushSize; apos0.y = pos0.y;
			apos1.x = pos1.x; apos1.y = pos1.y + brushSize;
			apos2.x = pos2.x; apos2.y = pos2.y + brushSize;
			aapos2.x = pos2.x - 2 * brushSize, aapos2.y = pos2.y;
			apos3.x = pos3.x - 2 * brushSize, apos3.y = pos3.y;
			aapos3.x = pos3.x; aapos3.y = apos3.y - brushSize;
			aapos0.x = pos0.x; aapos0.y = apos0.y + brushSize;

			rectangleConnect(apos0, pos1, brushSize, guide_col, 0);
			rectangleConnect(pos1, apos0, brushSize, guide_col, 1);
			rectangleConnect(apos1, apos2, brushSize, guide_col, 2);
			rectangleConnect(apos2, apos1, brushSize, guide_col, 3);
			rectangleConnect(aapos2, apos3, brushSize, guide_col, 4);
			rectangleConnect(apos3, aapos2, brushSize, guide_col, 5);
			rectangleConnect(aapos3, aapos0, brushSize, guide_col, 6);
			rectangleConnect(aapos0, aapos3, brushSize, guide_col, 7);

			last_Mouse_pos = sf::Mouse::getPosition();
		}
	}
	if (evnt.type == sf::Event::MouseButtonReleased)
	{
		if (evnt.mouseButton.button == sf::Mouse::Left) {
			mousePressedDown = false;
			last_Mouse_pos.x = 0;
			last_Mouse_pos.y = 0;
			pos2 = (sf::Vector2f)sf::Mouse::getPosition(artBoard);
			pos0 = first_position;
			pos1.x = pos2.x; pos1.y = pos0.y;
			pos3.x = pos0.x; pos3.y = pos2.y;

			apos0.x = pos0.x - 2 * brushSize; apos0.y = pos0.y;
			apos1.x = pos1.x; apos1.y = pos1.y + brushSize;
			apos2.x = pos2.x; apos2.y = pos2.y + brushSize;
			aapos2.x = pos2.x - 2 * brushSize, aapos2.y = pos2.y;
			apos3.x = pos3.x - 2 * brushSize, apos3.y = pos3.y;
			aapos3.x = pos3.x; aapos3.y = apos3.y - brushSize;
			aapos0.x = pos0.x; aapos0.y = apos0.y + brushSize;

			rectangleConnect(apos0, pos1, brushSize, curr_col, 0);
			rectangleConnect(pos1, apos0, brushSize, curr_col, 1);
			rectangleConnect(apos1, apos2, brushSize, curr_col, 2);
			rectangleConnect(apos2, apos1, brushSize, curr_col, 3);
			rectangleConnect(aapos2, apos3, brushSize, curr_col, 4);
			rectangleConnect(apos3, aapos2, brushSize, curr_col, 5);
			rectangleConnect(aapos3, aapos0, brushSize, curr_col, 6);
			rectangleConnect(aapos0, aapos3, brushSize, curr_col, 7);
		}
	}
}

void circle_action(sf::RenderWindow& artBoard, sf::Event& evnt)
{
	sf::Color guide_col = curr_col;
	guide_col.a = curr_col.a / 3;

	if (evnt.type == sf::Event::MouseButtonPressed)
	{
		if (undo_count > 0) {
			while (undo_count) {
				vertices.pop_back();
				--lines_number;
				--undo_count;
			}
		}

		if (evnt.mouseButton.button == sf::Mouse::Left)
		{
			undo_count = 0;
			if (last_cleared) {
				vertices.clear();
				lines_number = -1;
				last_cleared = false;
			}

			vertices.push_back(sf::VertexArray(sf::TriangleStrip));
			lines_number++;
			firstPoint = sf::Vector2f(sf::Mouse::getPosition(artBoard));
			//firstPoint = getCoordinates(firstPoint);
			mousePressedDown = true;
		}
	}

	vertices[lines_number].setPrimitiveType(sf::PrimitiveType::TriangleStrip);

	if (mousePressedDown)
	{
		if (last_Mouse_pos != sf::Mouse::getPosition(artBoard))
		{
			sf::Vector2f curr_pos = sf::Vector2f(sf::Mouse::getPosition(artBoard));
			float radius = 0.5f * sqrt((curr_pos.x - firstPoint.x) * (curr_pos.x - firstPoint.x) + (curr_pos.y - firstPoint.y) * (curr_pos.y - firstPoint.y));
			//curr_pos = getCoordinates(curr_pos);
			sf::Vector2f center;
			center.x = firstPoint.x + 0.5f * (curr_pos.x - firstPoint.x);
			center.y = firstPoint.y + 0.5f * (curr_pos.y - firstPoint.y);
			//center = getCoordinates(center);
			circleConnect(center, radius, guide_col);
			last_Mouse_pos = sf::Mouse::getPosition();
		}
	}

	if (evnt.type == sf::Event::MouseButtonReleased)
	{
		if (evnt.mouseButton.button == sf::Mouse::Left) {
			last_Mouse_pos.x = 0;
			last_Mouse_pos.y = 0;
			mousePressedDown = false;
			sf::Vector2f curr_pos = sf::Vector2f(sf::Mouse::getPosition(artBoard));
			float radius = 0.5f * sqrt((curr_pos.x - firstPoint.x) * (curr_pos.x - firstPoint.x) + (curr_pos.y - firstPoint.y) * (curr_pos.y - firstPoint.y));
			//curr_pos = getCoordinates(curr_pos);
			sf::Vector2f center;
			center.x = firstPoint.x + 0.5f * (curr_pos.x - firstPoint.x);
			center.y = firstPoint.y + 0.5f * (curr_pos.y - firstPoint.y);
			//center = getCoordinates(center);
			circleConnect(center, radius, curr_col);
		}
	}
}