#include "global.hpp"
#include <sstream>

#define BACKSPACE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

int save(sf::RenderWindow& artBoard) {
	int x, y;
	bool save = false;

	std::ostringstream text;
	sf::Font font;
	sf::Text textbox;

	sf::RenderWindow save_prompt(sf::VideoMode(280, 120), "Save?", sf::Style::Titlebar);
	sf::Sprite sprt_savePrompt;
	sf::Texture txtr_savePrompt;
	sf::RectangleShape btn_bg_save(sf::Vector2f(40.0f, 19.0f));
	sf::RectangleShape btn_bg_dontSave(sf::Vector2f(78.0f, 19.0f));
	sf::RectangleShape btn_bg_cancel(sf::Vector2f(53.0f, 19.0f));
	sf::RectangleShape bg_textField(sf::Vector2f(113.0f, 18.0f));

	txtr_savePrompt.loadFromFile("save_prompt.png");
	sprt_savePrompt.setTexture(txtr_savePrompt);

	btn_bg_save.setPosition(120.0f, 88.0f);
	btn_bg_dontSave.setPosition(8.0f, 88.0f);
	btn_bg_cancel.setPosition(217.0f, 88.0f);
	bg_textField.setPosition(145.0f, 46.0f);

	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "unable to load font\n";
	}
	textbox.setFont(font);
	textbox.setString(text.str() + "_");
	textbox.setCharacterSize(14);
	textbox.setPosition({ 148, 46 });
	textbox.setFillColor(sf::Color::Black);

	while (save_prompt.isOpen())
	{
		x = sf::Mouse::getPosition(save_prompt).x;
		y = sf::Mouse::getPosition(save_prompt).y;

		sf::Event evnt;
		while (save_prompt.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				save_prompt.close();
			}

			if (evnt.type == sf::Event::MouseButtonPressed)
			{
				if (evnt.mouseButton.button == sf::Mouse::Left)
				{
					if (x >= 8 && x <= 86 && y >= 88 && y <= 107) //Dont save
					{
						save_prompt.close();
						return 0;
					}
					if (x >= 120 && x <= 160 && y >= 88 && y <= 107) //save
					{
						save = true;
					}
					if (x >= 217 && x <= 270 && y >= 88 && y <= 107) //cancel
					{
						save_prompt.close();
						return -1;
					}
				}
			}
			if (evnt.type == sf::Event::TextEntered)
			{
				int ch = (char)evnt.text.unicode;
				int len = text.str().length();
				if (len < 12 && ch != BACKSPACE_KEY)
				{
					text << (char)evnt.text.unicode;
				}
				else if (ch == BACKSPACE_KEY)
				{
					if (len > 0)
					{
						std::string temp = text.str();
						temp.pop_back();
						text.str("");
						text << temp;
					}
				}
				textbox.setString(text.str() + "_");
			}
		}

		//handling button BGs
		if (x >= 8 && x <= 86 && y >= 88 && y <= 107)
		{
			btn_bg_dontSave.setFillColor(sf::Color(50, 50, 50));
		}
		else
		{
			btn_bg_dontSave.setFillColor(sf::Color(70, 70, 70));
		}
		if (x >= 120 && x <= 160 && y >= 88 && y <= 107)
		{
			btn_bg_save.setFillColor(sf::Color(50, 50, 50));
		}
		else
		{
			btn_bg_save.setFillColor(sf::Color(70, 70, 70));
		}
		if (x >= 217 && x <= 270 && y >= 88 && y <= 107)
		{
			btn_bg_cancel.setFillColor(sf::Color(50, 50, 50));
		}
		else
		{
			btn_bg_cancel.setFillColor(sf::Color(70, 70, 70));
		}
		bg_textField.setFillColor(sf::Color(200, 200, 200));

		//handling saving
		if (save)
		{
			sf::Texture texture;
			texture.create(artBoard.getSize().x, artBoard.getSize().y);
			texture.update(artBoard);
			if (texture.copyToImage().saveToFile(text.str() + ".png"))
			{
				std::cout << "Art saved to " << text.str() + ".png" << std::endl;
				save_prompt.close();
				return 0;
			}
			else
			{
				save_prompt.close();
				return -1;
			}
		}

		save_prompt.clear(sf::Color(60, 60, 60));
		save_prompt.draw(bg_textField);
		save_prompt.draw(btn_bg_dontSave);
		save_prompt.draw(btn_bg_save);
		save_prompt.draw(btn_bg_cancel);
		save_prompt.draw(sprt_savePrompt);
		save_prompt.draw(textbox);
		save_prompt.display();
	}
	return 0;
}