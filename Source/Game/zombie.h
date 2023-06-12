#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <string>

//using namespace game_framework;

class Zombie {
protected:
	int x = 0;
	int y = 0;
	game_framework::CMovingBitmap zombie;
	game_framework::CMovingBitmap zombie_die;
	game_framework::CMovingBitmap zombie_headfall;
	game_framework::CMovingBitmap zombie_atk;
	game_framework::CMovingBitmap zombie_fire;
public:
	Zombie() {}
	~Zombie() = default;
	virtual void show();
	virtual void init();
	int hp = 100;
	void SetTopLeft(int x,int y);
	int die_flag = 0;
	int speed = -1;
	int GetLeft();
	int GetTop();
	int state = 0;
	int attack = 0;
	int cd = 0;
};

#endif // ZOMBIE_H



