#include "SettingsMenu.h"

void create_settings(RenderWindow& window, bool& sound, bool& music) {
	bool MenuOpen = 1;
	Texture TSoundOn, TSoundOff, TControl, TControlSelected;
	TSoundOn.loadFromFile("resources/textures/sound_on.png");
	TSoundOff.loadFromFile("resources/textures/sound_off.png");
	TControl.loadFromFile("resources/textures/control.png");
	TControl.loadFromFile("resources/textures/control.png");
	TControlSelected.loadFromFile("resources/textures/control_selected.png");
	Sprite SSound(TSoundOn), SMusic(TSoundOn), SControl(TControl);
	Event event;

	Texture TBG;
	TBG.loadFromFile("resources/textures/bg.jpg");
	Sprite BG(TBG);
	BG.setScale(1, 2);

	SSound.setPosition(400, 300);
	SMusic.setPosition(400, 500);
	SControl.setPosition(71, 700);

	Font font;
	font.loadFromFile("resources/Fifaks10Dev1.ttf");
	Text Tsounds(L"«¬” »", font, 50), Tmusic(L"Ã”«€ ¿", font, 50);
	Tsounds.setPosition(50, 300);
	Tmusic.setPosition(50, 500);

	Text Header(L"Õ¿—“–Œ… »", font, 70);
	Header.setPosition(95, 2);

	if (!sound) SSound.setTexture(TSoundOff); else SSound.setTexture(TSoundOn);
	if (!music) SMusic.setTexture(TSoundOff); else SMusic.setTexture(TSoundOn);

	while (MenuOpen) {
		window.clear();
		SControl.setTexture(TControl);
		int SelectedButton = 0;

		while (window.pollEvent(event)) {
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				MenuOpen = 0;
			if (IntRect(400, 300, 50, 50).contains(Mouse::getPosition(window))) { SelectedButton = 1; }
			if (IntRect(400, 500, 50, 50).contains(Mouse::getPosition(window))) { SelectedButton = 2; }
			if (event.type == Event::MouseButtonReleased)
			{
				if (SelectedButton == 1) { if (sound) SSound.setTexture(TSoundOff); else SSound.setTexture(TSoundOn); sound = !sound; }
				if (SelectedButton == 2) { if (music) SMusic.setTexture(TSoundOff); else SMusic.setTexture(TSoundOn); music = !music; }
			}
		}
		if (IntRect(71, 700, 370, 80).contains(Mouse::getPosition(window))) { SelectedButton = 3; SControl.setTexture(TControlSelected); }
		if (event.type == Event::MouseButtonReleased)
			if (SelectedButton == 3) { create_control(window); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
		{
			window.draw(BG);
			window.draw(SSound);
			window.draw(SMusic);
			window.draw(SControl);
			window.draw(Tsounds);
			window.draw(Tmusic);
			window.draw(Header);
			window.display();
		}
	}
}




