#include "ScoreTable.h"

void create_table(RenderWindow& window) {
	vector<wstring> nickname;
	vector<int> score;
	vector<pair<wstring, int>> vec;

	wstring line;
	int number;
	int results = 15;

	Font font;
	font.loadFromFile("resources/Fifaks10Dev1.ttf");

	Texture TBG;
	TBG.loadFromFile("resources/textures/bg.jpg");
	Sprite BG(TBG);
	BG.setPosition(0, 0);
	BG.scale(1, 2);

	Text Header(L"ÒÀËÈÖÀ ÐÅÊÎÐÄÎÂ", font, 60);
	Header.setPosition(Vector2f(25, 2));

	window.clear(Color::Black);
	window.draw(BG);
	window.draw(Header);
	wifstream in("resources/high score table.txt");
	in.imbue(locale("RU"));
	if (in.is_open())
		while (!in.eof()) {
			in >> line;
			nickname.push_back(line);
			in >> number;
			score.push_back(number);
		}
	in.close();
	if (score.size() < 15)
		results = score.size();


	for (int i = 0; i < score.size(); i++)
		vec.push_back(make_pair(nickname[i], score[i]));
	sort(vec.begin(), vec.end(), [](pair<wstring, int>a, pair<wstring, int>b) {return a.second > b.second; });

	wofstream out("resources/high score table.txt");
	out.imbue(locale("RU"));
	for (int i = 0; i < results; i++) {
		out << vec[i].first << " "
			<< vec[i].second << "\n";
		string space = " ";
		for (int q = 0; q < 13 - vec[i].first.length(); q++)
			space += " ";

		Text* text = new Text(" " + to_string(i + 1) + ((i + 1 > 9) ? "  " : "   ") + vec[i].first + space + to_string(vec[i].second), font, 40);
		text->setPosition(1, 53 * i + 80);
		text->setFillColor(Color::Red);
		window.draw(*text);
	}
	Text lines("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _", font, 40);
	for (int i = 0; i < 15; i++) {
		lines.setPosition(3, i * 53 + 90);
		window.draw(lines);
	}
	lines.rotate(90);
	lines.setString("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _");
	for (int i = 0; i < 2; i++) {
		lines.setPosition(i * 285 + 110, 80);
		window.draw(lines);
	}
	out.close();
	nickname.clear();
	score.clear();
	vec.clear();
	window.display();
}
