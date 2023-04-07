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
public:
	Zombie() {}
	~Zombie() = default;
	void show();
	virtual void init();
	int hp = 100;
	void SetTopLeft(int x,int y);
	int speed = -1;
};
class Basic_zombie:public Zombie {
protected:
private:
public:
	Basic_zombie():Zombie() {}
	void init() override;
	void show();
	int GetLeft();
	int GetTop();
	int state = 0;
	void loadstate(int state);
};
#endif // ZOMBIE_H



