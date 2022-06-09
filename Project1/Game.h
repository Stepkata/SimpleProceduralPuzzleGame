#include "tiles.h"


class Game {
public:
	Game(std::vector<Data> vec_data);
	void start();
	~Game() {
		for (int i = 0; i < kafelki.size(); i++) {
			Tiles *pom;
			pom = kafelki[i];
			delete pom;
		}
		delete [] buttons;
		delete back_button;
	}
private:

	int im_x = 800;
	int im_y = 800;
	int size;

	int LEFT_BOUND;
	int UPPER_BOUND;
	int RIGHT_BOUND;
	int LOWER_BOUND;

	int dim_x;
	int dim_y;
	int num_t;

	Tiles *tiles;
	sf::Sprite *buttons;
	sf::Texture buttons_tex;
	std::vector<Data> Dane;
	std::vector<Tiles *> kafelki;
	sf::Sprite *back_button;
	sf::Sprite prev;
	sf::Texture back_button_tex;


	sf::Vector2f freeSpace;
	sf::Vector2f oldPos;

	bool is_moving = false;
	bool first_click = true;
	bool podglad = false;
	int dx = 0;
	int dy = 0;
	int n = 0;
	int m = 0;

	void SetParas(int n);
	void MakeMenu();
	void prepareTiles();
};
