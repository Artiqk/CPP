#pragma once
#include <SFML/Graphics.hpp>

class Ball {
private:
	sf::RectangleShape mBall;
public:
	sf::RenderWindow *bWindow;

	Ball();
	void show();
	void move(Paddle &pad, Paddle &pad2, Ball &ball);
	sf::Vector2f getPos();
	sf::Vector2f getHalf();
	void reset();

	static void debugVel();
};