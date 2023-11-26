#include "ControlMenu.h"

void create_control(RenderWindow& window) {
	Texture TBG, TControl;
	TBG.loadFromFile("resources/textures/bg.jpg");
	TControl.loadFromFile("resources/textures/control_table.png");
	Sprite BG(TBG), Control(TControl);
	BG.setScale(1, 2);
	window.draw(BG);
	window.draw(Control);
	window.display();
}