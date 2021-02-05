#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
public:
	Textbox() { }

	Textbox(sf::Font& font, sf::Vector2f pos, int size, sf::Color color, int lim, bool sel)
	{
		textbox.setFont(font);
		textbox.setPosition(pos);
		textbox.setCharacterSize(size);
		textbox.setFillColor(color);
		isSelected = sel;
		limit = lim;
		if (sel)
		{
			textbox.setString("_");
		}
		else
		{
			textbox.setString("");
		}
	}
	void selected(bool sel)
	{
		isSelected = sel;
		if (sel)
		{
			textbox.setString(text.str() + '_');
		}
		else
		{
			textbox.setString(text.str());
		}
	}

	std::string getText()
	{
		return text.str();
	}

	void setText(std::string txt)
	{
		text.str(txt);
		textbox.setString(text.str());
	}

	void drawTo(sf::RenderWindow& window)
	{
		window.draw(textbox);
	}

	void typedOn(sf::Event input)
	{
		if (isSelected)
		{
			int ch = input.text.unicode;
			if (ch < 123)
			{
				if (text.str().length() < (size_t)limit)
				{
					typeText(ch);
				}
				else if (text.str().length() >= 4 && ch == DELETE_KEY)
				{
					backspace();
				}
			}
		}
	}

private:
	sf::Text textbox;
	std::ostringstream text;
	bool isSelected = false;
	int limit;

	void typeText(int ch)
	{
		if (ch == DELETE_KEY)
		{
			if (text.str().length() > 0)
			{
				backspace();
			}
		}
		//else if (ch == ENTER_KEY)
		//{
		//	//selected(false);
		//}
		//else if (ch == ESCAPE_KEY)
		//{
		//}
		else if (ch < 123)
		{
			text << (char)ch;
		}
		textbox.setString(text.str() + '_');
	}

	void backspace()
	{
		std::string temp = text.str();
		temp.pop_back();
		text.str("");
		text << temp;
		textbox.setString(text.str() + '_');
	}
};