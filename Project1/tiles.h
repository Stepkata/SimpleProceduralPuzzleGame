#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <time.h>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <cmath>

struct Tuple {
	int x;
	int y;
};


struct Data {
	std::string name;
	int size;
};

class Tiles {
public:
	Tiles() = default;
	Tiles(int i, int j, int size, std::string name, int lb, int ub, int rb, int lob);
	~Tiles() {
		delete[] Sprites;
	}

	sf::Sprite sprites(int x) {
		return Sprites[x];
	}

	sf::Sprite operator[](int x) { //nie potrzebny bo operujê na wskaŸnikach
		return Sprites[x];
	}

	int getNumerTiles() {
		return tiles_num;
	}

	void setPosition(int n, int x, int y) {
		Sprites[n].setPosition(x, y);
	}
	Tuple getPosition(int x) {
		return positioning[x];
	}

	int getFreeSpaceX() {
		return freeSpace.x;
	}

	int getFreeSpaceY() {
		return freeSpace.y;
	}

	void setFreeSpace(int x, int y) {
		this->freeSpace = sf::Vector2f(x, y);
	}

	sf::Sprite getPreview() {
		return preview;
	}

	int leftBound() {
		return LEFT_BOUND;
	}

	int rightBound() {
		return RIGHT_BOUND;
	}

	int upperBound() {
		return UPPER_BOUND;
	}

	int lowerBound() {
		return LOWER_BOUND;
	}


private:
	int tiles_num;
	int corner_x;
	int corner_y;
	int size;
	std::string file_name;
	sf::Texture texture;
	sf::Sprite *Sprites;
	std::vector<Tuple> placements;
	std::vector<Tuple> positioning;
	int LEFT_BOUND;
	int UPPER_BOUND;
	int RIGHT_BOUND;
	int LOWER_BOUND;
	sf::Vector2f freeSpace;
	sf::Sprite preview;

	void SetTexture();
	void CreateSprites();
	void RandomShuffle();

};