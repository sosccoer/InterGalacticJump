#include "inc.h"
#include "ScoreTable.h"
#include "MainMenu.h"
#include "GameProcess.h"
#include <iostream>
#include <filesystem>
#include <string>
namespace fs = std::experimental::filesystem;

int main() {
	srand(time(NULL));
	RenderWindow window(VideoMode(512, 900), "IntergalacticJump",  Style::Titlebar | Style::Close);
	Image icon;
	std::string path = fs::current_path().string();
	icon.loadFromFile(path + "\\menu_pix.png");
	window.setIcon(50, 50, icon.getPixelsPtr());
	while (window.isOpen()) {
		create_menu(window);
	}
}






