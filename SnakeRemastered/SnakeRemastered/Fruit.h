#pragma once
#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

class Fruit {
private:
	int scl;
	sf::RectangleShape fruit;
	sf::RenderWindow* win;
public:
	static sf::Vector2f fruitPos;

	Fruit(sf::RenderWindow* window) {
		win = window;
		scl = 20;
		fruit.setFillColor(sf::Color::Red);
		fruit.setSize(sf::Vector2f(1, 1));
		fruit.setScale(sf::Vector2f(scl, scl));
		spawnFruit();
	}

	void spawnFruit() {
		srand(time(NULL));
		int randX = rand() % (win->getSize().x / scl);
		int randY = rand() % (win->getSize().y / scl);
		fruitPos.x = randX * scl;
		fruitPos.y = randY * scl;
		fruit.setPosition(fruitPos);
	}

	void update(bool isFruitEaten) {
		if (isFruitEaten)
			spawnFruit();

		win->draw(fruit);
	}

	void fruitPosDebug() {
		std::cout << "Fruit x : " << fruitPos.x << "\nFruit y : " << fruitPos.y << std::endl;
	}
};