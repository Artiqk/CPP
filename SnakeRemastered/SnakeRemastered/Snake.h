#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Fruit.h"

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3

sf::Vector2f Fruit::fruitPos;

class Snake {
private:
	int tail, scl, dir;
	std::vector<sf::RectangleShape> snk;
	sf::RectangleShape snake;
	std::vector<sf::Vector2f> tailPos;
	sf::Vector2f tailP;
	sf::RenderWindow* win;

public:
	Snake(sf::RenderWindow* window) {
		win = window;
		tail = 3;
		scl = 20;
		dir = 0;

		snake.setFillColor(sf::Color::Black);
		snake.setSize(sf::Vector2f(1, 1));
		snake.setScale(sf::Vector2f(scl, scl));

		for (int i = 0; i < tail; i++) {
			snk.push_back(snake);
			tailPos.push_back(tailP);
		}
	}

	~Snake() {
		snk.clear();
		tailPos.clear();
		tail = 0;
		std::cout << "Game over !" << std::endl;
		system("pause");
		exit(EXIT_SUCCESS);
	}

	//Add something to slow down time w/o modif FPS

	void update(bool* isEaten) {
		if (eat())
			*isEaten = true;
		else
			*isEaten = false;

		for (int i = 0; i < snk.size(); i++) {
			tailPos[i].x = snk[i].getPosition().x;
			tailPos[i].y = snk[i].getPosition().y;
		}

		this->move();

		for (int i = 1; i < tail; i++) {
			snk[i].setPosition(sf::Vector2f(tailPos[i - 1].x, tailPos[i - 1].y));
		}

		tailBite();

		for(int i = 0; i < snk.size(); i++)
			win->draw(snk[i]);
	}

	void keyDirection() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (dir == LEFT)
				dir = LEFT;
			else
				dir = RIGHT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (dir == RIGHT)
				dir = RIGHT;
			else
				dir = LEFT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (dir == DOWN)
				dir = DOWN;
			else
				dir = UP;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (dir == UP)
				dir = UP;
			else
				dir = DOWN;
		}
	}

	void wallLoopback() { //Bug --> Snake skip 1 block (eg. -20 -> 560)
		if (snk[0].getPosition().x == win->getSize().x) {
			snk[0].setPosition(sf::Vector2f(0, snk[0].getPosition().y));
		}
		else if (snk[0].getPosition().x == (0 - scl)) {
			snk[0].setPosition(sf::Vector2f(win->getSize().x - scl, snk[0].getPosition().y));
		}
		if (snk[0].getPosition().y == win->getSize().y) {
			snk[0].setPosition(sf::Vector2f(snk[0].getPosition().x, 0));
		}
		else if (snk[0].getPosition().y == (0 - scl)) {
			snk[0].setPosition(sf::Vector2f(snk[0].getPosition().x, win->getSize().y - scl));
		}
	}

	void tailBite() {
		for (int i = 1; i < snk.size(); i++) {
			if (snk[0].getPosition().x == snk[i].getPosition().x && snk[0].getPosition().y == snk[i].getPosition().y) {
				delete this;
			}
		}
	}

	void move() {
		this->keyDirection();
		if (dir == RIGHT)
			snk[0].move(1 * scl, 0);
		else if (dir == LEFT)
			snk[0].move(-1 * scl, 0);
		else if (dir == UP)
			snk[0].move(0, -1 * scl);
		else if (dir == DOWN)
			snk[0].move(0, 1 * scl);
		this->wallLoopback();
	}

	void snakePosDebug() {
		std::cout << snk[0].getPosition().x << ":" << snk[0].getPosition().y << std::endl;
		std::cout << "Size: " << snk.size() << std::endl;
	}

	bool eat() {
		if (snk[0].getPosition().x == Fruit::fruitPos.x && snk[0].getPosition().y == Fruit::fruitPos.y) {
			this->grow();
			return true;
		}
		else {
			return false;
		}
	}

	void grow() {
		snk.push_back(snake);
		tailPos.push_back(tailP);
		tail += 1;
	}
};