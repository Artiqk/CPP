#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include "Game.h"
#include "Ball.h"
#include "Paddle.h"

using namespace sf;

bool reverse = false;
int vel = 10;
float maxAngle = 1.0472;
float vX = vel;
float vY = 0;

SoundBuffer buffer;
Sound sound;

void reverseBall();
void difficulty();
int playSound();

Ball::Ball() {
	this->mBall.setSize(Vector2f(14, 14));
	this->mBall.setFillColor(Color::White);
	this->mBall.setOrigin(Vector2f(mBall.getSize().x / 2, mBall.getSize().y / 2));
	this->mBall.setPosition(Vector2f(640, 360));
}

void Ball::show() {
	bWindow->draw(mBall);
}

void Ball::move(Paddle &pad, Paddle &pad2, Ball &ball) {
	if (Game::DetectPaddleCollision(ball, pad) || Game::DetectPaddleCollision(ball, pad2)) {
		playSound();
		if (Game::getHitPos(pad, ball) == 0) {
			vX = vel;
			vY = 0;
		}
		else {
			float bounceAngle = Game::getHitPos(pad, ball) * maxAngle;
			vX = vel * cos(bounceAngle);
			vY = vel * sin(bounceAngle);
		}
		reverseBall();
		difficulty();
	}

	if (Game::DetectWallCollision(ball)) {
		vY = -vY;
	}

	if (!reverse) {
		this->mBall.move(vX, vY);
	}
	else {
		this->mBall.move(-vX, vY);
	}
}

void Ball::reset() {
	this->mBall.setPosition(Vector2f(640, 360));
	vel = 10;
	vX = vel;
	vY = 0;
}

Vector2f Ball::getPos() {
	return this->mBall.getPosition();
}

Vector2f Ball::getHalf() {
	Vector2f half = Vector2f(this->mBall.getSize().x / 2, this->mBall.getSize().y / 2);
	return half;
}

void Ball::debugVel() {
	if (Mouse::isButtonPressed(Mouse::Right)) {
		if (vel > 0) {
			vel--;
		}
	}

	if (Mouse::isButtonPressed(Mouse::Left)) {
		vel++;
	}
}

int playSound() {
	if (!buffer.loadFromFile("ball.wav"))
		return EXIT_FAILURE;
	sound.setBuffer(buffer);
	sound.play();
}

void reverseBall() {
	if (reverse) {
		reverse = false;
	}
	else {
		reverse = true;
	}
}

void difficulty() {
	if (vel < 25) {
		vel++;
	}
}