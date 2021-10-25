#include <SFML/Graphics.hpp>
#include <cmath>
#include "gameTile.h"
#include <cstdlib>
#include <ctime>



int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	float level = 0.41;
	float level_increment = 0.04;
	float level_max = 0.41;
	int scale = 20;
	int const gridlen = 30;
	int x_temp = round(gridlen / 2);
	int y_temp = round(gridlen / 2);
	int temp;
	int temp2;
	int snakelen;
	int food;
	bool start = false;
	bool keypressflag = false;
	bool foodgeneratorflag = true;
	float x_temp2;
	float y_temp2;
	float color_temp;
	enum Direction {
		UP = 3,
		RIGHT = -4,
		LEFT = 4,
		DOWN = -3,

	}D = UP;
	Direction D_prev = UP;
	sf::RenderWindow window(sf::VideoMode(scale * gridlen, scale * gridlen), "snek");
	
	GameTile tail[gridlen * gridlen];
	int snake[gridlen * gridlen];
	for (int i = 0; i < gridlen; i++) {
		for (int j = 0; j < gridlen; j++) {

			tail[i * gridlen + j].a.setSize(sf::Vector2f(scale, scale));
			tail[i * gridlen + j].a.setFillColor(sf::Color(200, 100, 50));
			tail[i * gridlen + j].a.setPosition(sf::Vector2f(i * scale + 1, j * scale + 1));
			tail[i * gridlen + j].isFood = false;
			tail[i * gridlen + j].isSnake = false;
		}
	}

	snake[0] = x_temp * gridlen + y_temp;
	snake[1] = x_temp * gridlen + y_temp + 1;
	snake[2] = x_temp * gridlen + y_temp + 2;

	tail[snake[0]].isSnake = true;
	tail[snake[1]].isSnake = true;
	tail[snake[2]].isSnake = true;
	snakelen = 3;
	food = rand() % (gridlen * gridlen);
	for (int i = 0; i < snakelen; i++) {
		while (food == snake[i]) {
			food = rand() % (gridlen * gridlen);
		}
	}

	tail[food].isFood = true;






	sf::Time elapsed;
	sf::Clock clock;


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		elapsed = clock.getElapsedTime();
		if (start == false) {
			sf::RectangleShape background;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&!keypressflag)
			{
				keypressflag = true;
				level = level - level_increment;
				if (level < level_increment) {
					level = level_increment;
				}


			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !keypressflag)
			{
				keypressflag = true;
				level = level + level_increment;
				if (level > level_max) {
					level = level_max;
				}


			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				keypressflag = false;

			}
			color_temp = (level - level_increment) * 255 / level_max;
			background.setFillColor(sf::Color(color_temp, color_temp, color_temp));
			

			background.setSize(sf::Vector2f(scale * gridlen, scale * gridlen));
			sf::RectangleShape shape;
			sf::CircleShape triangle(scale*1.5, 3);
			triangle.setFillColor(sf::Color(color_temp, color_temp, color_temp));
			shape.setFillColor(sf::Color(0,0,255));
			shape.setSize(sf::Vector2f(scale*4, scale*4));
			shape.setOrigin(sf::Vector2f((-scale*gridlen/2)+scale*2, (-scale * gridlen / 2) + scale * 2));

			triangle.setPosition(sf::Vector2f((scale*gridlen/2)-scale*2.35, (scale*gridlen/2)-scale*0.5));
			triangle.setRotation(-30);
			window.draw(background);
			window.draw(shape);
			window.draw(triangle);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				
				start = true;
			}

			window.display();
			
			window.clear();
		}
		else {
			if (elapsed >= sf::seconds(level)) {
				for (int i = snakelen; i > 0; i--) {
					snake[i] = snake[i - 1];
				}

				if ((!((snake[0] - (D % 3 * gridlen + D % 2) + 1) % (gridlen))) && D == UP) {
					snake[0] = snake[0] + gridlen;
				}
				if ((!((snake[0] - (D % 3 * gridlen + D % 2)) % (gridlen))) && D == DOWN) {
					snake[0] = snake[0] - gridlen;
				}
				if ((snake[0] - (D % 3 * gridlen + D % 2)) > (gridlen * gridlen)) {
					snake[0] = snake[0] % gridlen - gridlen;
				}
				if ((snake[0] - (D % 3 * gridlen + D % 2)) < 0) {
					snake[0] = snake[0] + ((D % 3) * gridlen + D % 2) + gridlen * (gridlen - 1);
				}
				snake[0] = snake[0] - (D % 3 * gridlen + D % 2);


				if (snake[0] == food) {
					while (foodgeneratorflag) {
						food = rand() % (gridlen * gridlen);
						for (int i = 0; i < snakelen; i++) {
							if (snake[i] == food) {
								foodgeneratorflag = true;
								break;
							}
							foodgeneratorflag = false;
						}
					}
					foodgeneratorflag = true;
				}
				tail[food].isFood = true;

				for (int i = 1; i < snakelen; i++) {
					if (snake[i] == snake[0]) {
						D = UP;
						D_prev = UP;
						for (int i = 0; i < gridlen; i++) {
							for (int j = 0; j < gridlen; j++) {

								tail[i * gridlen + j].a.setSize(sf::Vector2f(scale, scale));
								tail[i * gridlen + j].a.setFillColor(sf::Color(200, 100, 50));
								tail[i * gridlen + j].a.setPosition(sf::Vector2f(i * scale + 1, j * scale + 1));
								tail[i * gridlen + j].isFood = false;
								tail[i * gridlen + j].isSnake = false;
							}
						}

						snake[0] = x_temp * gridlen + y_temp;
						snake[1] = x_temp * gridlen + y_temp + 1;
						snake[2] = x_temp * gridlen + y_temp + 2;

						tail[snake[0]].isSnake = true;
						tail[snake[1]].isSnake = true;
						tail[snake[2]].isSnake = true;
						snakelen = 3;
						food = rand() % (gridlen * gridlen);
						for (int i = 0; i < snakelen; i++) {
							while (food == snake[i]) {
								food = rand() % (gridlen * gridlen);
							}
							tail[food].isFood = true;
						}
					}

				}
				if (tail[snake[snakelen]].isFood && tail[snake[snakelen]].isSnake) {
					tail[snake[snakelen]].isFood = false;
					snakelen++;
				}
				for (int i = 0; i < gridlen * gridlen; i++)
				{
					tail[i].isSnake = false;
				}
				for (int i = 0; i < snakelen; i++)
				{
					tail[snake[i]].isSnake = true;
				}




				D_prev = D;
				clock.restart();

			}
			window.clear();
			color_temp = 0;
			for (int i = 0; i < gridlen * gridlen; i++) {
				
				if (tail[i].isFood == true) {
					tail[i].a.setFillColor(sf::Color(250, 150, 100));
					window.draw(tail[i].a);
				}
				if (tail[i].isSnake == true) {

					tail[i].a.setFillColor(sf::Color(color_temp, color_temp, 255));
					color_temp = color_temp + 255 / snakelen;
					window.draw(tail[i].a);
				}

			}
			window.display();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				start = false;
			}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (D_prev != RIGHT) {
					D = LEFT;

				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				if (D_prev != DOWN) {
					D = UP;

				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (D_prev != LEFT) {
					D = RIGHT;

				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (D_prev != UP) {
					D = DOWN;

				}
			}
		}
	}
	return 0;
}