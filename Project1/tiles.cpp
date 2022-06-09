#include "tiles.h"


Tiles::Tiles(const int i, const int j, int s, std::string name, int lb, int ub, int rb, int lob) {
	this->corner_x = i;
	this->corner_y = j;
	this->tiles_num = (i * j) - 1;
	this->size = s;
	this->Sprites = new sf::Sprite[tiles_num];
	this->file_name = name;
	this->LEFT_BOUND = lb;
	this->UPPER_BOUND = ub;
	this->RIGHT_BOUND = rb;
	this->LOWER_BOUND  = lob;
	this->freeSpace = sf::Vector2f(RIGHT_BOUND, LOWER_BOUND);

	SetTexture();
	RandomShuffle();
	CreateSprites();

	this->preview.setTexture(texture);

}

void Tiles::SetTexture() {
	try {
		this->texture.loadFromFile(file_name);
	}
	catch (...) {
		std::cout << "Blad!";
	}
}

void Tiles::CreateSprites() {

	for (int i = 0; i < tiles_num; i++) {
		Sprites[i].setTexture(texture);
		Sprites[i].setTextureRect(sf::IntRect(placements[i].x, placements[i].y, size, size));
		Sprites[i].setPosition(this->LEFT_BOUND + positioning[i].x, this->UPPER_BOUND + positioning[i].y);
	}

}


void Tiles::RandomShuffle() {
	for (int i = 0; i < corner_x; i++)
		for (int j = 0; j < corner_y; j++) {
			if (i == corner_x-1 && j == corner_y-1) {
				continue;
			}
			else {
				Tuple position;
				position.x = i * size;
				position.y = j * size;
				placements.push_back(position);
				positioning.push_back(position);
			}
		}
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> distributionInteger(0, tiles_num-1);
	for (int i = 0; i < tiles_num; i++) {
		int pos2 = distributionInteger(generator);
		Tuple pom;
		pom = placements[i];
		placements[i] = placements[pos2];
		placements[pos2] = pom;
	}

	
}
