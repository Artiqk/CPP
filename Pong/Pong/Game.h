#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"

class Game {
private:
	sf::RenderWindow mWindow;
	sf::RectangleShape midLine;
public:
	Game();
	void run();
	void BallOutOfField(Ball &ball);
	static bool DetectPaddleCollision(Ball ball, Paddle paddle);
	static bool DetectWallCollision(Ball ball);
	static float getHitPos(Paddle pad, Ball ball);
};