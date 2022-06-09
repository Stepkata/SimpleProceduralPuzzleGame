/*int LEFT_BOUND = 450;
int UPPER_BOUND = 50;
int RIGHT_BOUND = 1050;
int LOWER_BOUND = 750;

struct Tuple {
	int x;
	int y;
};

std::vector<Tuple> placements;

void RandomShuffle() {
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 8; j++) {
			if (j == 7 && i == 6) {
				continue;
			}
			else {
				Tuple position;
				position.x = i * 100;
				position.y = j * 100;
				placements.push_back(position);
			}
		}
	for (int i = 0; i < 55; i++) {
		int pos2 = rand() % 54;
		Tuple pom;
		pom = placements[i];
		placements[i] = placements[pos2];
		placements[pos2] = pom;
	}

}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Puzzle? Maybe");

	sf::Texture t1; //wczytywanie tekstury
	try {
		t1.loadFromFile("picture1.png");
	}
	catch (...) {
		std::cout << "Blad!";
	}

	RandomShuffle();
	int x = 0;
	sf::Sprite sprites[7][8]; //kreacja spritów
	for (int i = 0; i < 7; i++)
		for(int j=0; j<8; j++){
			if (j == 7 && i == 6) {
				continue;
			}
			else {
				sprites[i][j].setTexture(t1);
				sprites[i][j].setTextureRect(IntRect(placements[x].x, placements[x].y, 100, 100));
				sprites[i][j].setPosition(LEFT_BOUND+(i * 100), UPPER_BOUND + (j * 100));
				x++;
			}
	}


	bool is_moving = false;
	int dx = 0;
	int dy = 0;
	int n = 0;
	int m = 0;

	while (window.isOpen()) //okno
	{
		sf::Event event;
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed) //wykrywanie naciœniêcia myszk¹
				if (event.key.code == sf::Mouse::Left)
					for(int i=0; i<7; i++)
						for (int j = 0; j < 8; j++) {
							if (j == 7 && i == 6) {
								continue;
							}
							else if (sprites[i][j].getGlobalBounds().contains(pos.x, pos.y)) {
								is_moving = true;
								n = i;
								m = j;
								dx = pos.x - sprites[i][j].getPosition().x;
								dy = pos.y - sprites[i][j].getPosition().y;
							}
						}


			if (event.type == sf::Event::MouseButtonReleased)
				if (event.key.code == sf::Mouse::Left)
					is_moving = false;
		}
		if (is_moving) { //ruch
			for (int i = 0; i < 7; i++)
				for (int j = 0; j < 8; j++) {
					if (j == 7 && i == 6) {
						continue;
					}
					else
						window.draw(sprites[i][j]);
				}

			int px = (pos.x - dx) > LEFT_BOUND ? (pos.x - dx) : LEFT_BOUND;
			int py = (pos.y - dy) > UPPER_BOUND ? (pos.y - dy) : UPPER_BOUND;
			sprites[n][m].setPosition((px < RIGHT_BOUND ? px : RIGHT_BOUND) , (py < LOWER_BOUND ? py : LOWER_BOUND));
		}

		window.clear(); //odœwierznie ekranu
		for (int i = 0; i < 7; i++)
			for (int j = 0; j < 8; j++) {
				if (j == 7 && i == 6) {
					continue;
				}
				else
					window.draw(sprites[i][j]);
			}
		window.display();

	}

	return 0;
}*/

/*
#include "tiles.h"

using namespace sf;

void Level1();

int LEFT_BOUND = 450;
int UPPER_BOUND = 50;
int RIGHT_BOUND = 1050;
int LOWER_BOUND = 750;

int IMAGE_X = 700;
int IMAGE_Y = 800;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Puzzle? Maybe");

	Tiles tiles(7, 8, 100, "picture1.png", LEFT_BOUND, UPPER_BOUND);


	sf::Vector2f freeSpace = sf::Vector2f(RIGHT_BOUND, LOWER_BOUND);
	sf::Vector2f oldPos = sf::Vector2f(0, 0);

	bool is_moving = false;
	bool first_click = true;
	int dx = 0;
	int dy = 0;
	int n = 0;
	int m = 0;

	while (window.isOpen()) //okno
	{
		sf::Event event;
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed) //wykrywanie naciœniêcia myszk¹
				if (event.key.code == sf::Mouse::Left)
					for (int i = 0; i < 55; i++){
						if (tiles.sprites(i).getGlobalBounds().contains(pos.x, pos.y)) {
							if (first_click) {
								first_click = false;
								oldPos.x = tiles.sprites(i).getPosition().x;
								oldPos.y = tiles.sprites(i).getPosition().y;
							}
							if ((abs(oldPos.x - freeSpace.x)<=100 && (oldPos.y - freeSpace.y)==0) || ((oldPos.x - freeSpace.x) == 0 && abs(oldPos.y - freeSpace.y) <= 100))
								is_moving = true; //mo¿emy siê ruszyæ tylko jak obok jest wolne miejsce
							n = i;
							dx = pos.x - tiles.sprites(i).getPosition().x;
							dy = pos.y - tiles.sprites(i).getPosition().y;

							}
							
						}


			if (event.type == sf::Event::MouseButtonReleased)
				if (event.key.code == sf::Mouse::Left) {
					if (is_moving) {
						sf::Vector2f p = tiles.sprites(n).getPosition();
						sf::Vector2f newPos = sf::Vector2f(100 * int(p.x / 100) + 50, 100 * int(p.y / 100) + 50);
						if (newPos.x == freeSpace.x && newPos.y == freeSpace.y) { //sprawdzenie czy przesunêliœmy na woln¹ pozycjê
							tiles.setPosition(n, newPos.x, newPos.y);
							freeSpace.x = oldPos.x;
							freeSpace.y = oldPos.y;
						}
						else
							tiles.setPosition(n, oldPos.x, oldPos.y); //jak nie wracamy z powrotem
					}
					is_moving = false;
					first_click = true;
				
				}
		}
		if (is_moving) { //ruch
			for (int i = 0; i < 55; i++) {
					window.draw(tiles.sprites(i));
			}
			int chx;
			int chy;
	
		
			int px = (pos.x - dx) > LEFT_BOUND ? (pos.x - dx) : LEFT_BOUND;
			int py = (pos.y - dy) > UPPER_BOUND ? (pos.y - dy) : UPPER_BOUND;

			if (abs(oldPos.x - freeSpace.x) <= 100 && (oldPos.y - freeSpace.y) == 0) { //poruszanie siê tylko po jednej osi + ¿eby nie mo¿na by³o iœæ po skosie
				chx = px < RIGHT_BOUND ? px : RIGHT_BOUND;
				chy = oldPos.y;
			}
			else {
				chx = oldPos.x;
				chy = py < LOWER_BOUND ? py : LOWER_BOUND;
			}
			tiles.setPosition(n, chx, chy);
			
		}

		window.clear(); //odœwierznie ekranu
		for (int i = 0; i < 55; i++){
					window.draw(tiles.sprites(i));
			}
		window.display();

	}


	return 0;
}*/