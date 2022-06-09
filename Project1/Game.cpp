#include "Game.h"

//@TODO: przesuwanie kamery
//@TODO: customowy poziom?

Game::Game(std::vector<Data> vec_data){
	Dane = vec_data;
	prepareTiles();
	SetParas(0);
	MakeMenu();
}

void Game::start() {
	sf::RenderWindow window(sf::VideoMode(1600, 900), "basic procedural puzzle game");
	bool menu = true;
	float vpos = 0; 

	sf::View view;
	view.reset(sf::FloatRect(0, vpos, 1600, 900));
	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	while (window.isOpen()) //okno
	{
		sf::Event event;
		sf::Vector2i pos = sf::Mouse::getPosition(window);


		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();


			//GAMEPLAY
			if (!menu) {
				if (event.type == sf::Event::MouseButtonPressed) //wykrywanie naciœniêcia myszk¹
					if (event.key.code == sf::Mouse::Left) {
						for (int i = 0; i < num_t; i++) {
							if (tiles->sprites(i).getGlobalBounds().contains(pos.x, pos.y)) {
								if (first_click) { //oryginalna pozycja kafelka który przesuwamy
									first_click = false;
									oldPos.x = tiles->sprites(i).getPosition().x;
									oldPos.y = tiles->sprites(i).getPosition().y;
								}
								if ((abs(oldPos.x - freeSpace.x) <= size && (oldPos.y - freeSpace.y) == 0) || ((oldPos.x - freeSpace.x) == 0 && abs(oldPos.y - freeSpace.y) <= size))
									is_moving = true; //mo¿emy siê ruszyæ tylko jak obok jest wolne miejsce
								n = i;
								dx = pos.x - tiles->sprites(i).getPosition().x;
								dy = pos.y - tiles->sprites(i).getPosition().y;

							}

						}
						if (back_button->getGlobalBounds().contains(pos.x, pos.y)) { //back to menu
							tiles->setFreeSpace(freeSpace.x, freeSpace.y);
							menu = true;
						}
							
					}
					
				if (event.type == sf::Event::MouseButtonPressed) //wskazówka
					if (event.key.code == sf::Mouse::Right)
						podglad = true;

				if (event.type == sf::Event::MouseButtonReleased)
					if (event.key.code == sf::Mouse::Right)
						podglad = false;


				if (event.type == sf::Event::MouseButtonReleased) //koniec ruchu
					if (event.key.code == sf::Mouse::Left) {
						if (is_moving) {
							sf::Vector2f p = tiles->sprites(n).getPosition();
							int pomy = (size  < 80) ? size * int(p.y / size) : (size * int(p.y / size)) +50; //@TODO: why

							sf::Vector2f newPos = sf::Vector2f(size * int(p.x / size), pomy);

							if (newPos.x == freeSpace.x && newPos.y == freeSpace.y) { //sprawdzenie czy przesunêliœmy na woln¹ pozycjê
								tiles->setPosition(n, newPos.x, newPos.y);
								freeSpace.x = oldPos.x;
								freeSpace.y = oldPos.y;
							}
							else
								tiles->setPosition(n, oldPos.x, oldPos.y); //jak nie wracamy z powrotem
						}
						is_moving = false;
						first_click = true;

					}

				if (back_button->getGlobalBounds().contains(pos.x, pos.y)) { //"amimacja" back button
					back_button->setScale(sf::Vector2f(0.95f, 0.95f));
					back_button->setColor(sf::Color(255, 255, 255, 128));
				}
				else {
					back_button->setScale(sf::Vector2f(1.f, 1.f));
					back_button->setColor(sf::Color(255, 255, 255, 255));
				}
			}
			
			//MENU
			else { //"animacja" przycisków
				for (int i = 0; i < kafelki.size(); i++) {
					if (buttons[i].getGlobalBounds().contains(pos.x, pos.y+vpos)) {
						buttons[i].setScale(sf::Vector2f(0.25f, 0.25f));
						buttons[i].setColor(sf::Color(255, 255, 255, 128));
					}
					else {
						buttons[i].setScale(sf::Vector2f(0.3f, 0.3f));
						buttons[i].setColor(sf::Color(255, 255, 255, 255));
					}

				}


				if (event.type == sf::Event::MouseButtonPressed) //wykrywanie naciœniêcia myszk¹
					if (event.key.code == sf::Mouse::Left)
						for (int i = 0; i < kafelki.size(); i++) {
							if (buttons[i].getGlobalBounds().contains(pos.x, pos.y+vpos)) {
								SetParas(i);
								menu = false;
							}
						}
				if (event.type == sf::Event::MouseWheelMoved) //scrollowanie
				{
					if (event.mouseWheel.delta < 0) {
						int stop = buttons[kafelki.size() - 1].getPosition().y;

						vpos = (vpos + 2*800/3 >=stop)? vpos : vpos + 30;
					}
					if (event.mouseWheel.delta > 0) {
						vpos = (vpos <=0) ? 0: vpos-30;
					}

					
				}
			}
		}
		//GAMEPLAY

		if (!menu) {
			if (is_moving) { //ruch
				for (int i = 0; i < num_t; i++) {
					window.draw(tiles->sprites(i));
				}
				int chx;
				int chy;

				int px = (pos.x - dx) > LEFT_BOUND ? (pos.x - dx) : LEFT_BOUND;
				int py = (pos.y - dy) > UPPER_BOUND ? (pos.y - dy) : UPPER_BOUND;

				if (abs(oldPos.x - freeSpace.x) <= size && (oldPos.y - freeSpace.y) == 0) { //poruszanie siê tylko po jednej osi + ¿eby nie mo¿na by³o iœæ po skosie -wer. y const
					chx = px < RIGHT_BOUND ? px : RIGHT_BOUND;
					if (oldPos.x < freeSpace.x) { //kolizje
						if (chx < oldPos.x)
							chx = oldPos.x;
						if (chx > freeSpace.x)
							chx = freeSpace.x;
					}
					else if (oldPos.x > freeSpace.x) {
						if (chx > oldPos.x)
							chx = oldPos.x;
						if (chx < freeSpace.x)
							chx = freeSpace.x;

					}
					chy = oldPos.y;
				}
				else {//wer. x const.
					chx = oldPos.x;
					chy = py < LOWER_BOUND ? py : LOWER_BOUND;
					if (oldPos.y < freeSpace.y) { //kolizje
						if (chy < oldPos.y)
							chy= oldPos.y;
						if (chy > freeSpace.y)
							chy= freeSpace.y;
					}
					else if (oldPos.y> freeSpace.y) {
						if (chy > oldPos.y)
							chy = oldPos.y;
						if (chy < freeSpace.y)
							chy = freeSpace.y;

					}
				}
				tiles->setPosition(n, chx, chy);
			}

			window.clear(); //odœwierznie ekranu

			view.reset(sf::FloatRect(0, 0, 1600, 900));
			window.setView(view);
			for (int i = 0; i < num_t; i++) {
				window.draw(tiles->sprites(i));
			}
			window.draw(*back_button);
			if (podglad)
				window.draw(prev);
			window.display();
		}

		//MENU
		else {
			window.clear(); //odœwierznie ekranu

			view.reset(sf::FloatRect(0, vpos, 1600, 900));
			window.setView(view);

			for (int i = 0; i < kafelki.size(); i++) {
				window.draw(buttons[i]);
			}
			window.display();
		}

	}


}

void Game::prepareTiles() {
	for (int i = 0; i < Dane.size(); i++) {

		LEFT_BOUND = 800 - (im_x / 2);
		UPPER_BOUND = 450 - (im_y / 2);
		RIGHT_BOUND = 800 + (im_x / 2) - Dane[i].size;
		LOWER_BOUND = 450 + (im_y / 2) - Dane[i].size;

		dim_x = im_x / Dane[i].size;
		dim_y = im_y / Dane[i].size;
		num_t = dim_x * dim_y - 1;
		Tiles *pom = new Tiles(dim_x, dim_y, Dane[i].size, Dane[i].name, LEFT_BOUND, UPPER_BOUND, RIGHT_BOUND, LOWER_BOUND);
		kafelki.push_back(pom);
	}
}

void Game::SetParas(int n) {
	size = Dane[n].size;
	tiles = kafelki[n];

	LEFT_BOUND = tiles->leftBound();
	UPPER_BOUND = tiles->upperBound();
	RIGHT_BOUND = tiles->rightBound();
	LOWER_BOUND = tiles->lowerBound();

	dim_x = im_x / size;
	dim_y = im_y / size;
	num_t = dim_x * dim_y - 1;


	freeSpace = sf::Vector2f(tiles->getFreeSpaceX(), tiles->getFreeSpaceY());
	
	oldPos = sf::Vector2f(0, 0);

	prev = kafelki[n]->getPreview();
	prev.setPosition(LEFT_BOUND, UPPER_BOUND);
	prev.setColor(sf::Color(255, 255, 255, 170));

}


void Game::MakeMenu() {

	this->buttons = new sf::Sprite[kafelki.size()];
	int zm_y = 0;
	int zm_x = 0;
	for (int i = 0; i < kafelki.size(); i++) {
		buttons[i] = kafelki[i]->getPreview();
		if (200 + (zm_x * (800 / 3)) > 1600-800/3) {
			zm_x = 0;
			zm_y++;
		}
		int x = 200 + (zm_x * (800 / 3));
		int y = (zm_y * (800 / 3));
		buttons[i].setPosition( x, ( x > RIGHT_BOUND?(100+y):(100+(++y)) ) );
		buttons[i].setOrigin(150.f, 150.f);
		buttons[i].setScale(0.3f, 0.3f);
		zm_x++;
	}

	try {
		back_button_tex.loadFromFile("button.png");
	}
	catch (...) {
		std::cout << "Blad!";
	}
	this->back_button = new sf::Sprite;
	back_button->setTexture(back_button_tex);
	back_button->setPosition(100, 100);
	back_button->setOrigin(95.f,48.f);
}