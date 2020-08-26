#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Game.h"
#include "Paddle.h"
#include "Ball.h"

using namespace sf;

int score1 = 0;
int score2 = 0;

Paddle paddle(0);
Paddle ai(1);
Ball ball;

Game::Game() {
	this->midLine.setSize(Vector2f(10, 720));
	this->midLine.setFillColor(Color::White);
	this->midLine.setOrigin(Vector2f(midLine.getSize().x / 2, midLine.getSize().y / 2));
	this->midLine.setPosition(Vector2f(640, 360));
}

void Game::run() {
	this->mWindow.create(VideoMode(1280, 720), "Pong");
	this->mWindow.setFramerateLimit(60);

	paddle.pWindow	= &mWindow;
	ai.pWindow		= &mWindow;
	ball.bWindow	= &mWindow;

	while (this->mWindow.isOpen()) {
		Event event;

		while (this->mWindow.pollEvent(event)) {
			if (event.type == Event::Closed || event.key.code == Keyboard::Escape) {
				this->mWindow.close();
			}
		}
		this->mWindow.clear(Color::Black);

		mWindow.draw(midLine);
		paddle.show();
		ai.show();
		ball.show();

		paddle.move();
		ai.move();
		ball.move(paddle, ai, ball);

		BallOutOfField(ball);

		this->mWindow.display();
	}
}

bool Game::DetectPaddleCollision(Ball ball, Paddle paddle) {
	//Ball
	Vector2f bA = Vector2f(ball.getPos().x - ball.getHalf().x, ball.getPos().y - ball.getHalf().y);
	Vector2f bB = Vector2f(ball.getPos().x + ball.getHalf().x, ball.getPos().y - ball.getHalf().y);
	Vector2f bC = Vector2f(ball.getPos().x + ball.getHalf().x, ball.getPos().y + ball.getHalf().y);
	Vector2f bD = Vector2f(ball.getPos().x - ball.getHalf().x, ball.getPos().y + ball.getHalf().y);

	//Paddle
	Vector2f pA = Vector2f(paddle.getPos().x - paddle.getHalf().x, paddle.getPos().y - paddle.getHalf().y);
	Vector2f pB = Vector2f(paddle.getPos().x + paddle.getHalf().x, paddle.getPos().y - paddle.getHalf().y);
	Vector2f pC = Vector2f(paddle.getPos().x + paddle.getHalf().x, paddle.getPos().y + paddle.getHalf().y);
	Vector2f pD = Vector2f(paddle.getPos().x - paddle.getHalf().x, paddle.getPos().y + paddle.getHalf().y);

	if ((bD.x < pC.x && pD.x < bC.x) && (pD.y > bA.y && bD.y > pA.y)) {
		return 1;
	}
	else {
		return 0;
	}
}

bool Game::DetectWallCollision(Ball ball) {
	Vector2f bA = Vector2f(ball.getPos().x - ball.getHalf().x, ball.getPos().y - ball.getHalf().y);
	Vector2f bD = Vector2f(ball.getPos().x - ball.getHalf().x, ball.getPos().y + ball.getHalf().y);

	if (bD.y > 720 || bA.y < 0) {
		return 1;
	}
	else {
		return 0;
	}
}

float Game::getHitPos(Paddle pad, Ball ball) {
	float relativeDistY = sqrt(pow(ball.getPos().y - pad.getPos().y, 2));
	float normalizedDistY = (relativeDistY / pad.getHalf().y);

	if (ball.getPos().y < pad.getPos().y) {
		return -normalizedDistY;
	}
	else if (ball.getPos().y > pad.getPos().y) {
		return normalizedDistY;
	}
	else {
		return 0;
	}
}

void Game::BallOutOfField(Ball &ball) {
	if (ball.getPos().x < 0) {
		score2++;
		system("cls");
		std::cout << score1 << " : " << score2 << std::endl;
		ball.reset();
	}
	else if (ball.getPos().x > 1280) {
		score1++;
		system("cls");
		std::cout << score1 << " : " << score2 << std::endl;
		ball.reset();
	}
}