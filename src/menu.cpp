#include "global.hpp"

sf::RectangleShape bar;
sf::Text t_open, t_new, t_save, t_saveas, t_changebg, t_exit;
sf::RectangleShape b_new(sf::Vector2f(124.f, 30.f));
sf::RectangleShape b_open(sf::Vector2f(58.f, 30.f));
sf::RectangleShape b_save(sf::Vector2f(60.f, 30.f));
sf::RectangleShape b_saveas(sf::Vector2f(79.f, 30.f));
sf::RectangleShape b_changebg(sf::Vector2f(178.f, 30.f));
sf::RectangleShape b_exit(sf::Vector2f(50.f, 30.f));

int menuMouseX, menuMouseY;

bool saved = false;

void init_menu(sf::RenderWindow& artBoard)
{
	bar.setSize(sf::Vector2f((float)artBoardWidth, 30.f));
	bar.setPosition(0.0f, 0.0f);
	bar.setFillColor(sf::Color(105, 105, 105));
	artBoard.draw(bar);

	int fsize = 17;

	sf::Text t_open, t_new, t_save, t_saveas, t_changebg, t_exit;

	t_open.setFont(font_arial); t_open.setFillColor(sf::Color::White); t_open.setString("Open");
	t_new.setFont(font_arial); t_new.setFillColor(sf::Color::White); t_new.setString("Create New");
	t_changebg.setFont(font_arial); t_changebg.setFillColor(sf::Color::White); t_changebg.setString("Change Background");
	t_save.setFont(font_arial); t_save.setFillColor(sf::Color::White); t_save.setString("Save");
	t_saveas.setFont(font_arial); t_saveas.setFillColor(sf::Color::White); t_saveas.setString("Save as");
	t_exit.setFont(font_arial); t_exit.setFillColor(sf::Color::White); t_exit.setString("Exit");
	t_new.setCharacterSize(fsize);
	t_open.setCharacterSize(fsize);
	t_save.setCharacterSize(fsize);
	t_saveas.setCharacterSize(fsize);
	t_changebg.setCharacterSize(fsize);
	t_exit.setCharacterSize(fsize);
	t_new.setPosition(20.f, 2.5f);
	t_open.setPosition(130.f, 2.5f);
	t_save.setPosition(190.f, 2.5f);
	t_saveas.setPosition(250.f, 2.5f);
	t_changebg.setPosition(330.f, 2.5f);
	t_exit.setPosition(510.f, 2.5f);

	b_new.setPosition(0.f, 0.f); b_new.setFillColor(sf::Color(105, 105, 105));
	b_open.setPosition(125.f, 0.f); b_open.setFillColor(sf::Color(105, 105, 105));
	b_save.setPosition(184.f, 0.f); b_save.setFillColor(sf::Color(105, 105, 105));
	b_saveas.setPosition(245.f, 0.f); b_saveas.setFillColor(sf::Color(105, 105, 105));
	b_changebg.setPosition(325.f, 0.f); b_changebg.setFillColor(sf::Color(105, 105, 105));
	b_exit.setPosition(504.f, 0.f); b_exit.setFillColor(sf::Color(105, 105, 105));

	menuMouseX = sf::Mouse::getPosition(artBoard).x;
	menuMouseY = sf::Mouse::getPosition(artBoard).y;

	if (menuMouseX >= 0 && menuMouseX < 125 && menuMouseY >= 0 && menuMouseY < 30)
	{
		b_new.setFillColor(sf::Color(70, 70, 70));
	}
	else if (menuMouseX >= 125 && menuMouseX < 184 && menuMouseY >= 0 && menuMouseY < 30)
	{
		b_open.setFillColor(sf::Color(70, 70, 70));
	}
	else if (menuMouseX >= 184 && menuMouseX < 245 && menuMouseY >= 0 && menuMouseY < 30)
	{
		b_save.setFillColor(sf::Color(70, 70, 70));
	}
	else if (menuMouseX >= 245 && menuMouseX < 325 && menuMouseY >= 0 && menuMouseY < 30)
	{
		b_saveas.setFillColor(sf::Color(70, 70, 70));
	}
	else if (menuMouseX >= 325 && menuMouseX < 504 && menuMouseY >= 0 && menuMouseY < 30)
	{
		b_changebg.setFillColor(sf::Color(70, 70, 70));
	}
	else if (menuMouseX >= 504 && menuMouseX < 555 && menuMouseY >= 0 && menuMouseY < 30)
	{
		b_exit.setFillColor(sf::Color(70, 70, 70));
	}

	artBoard.draw(b_new);
	artBoard.draw(b_open);
	artBoard.draw(b_save);
	artBoard.draw(b_saveas);
	artBoard.draw(b_changebg);
	artBoard.draw(b_exit);
	artBoard.draw(t_new);
	artBoard.draw(t_open);
	artBoard.draw(t_save);
	artBoard.draw(t_saveas);
	artBoard.draw(t_changebg);
	artBoard.draw(t_exit);
}

void menu_action(sf::RenderWindow& artBoard, sf::Event& evnt)
{
	menuMouseX = sf::Mouse::getPosition(artBoard).x;
	menuMouseY = sf::Mouse::getPosition(artBoard).y;

	if (evnt.type == sf::Event::MouseButtonPressed)
	{
		if (evnt.mouseButton.button == sf::Mouse::Left)
		{
			if (menuMouseX >= 0 && menuMouseX < 125 && menuMouseY >= 0 && menuMouseY < 30)
			{
				//Create New
				if (!open())
				{
					init_artBoard();
				}
				mousePressedDown = false;
			}
			else if (menuMouseX >= 125 && menuMouseX < 184 && menuMouseY >= 0 && menuMouseY < 30)
			{
				//Open
				fileLocation = import();
				if (fileLocation != "")
				{
					fileLocation = "./art/" + fileLocation + ".png";
					init_artBoard();
				}
				mousePressedDown = false;
			}
			else if (menuMouseX >= 184 && menuMouseX < 245 && menuMouseY >= 0 && menuMouseY < 30)
			{
				//Save
				if (!saved)
				{
					save(artBoard);
					saved = true;
				}
				else
				{
					if (!normal_save(artBoard))
					{
						std::cout << "Failed to save!\n";
					}
				}
				mousePressedDown = false;
			}
			else if (menuMouseX >= 245 && menuMouseX < 325 && menuMouseY >= 0 && menuMouseY < 30)
			{
				//Save as
				saved = true;
				save(artBoard);
				mousePressedDown = false;
			}
			else if (menuMouseX >= 325 && menuMouseX < 504 && menuMouseY >= 0 && menuMouseY < 30)
			{
				//Change Background
				mousePressedDown = false;
				bg_col = colorMixer_action(sf::Mouse::getPosition(), bg_col);
			}
			else if (menuMouseX >= 504 && menuMouseX < 555 && menuMouseY >= 0 && menuMouseY < 30)
			{
				//Exit
				if (save(artBoard) != -1)
				{
					artBoard.close();
				}
			}
		}
	}
}