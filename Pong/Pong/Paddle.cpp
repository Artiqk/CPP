#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"

using namespace sf;

Paddle::Paddle(bool player) {
	this->mPaddle.setSize(Vector2f(20, 120));
	this->mPaddle.setFillColor(Color::White);
	this->mPaddle.setOrigin(Vector2f(mPaddle.getSize().x / 2, mPaddle.getSize().y / 2));
	if (player) {
		this->mPaddle.setPosition(Vector2f((0 + (mPaddle.getSize().x) * 2), 360));
	}
	if (!player) {
		this->mPaddle.setPosition(Vector2f((1280 - (mPaddle.getSize().x * 2)), 360));
	}
}

void Paddle::show() {
	pWindow->draw(mPaddle);
}

void Paddle::move() {
	int mouseY = Mouse::getPosition(*pWindow).y;
	this->mPaddle.setPosition(Vector2f(this->mPaddle.getPosition().x, mouseY));
}

/*void Paddle::moveAI(Ball &ball) {
	if (mPaddle.getPosition().y - getHalf().y == 0 || mPaddle.getPosition().y + getHalf().y == 720) {
		mPaddle.setPosition(Vector2f(mPaddle.getPosition().x, mPaddle.getPosition().y));
	}
	else {
		this->mPaddle.setPosition(Vector2f(this->mPaddle.getPosition().x, ball.getPos().y));
	}
}*/

Vector2f Paddle::getPos() {
	return this->mPaddle.getPosition();
}

Vector2f Paddle::getHalf() {
	Vector2f half = Vector2f(this->mPaddle.getSize().x / 2, this->mPaddle.getSize().y / 2);
	return half;
}