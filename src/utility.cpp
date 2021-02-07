#include "global.hpp"
#include <queue>

float pi = (float)acos(-1);

void canvas_draw(sf::RenderWindow& artBoard)
{
	//std::cout << "Currently drawing\n";
	if (!last_cleared)
	{
		for (auto i = 0; i < (int)vertices.size() - undo_count; i++)
		{
			artBoard.draw(vertices[i]);
		}
	}
}

void mouseToggle(sf::Event& evnt)
{
	if (evnt.type == sf::Event::MouseButtonPressed)
	{
		if (undo_count > 0)
		{
			while (undo_count)
			{
				vertices.pop_back();
				--lines_number;
				--undo_count;
			}
		}

		if (evnt.mouseButton.button == sf::Mouse::Left)
		{
			undo_count = 0;
			if (last_cleared)
			{
				vertices.clear();
				lines_number = -1;
				last_cleared = false;
			}

			if (penSelected || brushSelected || eraserSelected)
			{
				vertices.push_back(sf::VertexArray(sf::TriangleStrip));
				lines_number++;
			}

			mousePressedDown = true;
		}
	}
	if (evnt.type == sf::Event::MouseButtonReleased)
	{
		if (evnt.mouseButton.button == sf::Mouse::Left)
		{
			mousePressedDown = false;
		}
	}
}

void brushConnect(sf::Vector2i newPos, sf::Vector2i lastPos, float radius, sf::Color col)
{
	float curr_slope, mult;

	if (newPos.y != lastPos.y)
	{
		curr_slope = -(float)(newPos.x - lastPos.x) / (newPos.y - lastPos.y);
		mult = sqrt((radius * radius) / (curr_slope * curr_slope + 1));

		vertices[lines_number].append(sf::Vertex(getCoordinates({ newPos.x + mult, newPos.y + curr_slope * mult }), col));
		vertices[lines_number].append(sf::Vertex(getCoordinates({ newPos.x - mult, newPos.y - curr_slope * mult }), col));
	}

	else
	{
		curr_slope = 1; // m = 1/0
		vertices[lines_number].append(sf::Vertex(getCoordinates({ newPos.x + radius, newPos.y - radius }), col));
		vertices[lines_number].append(sf::Vertex(getCoordinates({ newPos.x + radius, newPos.y + radius }), col));
	}
}

void rectangleConnect(sf::Vector2f newPos, sf::Vector2f lastPos, float radius, sf::Color col, int pos)
{
	float curr_slope, mult;

	if (newPos.y != lastPos.y)
	{
		curr_slope = -(float)(newPos.x - lastPos.x) / (newPos.y - lastPos.y);
		mult = sqrt((radius * radius) / (curr_slope * curr_slope + 1));

		vertices[lines_number][pos * 2] = (sf::Vertex(getCoordinates({ newPos.x + mult, newPos.y + curr_slope * mult }), col));
		vertices[lines_number][pos * 2 + 1] = (sf::Vertex(getCoordinates({ newPos.x - mult, newPos.y - curr_slope * mult }), col));
	}

	else
	{
		curr_slope = 1; // m = 1/0
		vertices[lines_number][pos * 2] = (sf::Vertex(getCoordinates({ newPos.x + radius, newPos.y - radius }), col));
		vertices[lines_number][pos * 2 + 1] = (sf::Vertex(getCoordinates({ newPos.x + radius, newPos.y + radius }), col));
	}
}

void circleConnect(sf::Vector2f center, float radius, sf::Color col)
{
	sf::Vector2i newPos, oldPos, firstPos;
	//std::cout << center.x << " " << center.y << '\n';
	int points = (int)ceil(radius * 10);
	float degInc = 2 * pi / points;

	for (float degree = 0; degree < 2 * pi; degree += degInc) {
		float circle_x = radius * cos(degree);
		float circle_y = radius * sin(degree);
		sf::Vector2f point;
		point.x = center.x + circle_x;
		point.y = center.y + circle_y;
		newPos = (sf::Vector2i)point;

		if (degree == 0)
			firstPos = newPos;

		if (filledCircle)
		{
			vertices[lines_number].append(sf::Vertex(getCoordinates((sf::Vector2f)newPos), col));
		}

		else
		{
			if (degree != 0) {
				brushConnect(newPos, oldPos, brushSize, col);
				brushConnect(oldPos, newPos, brushSize, col);
			}
			oldPos = newPos;
		}
	}

	if (!filledCircle)
	{
		brushConnect(oldPos, firstPos, brushSize, col);
	}

	else
	{
		vertices[lines_number].append(sf::Vertex(getCoordinates((sf::Vector2f)firstPos), col));
	}
}

sf::Vector2f getCoordinates(sf::Vector2f oldCord)
{
	sf::Vector2f newCord;
	if (zoomSelected)
	{
		newCord.x = (oldCord.x / 3) + zoomCordX - artBoardWidth / 6;
		newCord.y = (oldCord.y / 3) + zoomCordY - artBoardHeight / 6;
	}
	else
	{
		newCord = oldCord;
	}
	return newCord;
}

sf::VertexArray fillSquare(sf::Vector2f center, float radius, sf::Color col)
{
	sf::VertexArray square;
	square.setPrimitiveType(sf::TriangleFan);
	square.append(sf::Vertex(getCoordinates(sf::Vector2f(center)), col));
	square.append(sf::Vertex(getCoordinates(sf::Vector2f(center.x - brushSize, center.y + brushSize)), col));
	square.append(sf::Vertex(getCoordinates(sf::Vector2f(center.x + brushSize, center.y + brushSize)), col));
	square.append(sf::Vertex(getCoordinates(sf::Vector2f(center.x + brushSize, center.y - brushSize)), col));
	square.append(sf::Vertex(getCoordinates(sf::Vector2f(center.x - brushSize, center.y - brushSize)), col));
	square.append(sf::Vertex(getCoordinates(sf::Vector2f(center.x - brushSize, center.y + brushSize)), col));

	return square;
}

void floodfill(sf::Vector2i start, const sf::Image& curr_state, const sf::Color& prevCol, sf::RenderWindow& artBoard)
{
	int x, y;
	sf::Vector2i cur;

	std::queue<sf::Vector2i> q;
	std::map <std::pair<int, int>, bool> mp;

	q.push(start);

	while (!q.empty())
	{
		cur = q.front();
		x = cur.x, y = cur.y;
		q.pop();
		//std::cout << x << " " << y << '\n';

		if (mp.size() > 9e5 + 10)
		{
			//bg_col = curr_col;
			vertices[lines_number].clear();
			break;
		}

		if (mp[{x, y}] == 1) {
			continue;
		}

		mp[{x, y}] = 1;

		if (x < 0 || x >= artBoardWidth || y < 0 || y >= artBoardHeight || curr_state.getPixel(x, y) != prevCol) {
			vertices[lines_number].append(sf::Vertex(getCoordinates((sf::Vector2f)start), curr_col));
			vertices[lines_number].append(sf::Vertex(getCoordinates({ (float)x, (float)y }), curr_col));
			continue;
		}

		q.push(sf::Vector2i{ x + 1,y });
		q.push(sf::Vector2i{ x ,y + 1 });
		q.push(sf::Vector2i{ x ,y - 1 });
		q.push(sf::Vector2i{ x - 1,y });
	}
}
void init_artBoard()
{
	if (fileLocation != "")
	{
		if (txtr_importedBackground.loadFromFile(fileLocation))
		{
			bgImported = true;
		}
		sprt_importedBackground.setTexture(txtr_importedBackground);
		artBoardWidth = txtr_importedBackground.getSize().x;
		artBoardHeight = txtr_importedBackground.getSize().y;
	}
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
	gradientSelected = false;
	eyedropperSelected = false;
	fileLocation = "";
	brushSize = 3.0;
	vertices.clear();
	vertices.push_back(sf::VertexArray());
	vertices[0].setPrimitiveType(sf::LineStrip);
	background.setSize(sf::Vector2f(artBoard.getSize()));
	background.setFillColor(bg_col);
}