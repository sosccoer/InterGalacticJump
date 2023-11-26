#include "InputResult.h"

void create_field(RenderWindow& window, int score) {
	Event event;
	Font font;
	font.loadFromFile("resources/Fifaks10Dev1.ttf");
	TextField field;
	field.setPosition(Vector2f(100, 230));
	field.setFont(font);
	field.setLength(24);
	field.setPlaceholder("--------------------------");
	Text enter(L"      ббедхре хлъ х мюфлхре ENTER\n      дкъ янупюмемхъ пегскэрюрю\n хкх\n      мюфлхре ENTER, нярюбхб онке осяршл,\n      дкъ сдюкемхъ пегскэрюрю", font, 24);
	enter.setPosition(20, 360);
	float alpha = 255;
	float plus = 0.4;
	bool open = 1;
	wstring nickname = L" ";
	Texture BG;
	BG.loadFromFile("resources/textures/bld_bg.png");
	Sprite bg(BG);

	while (open) {
		window.clear();
		while (window.pollEvent(event)) {
			field.input(event);

			if (event.type == Event::KeyReleased && event.type == Event::Closed)
				exit(0);

			if (event.key.code == Keyboard::Return) {
				if (field.getTextLength() != 0) {
					nickname = field.getText();
					wofstream out("resources/high score table.txt", ios::app);
					out.imbue(locale("RU"));
					out << L"\n" + nickname + L" " + to_wstring(score);
					out.close();
				}
				open = 0;
			}
		}
		if (alpha == 255 || alpha == 0)
			plus = -plus;
		alpha += plus;
		enter.setFillColor(Color(255, 255, 255, alpha));
		window.draw(bg);
		field.render(window);
		window.draw(enter);
		window.display();


	}
}