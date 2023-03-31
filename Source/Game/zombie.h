#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <string>

using namespace game_framework;

class Zombie {
private:
	int hp;
	int atk;
	int state;
	double speed;
	game_framework::CMovingBitmap a;
public:
	Zombie() {}
	~Zombie() = default;
	void show();
	void init();
};

#endif // ZOMBIE_H



