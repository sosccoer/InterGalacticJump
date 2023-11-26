#include "MainMenu.h"

#include <iostream>
#include <filesystem>
#include <string>
namespace fs = std::experimental::filesystem;



bool sound, music;
bool create_menu(RenderWindow& window) {
	Texture TStart, TRecords, TExit, TBG, TStartSelected, TRecordsSelected, TExitSelected, rocket, TSettings, TSettingsSelected;

	std::string path = fs::current_path().string();

	TStart.loadFromFile("resources/textures/start.png");
	TRecords.loadFromFile("resources/textures/records.png");
	TExit.loadFromFile("resources/textures/exit.png");
	TBG.loadFromFile("resources/textures/bg.jpg");
	TStartSelected.loadFromFile("resources/textures/start_selected.png");
	TRecordsSelected.loadFromFile("resources/textures/records_selected.png");
	TExitSelected.loadFromFile("resources/textures/exit_selected.png");
	rocket.loadFromFile(path + "\\menu_pix.png");
	TSettings.loadFromFile("resources/textures/settings.png");
	TSettingsSelected.loadFromFile("resources/textures/settings_selected.png");
	Sprite BStart(TStart), BRecords(TRecords), BExit(TExit), BBG(TBG), Rocket(rocket), BSettings(TSettings);

	bool MenuOpen = 1;
	sound = 1, music = 1;
	int SelectedButton = 0;

	BStart.setPosition(71, 346);
	BRecords.setPosition(71, 614);
	BExit.setPosition(71, 748);
	BBG.setPosition(0, 0);
	BSettings.setPosition(71, 480);
	Rocket.setPosition(130, 60);
	Rocket.setScale(5, 5);
	BBG.scale(1, 2);

	Event event;

	while (MenuOpen)
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				exit(0);
		}
		window.clear(Color(129, 181, 221));

		BStart.setTexture(TStart);
		BRecords.setTexture(TRecords);
		BExit.setTexture(TExit);
		BSettings.setTexture(TSettings);
		SelectedButton = 0;

		if (IntRect(71, 346, 370, 80).contains(Mouse::getPosition(window))) { BStart.setTexture(TStartSelected); ; SelectedButton = 1; }
		if (IntRect(71, 480, 370, 80).contains(Mouse::getPosition(window))) { BSettings.setTexture(TSettingsSelected); SelectedButton = 2; }
		if (IntRect(71, 614, 370, 80).contains(Mouse::getPosition(window))) { BRecords.setTexture(TRecordsSelected);; SelectedButton = 3; }
		if (IntRect(71, 748, 370, 80).contains(Mouse::getPosition(window))) { BExit.setTexture(TExitSelected); SelectedButton = 4; }


		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (SelectedButton == 1) game_process(window, sound, music);
			if (SelectedButton == 2) { create_settings(window, sound, music); }
			if (SelectedButton == 3) { create_table(window); while (!Keyboard::isKeyPressed(Keyboard::Escape)) {}; }
			if (SelectedButton == 4) { window.close(); return 0; }



		}

		window.draw(BBG);
		window.draw(BStart);
		window.draw(BRecords);
		window.draw(BExit);
		window.draw(Rocket);
		window.draw(BSettings);
		window.display();
	}
}