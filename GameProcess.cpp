#include "GameProcess.h"
#include <iostream>
#include <filesystem>
#include <string>
namespace fs = std::experimental::filesystem;

int intersected = 0;

void game_process(RenderWindow& window, bool& isSound, bool& isMusic) {
	list<Entity*>friends;
	list<Entity*>enemies;

	std::string path = fs::current_path().string();

	Image TPlayer, TBullet, TEnemy;
	Texture BG, T3Hearts, T2Hearts, T1Hearts;
	T3Hearts.loadFromFile("resources/textures/3hearts.png");
	T2Hearts.loadFromFile("resources/textures/2hearts.png");
	T1Hearts.loadFromFile("resources/textures/1hearts.png");
	BG.loadFromFile("resources/textures/bg.jpg");
	TPlayer.loadFromFile(path + "\\menu_pix.png");
	TBullet.loadFromFile("resources/textures/bullet.png");
	TEnemy.loadFromFile("resources/textures/enemies.png");

	Sprite BBG(BG), SHearts(T3Hearts);
	BBG.scale(1, 2);
	BBG.setPosition(0, 0);
	SHearts.setPosition(392, 0);

	Player player(TPlayer, 231, 790, 50, 50);
	friends.push_back(&player);
	player.sprite.setScale(3, 3);

	Event event;
	Clock clock;
	float SpawnTimer = 0;
	float SpawnInterval = 5000;
	int SpawnNumber = 1;
	float gameTimer = 0;
	long int seconds = 0;
	Font font;
	font.loadFromFile("resources/Fifaks10Dev1.ttf");

	Text score(L"Î×ÊÈ: 0", font, 30);
	score.setPosition(5, 9);
	Text timer(L"ÂÐÅÌß: ", font, 30);
	timer.setPosition(220, 9);
	RectangleShape blackrect(Vector2f(512, 45));
	blackrect.setFillColor(Color::Black);
	blackrect.setPosition(0, 0);
	blackrect.setOutlineColor(Color::White);
	blackrect.setOutlineThickness(1);
	Sound sound;
	Music music;
	SoundBuffer buffer;
	sound.setBuffer(buffer);
	buffer.loadFromFile("resources/shooting.ogg");
	music.openFromFile("resources/soundtrack.ogg");
	if (isMusic)
		music.play();
	while (player.life && window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		seconds += time;
		time /= 800;
		SpawnTimer += time;
		timer.setString('0' + to_string(seconds / 1000000 / 60) + ":" + ((seconds / 1000000 % 60 < 10) ? '0' + to_string(seconds / 1000000 % 60) : to_string(seconds / 1000000 % 60)));
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				exit(0);

		}

		window.clear();
		window.draw(BBG);
		if (SpawnTimer > SpawnInterval) {
			for (int i = 0; i < rand() % SpawnNumber + 1; i++)
				enemies.push_back(new Enemy(TEnemy));
			SpawnTimer = 0;
		}

		if (player.isShoot) {
			player.isShoot = false;
			if (isSound) {
				buffer.loadFromFile("resources/shooting.ogg");
				sound.play();
			}
			friends.push_back(new Bullet(TBullet, player.x + 70, player.y + 10, 20, 20));
		}


		for (auto it = friends.begin(); it != friends.end();) {
			(*it)->update(time);
			window.draw((*it)->sprite);
			if (!(*it)->life) {
				it = friends.erase(it);
			}
			else
				it++;
		}
		for (auto it1 = enemies.begin(); it1 != enemies.end(); it1++) {
			(*it1)->update(time);
			window.draw((*it1)->sprite);
		}
		for (auto it2 = enemies.begin(); it2 != enemies.end(); it2++) {
			for (auto _it = friends.begin(); _it != friends.end(); _it++)
				if ((*_it)->getRect().intersects((*it2)->getRect()))
				{
					if ((*_it)->name == "bullet") {

						(*it2)->life = 0;
						(*_it)->life = 0;
						if (SpawnInterval < 3000)
							SpawnInterval = 3000;
						if (player.playerScore % 5 == 0 && SpawnInterval < 3500 && SpawnNumber < 4 && player.playerScore>20)
							SpawnNumber++;
						if (player.playerScore % 5 == 0 && player.playerScore != 0);
						SpawnInterval -= 250;
						player.playerScore++;
					}

					if ((*_it)->name == "player") {
						(*it2)->life = 0;
						player.hearts--;
					}
				}
			if ((*it2)->y > 900 || (*it2)->x > 512 || (*it2)->x < -60)
				player.life = 0;
		}

		for (auto it = enemies.begin(); it != enemies.end();)
			if (!(*it)->life)
				it = enemies.erase(it);
			else
				it++;
		switch (player.hearts)
		{
		case 2: SHearts.setTexture(T2Hearts); break;
		case 1: SHearts.setTexture(T1Hearts); break;
		case 0: player.life = 0; break;
		}
		for (auto it = friends.begin(); it != friends.end();)
			if (!(*it)->life) {
				it = friends.erase(it);
				if (isSound) {
					buffer.loadFromFile("resources/collision.ogg");
					sound.play();
				}
			}
			else
				it++;

		score.setString(L"Î×ÊÈ: " + to_string(player.playerScore));
		window.draw(blackrect);
		window.draw(timer);
		window.draw(score);
		window.draw(SHearts);
		window.display();
	}
	music.stop();
	create_field(window, player.playerScore);

}