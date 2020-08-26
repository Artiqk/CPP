#pragma once
class Ball;

#include <SFML/Graphics.hpp>

class Paddle {
private:
	sf::RectangleShape mPaddle;
public:
	sf::RenderWindow *pWindow;

	Paddle(bool player);
	void show();
	void move();

	//DEBUG
	sf::Vector2f getPos();
	sf::Vector2f getHalf(); 
};