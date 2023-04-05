#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <string>

//using namespace game_framework;

class Zombie {
protected:
	int hp;
	int atk;
	int state;
	double speed;
	game_framework::CMovingBitmap zombie;
public:
	Zombie() {}
	~Zombie() = default;
	void show();
	virtual void init();
	void SetTopLeft(int x,int y);
};
class Basic_zombie:public Zombie {
protected:
private:
public:
	Basic_zombie():Zombie() {}
	void init() override;
};
#endif // ZOMBIE_H



