#include "tiles.h"

void Level1(int im_x, int im_y, int size, sf::RenderWindow *window) {
	
	int LEFT_BOUND = 800 -(im_x/2);
	int UPPER_BOUND = 450 - (im_y / 2);
	int RIGHT_BOUND = 800 + (im_x / 2) - 100;
	int LOWER_BOUND = 450 + (im_y / 2) - 100;

	int dim_x = im_x / size;
	int dim_y = im_y / size;
	int num_t = dim_x * dim_y - 1;

	Tiles tiles(dim_x, dim_y, size, "picture1.png", LEFT_BOUND, UPPER_BOUND);


	sf::Vector2f freeSpace = sf::Vector2f(RIGHT_BOUND, LOWER_BOUND);
	sf::Vector2f oldPos = sf::Vector2f(0, 0);

	bool is_moving = false;
	bool first_click = true;
	int dx = 0;
	int dy = 0;
	int n = 0;
	int m = 0;

	while (window->isOpen()) //okno
	{
		sf::Event event;
		sf::Vector2i pos = sf::Mouse::getPosition(*window);
		while (window->pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == sf::Event::MouseButtonPressed) //wykrywanie naciœniêcia myszk¹
				if (event.key.code == sf::Mouse::Left)
					for (int i = 0; i < num_t; i++) {
						if (tiles.sprites(i).getGlobalBounds().contains(pos.x, pos.y)) {
							if (first_click) {
								first_click = false;
								oldPos.x = tiles.sprites(i).getPosition().x;
								oldPos.y = tiles.sprites(i).getPosition().y;
							}
							if ((abs(oldPos.x - freeSpace.x) <= size && (oldPos.y - freeSpace.y) == 0) || ((oldPos.x - freeSpace.x) == 0 && abs(oldPos.y - freeSpace.y) <= 100))
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
						sf::Vector2f newPos = sf::Vector2f(size * int(p.x / size) + size/2, size * int(p.y / size) + size/2);
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
			for (int i = 0; i < num_t; i++) {
				window->draw(tiles.sprites(i));
			}
			int chx;
			int chy;


			int px = (pos.x - dx) > LEFT_BOUND ? (pos.x - dx) : LEFT_BOUND;
			int py = (pos.y - dy) > UPPER_BOUND ? (pos.y - dy) : UPPER_BOUND;

			if (abs(oldPos.x - freeSpace.x) <= size && (oldPos.y - freeSpace.y) == 0) { //poruszanie siê tylko po jednej osi + ¿eby nie mo¿na by³o iœæ po skosie
				chx = px < RIGHT_BOUND ? px : RIGHT_BOUND;
				chy = oldPos.y;
			}
			else {
				chx = oldPos.x;
				chy = py < LOWER_BOUND ? py : LOWER_BOUND;
			}
			tiles.setPosition(n, chx, chy);

		}

		window->clear(); //odœwierznie ekranu
		for (int i = 0; i < num_t; i++) {
			window->draw(tiles.sprites(i));
		}
		window->display();

	}
}