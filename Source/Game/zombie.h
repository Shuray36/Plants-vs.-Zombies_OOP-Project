#pragma once
#include "PZGameObject.h"


class Zombie :public PZGameObject{
protected:
	int x = 0;
	int y = 0;
	//PZGameObject zombie;
	PZGameObject zombie_die;
	PZGameObject zombie_headfall;
	PZGameObject zombie_atk;
	PZGameObject zombie_fire;
public:
	Zombie() = default;
	~Zombie() = default;
	void show();
	virtual void init();
	int hp = 100;
	//void SetTopLeft(int x,int y);
	int die_flag = 0;
	int speed = -1;
	//int GetLeft();
	//int GetTop();
	int state = 0;
	int attack = 0;
	int cd = 0;
	int t = 0;
};




