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
			if (last_Mouse_pos.x != 0 && last_Mouse_pos.y != 0)
				brushConnect(new_Mouse_pos, last_Mouse_pos, radius);
			last_Mouse_pos = new_Mouse_pos;
			//std::cout << "X Y : " << vertices[lines_number][vertices[lines_number].getVertexCount() - 1].position.x << " " << vertices[lines_number][vertices[lines_number].getVertexCount() - 1].position.y << std::endl;
		}

		//curr_col = sf::Color::Color(rand() % 255, rand() % 255, rand() % 255);
	}

	else if (!mousePressedDown && brushTap && vertices[lines_number].getVertexCount() == 0) {
		vertices[lines_number] = fillSquare((sf::Vector2f)last_Mouse_pos, brushSize, curr_col);
		brushTap = false;
	}

	else if (!mousePressedDown)
	{
		last_Mouse_pos.x = 0;
		last_Mouse_pos.y = 0;
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
		penTap = false;
	}

	if (!mousePressedDown)
	{
		last_Mouse_pos.x = 0;
		last_Mouse_pos.y = 0;
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

void colorMixer_action(sf::Vector2i mouse_pos)
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
	sf::Text tb_rVal(std::to_string((int)curr_col.r), font, 16);
	tb_rVal.setPosition({ 310, 8 });
	tb_rVal.setFillColor(sf::Color(180, 180, 180));

	sf::Text tb_g("G", font, 16);
	tb_g.setPosition({ 8, 33 });
	tb_g.setFillColor(sf::Color(180, 180, 180));
	sf::Text tb_gVal(std::to_string((int)curr_col.g), font, 16);
	tb_gVal.setPosition({ 310, 33 });
	tb_gVal.setFillColor(sf::Color(180, 180, 180));

	sf::Text tb_b("B", font, 16);
	tb_b.setPosition({ 8, 58 });
	tb_b.setFillColor(sf::Color(180, 180, 180));
	sf::Text tb_bVal(std::to_string((int)curr_col.b), font, 16);
	tb_bVal.setPosition({ 310, 58 });
	tb_bVal.setFillColor(sf::Color(180, 180, 180));

	sf::Text tb_a("A", font, 16);
	tb_a.setPosition({ 8, 83 });
	tb_a.setFillColor(sf::Color(180, 180, 180));
	sf::Text tb_aVal(std::to_string((int)curr_col.a), font, 16);
	tb_aVal.setPosition({ 310, 83 });
	tb_aVal.setFillColor(sf::Color(180, 180, 180));

	crcl_red.setPosition((float)curr_col.r + 30.0f, 10.0f);
	crcl_red.setOutlineThickness(2);
	crcl_red.setOutlineColor(sf::Color(200, 200, 200));
	crcl_red.setFillColor(sf::Color(curr_col.r, 0, 0, 255));

	crcl_green.setPosition((float)curr_col.g + 30.0f, 35.0f);
	crcl_green.setOutlineThickness(2);
	crcl_green.setOutlineColor(sf::Color(200, 200, 200));
	crcl_green.setFillColor(sf::Color(0, curr_col.g, 0, 255));

	crcl_blue.setPosition((float)curr_col.b + 30.0f, 60.0f);
	crcl_blue.setOutlineThickness(2);
	crcl_blue.setOutlineColor(sf::Color(200, 200, 200));
	crcl_blue.setFillColor(sf::Color(0, 0, curr_col.b, 255));

	crcl_alpha.setPosition((float)curr_col.a + 30.0f, 85.0f);
	crcl_alpha.setOutlineThickness(2);
	crcl_alpha.setOutlineColor(sf::Color(200, 200, 200));
	crcl_alpha.setFillColor(sf::Color(0, 0, 0, curr_col.a));

	rect_newCol.setPosition(350.0, 8.0);
	rect_newCol.setFillColor(new_col);

	rect_currCol.setPosition(350.0, 55.0);
	rect_currCol.setFillColor(curr_col);

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
			curr_col = new_col;
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
					curr_col = new_col;
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
				new_col.r = (int)sliderPos % 256;
				tb_rVal.setString(std::to_string((int)new_col.r));
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
				new_col.g = (int)sliderPos % 256;
				tb_gVal.setString(std::to_string((int)new_col.g));
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
				new_col.b = (int)sliderPos % 256;
				tb_bVal.setString(std::to_string((int)new_col.b));
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
				new_col.a = (int)sliderPos % 256;
				tb_aVal.setString(std::to_string((int)new_col.a));
			}
		}

		rect_newCol.setFillColor(new_col);

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

			vertices.push_back(sf::VertexArray(sf::LineStrip, 2));
			lines_number++;
			//printf("Current line number %d vector size %d\n", lines_number, vertices.size());
			vertices[lines_number][0] = sf::Vertex(getCoordinates((sf::Vector2f)sf::Mouse::getPosition(artBoard)), guide_col);
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
			vertices[lines_number][1] = sf::Vertex(getCoordinates((sf::Vector2f)sf::Mouse::getPosition(artBoard)), guide_col);
			last_Mouse_pos = sf::Mouse::getPosition();
		}
	}
	if (evnt.type == sf::Event::MouseButtonReleased)
	{
		vertices[lines_number][0].color.a = curr_col.a;
		vertices[lines_number][1] = sf::Vertex(getCoordinates((sf::Vector2f)sf::Mouse::getPosition(artBoard)), curr_col);
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

			vertices.push_back(sf::VertexArray(sf::LineStrip, 5));
			lines_number++;
			first_position = sf::Vector2f(sf::Mouse::getPosition(artBoard));
			vertices[lines_number][0] = sf::Vertex(getCoordinates((sf::Vector2f)sf::Mouse::getPosition(artBoard)), guide_col);
			mousePressedDown = true;
		}
	}

	if (mousePressedDown)
	{
		if (last_Mouse_pos != sf::Mouse::getPosition(artBoard))
		{
			vertices[lines_number][1] = sf::Vertex(getCoordinates({ (float)sf::Mouse::getPosition(artBoard).x, (float)first_position.y }), guide_col);
			vertices[lines_number][2] = sf::Vertex(getCoordinates((sf::Vector2f)sf::Mouse::getPosition(artBoard)), guide_col);
			vertices[lines_number][3] = sf::Vertex(getCoordinates({ (float)first_position.x, (float)sf::Mouse::getPosition(artBoard).y }), guide_col);
			vertices[lines_number][4] = vertices[lines_number][0];

			last_Mouse_pos = sf::Mouse::getPosition();
		}
	}
	if (evnt.type == sf::Event::MouseButtonReleased)
	{
		if (evnt.mouseButton.button == sf::Mouse::Left) {
			mousePressedDown = false;
			last_Mouse_pos.x = 0;
			last_Mouse_pos.y = 0;
			vertices[lines_number][0].color.a = curr_col.a;
			vertices[lines_number][1] = sf::Vertex(getCoordinates({ (float)sf::Mouse::getPosition(artBoard).x, first_position.y }), curr_col);
			vertices[lines_number][2] = sf::Vertex(getCoordinates((sf::Vector2f)sf::Mouse::getPosition(artBoard)), curr_col);
			vertices[lines_number][3] = sf::Vertex(getCoordinates({ first_position.x, (float)sf::Mouse::getPosition(artBoard).y }), curr_col);
			vertices[lines_number][4] = vertices[lines_number][0];
		}
	}
}

void circle_action(sf::RenderWindow& artBoard, sf::Event& evnt)
{
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

			vertices.push_back(sf::VertexArray(sf::LineStrip));
			lines_number++;
			firstPoint = sf::Vector2f(sf::Mouse::getPosition(artBoard));
			//firstPoint = getCoordinates(firstPoint);
			mousePressedDown = true;
		}
	}

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