#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <string>

//using namespace game_framework;

class Zombie {
protected:
	int atk;
	int x = 0;
	int y = 0;
	game_framework::CMovingBitmap zombie;
	game_framework::CMovingBitmap zombie_die;
	game_framework::CMovingBitmap zombie_headfall;
	game_framework::CMovingBitmap zombie_atk;
public:
	Zombie() {}
	~Zombie() = default;
	void show();
	virtual void init();
	int hp = 100;
	void SetTopLeft(int x,int y);
	int speed = -1;
};

#endif // ZOMBIE_H



