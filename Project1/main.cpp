#include "game.h"

std::vector<Data> dane, dane2;

int main()
{
	Data data1 = { "picture1.png", 200 }, data2 = { "picture2.png", 100}, data3 = { "picture3.png", 80 }, data4 = { "picture4.png", 50 }, data5 = { "picture5.png", 25 },
	data6{ "picture3.png", 200 }, data7 = { "picture2.png", 100 }, data8 = { "picture5.png", 80 }, data9 = { "picture1.png", 50 }, data10 = { "picture4.png", 25 };
	dane2.push_back(data1);
	dane2.push_back(data2);
	dane2.push_back(data3);
	dane2.push_back(data4);
	dane2.push_back(data5);
	dane2.push_back(data6);
	dane2.push_back(data7);
	dane2.push_back(data8);
	dane2.push_back(data9);
	dane2.push_back(data10);
	dane2.push_back(data1);
	dane2.push_back(data2);
	dane2.push_back(data3);
	dane2.push_back(data4);
	dane2.push_back(data5);
	dane2.push_back(data6);
	dane2.push_back(data7);
	dane2.push_back(data8);
	dane2.push_back(data9);
	dane2.push_back(data10);
	dane2.push_back(data10);
	dane2.push_back(data1);
	dane2.push_back(data2);
	dane2.push_back(data3);
	dane2.push_back(data4);
	dane2.push_back(data5);
	dane2.push_back(data6);
	dane2.push_back(data7);
	dane2.push_back(data8);
	dane2.push_back(data9);
	dane2.push_back(data10);

	data1 = { "picture1.png", 200 };
	data2 = { "picture2.png", 100 };
	data3 = { "picture3.png", 80 };
	data4 = { "picture4.png", 50 };
	data5 = { "picture5.png", 25 };
	dane.push_back(data1);
	dane.push_back(data2);
	dane.push_back(data3);
	dane.push_back(data4);
	dane.push_back(data5);

	Game game(dane2);
	game.start();
	return 0;
}