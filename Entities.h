#pragma once
#include "inc.h"
#include <random>

class Entity {
public:
	float dx, x, y, speed, moveTimer;
	int w, h;
	bool life;
	Texture texture;
	Sprite sprite;
	string name;
	Entity() {}
	Entity(Image& image, float X, float Y, int W, int H) {
		x = X; y = Y; w = W; h = H;
		speed = 0; dx = 0;
		life = true;
		texture.loadFromImage(image);
		sprite.setTexture(texture);


	}

	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}

	virtual void update(float time) = 0;
	//virtual void collision(float time) = 0;
};

class Player : public Entity {
public:
	int playerScore;
	bool isShoot;
	int timer;
	int hearts;
	
	enum { left, right, stay } state;
	Player(Image& image, float X, float Y, int W, int H) :Entity(image, X, Y, W, H) {
		playerScore = 0;
		isShoot = 0;
		timer = 1000;
		name = "player";
		hearts = 3;
		
	}
	void control() {
		state = stay; speed = 0;
		if (Keyboard::isKeyPressed) {
			if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
				state = left; speed = 0.2;

			}
			if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
				state = right; speed = 0.2;

			}

			if ((Keyboard::isKeyPressed(Keyboard::Space) || Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))) {
				isShoot = true;
				timer = 0;
			}
		}


	}
	void collision(float time) {
		if (x < -30 || x>392)
			x -= dx * time;
	}
	void update(float time)
	{
		timer += time;
		control();
		switch (state)
		{
		case right:dx = speed;
			break;
		case left:dx = -speed;
			break;
		case stay: dx = 0; break;
		}
		x += dx * time;
		collision(time);
		sprite.setPosition(x, y);
	}
};

class Enemy : public Entity {
public:
	float dy;
	Enemy(Image& image) {
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = rand() % 452;
		y = -60;
		dx = rand() % 4 / 100.0;
		dx = (rand() % 1 == 1 && x>40) ? -dx : ((x<300)? dx:-dx);
		dy = (rand() % 3 + 8) / 100.;
		w = h = 60;
		int i = rand() % 4;
		sprite.setTextureRect(IntRect(w * i, h * i, w, h));
		life = true;
		name = "enemy";
	}
	void collision() {
		if (y > 900)
			life = 0;
	}
	void update(float time)
	{
		collision();
		x += dx * time;
		y += dy * time;
		sprite.setPosition(x, y);
	}
};

class Bullet : public Entity {
public:
	int dy;
	Bullet(Image& image, float X, float Y, int W, int H) :Entity(image, X, Y, W, H) {
		speed = 0.7;
		w = 10;
		h = 30;
		life = true;
		dy = 0;
		name = "bullet";
	}

	void update(float time)
	{
		y += -0.7 * time;
		sprite.setPosition(x, y);
		collision(time);
	}

	void collision(float time) {
		if (y < 0)
			life = 0;
	}
};
