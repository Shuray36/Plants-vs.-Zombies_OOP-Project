#pragma once
#include "zombie.h"
class Basic_zombie :public Zombie {
protected:
private:
public:
	Basic_zombie() = default;
	void init();
	void show();
	int GetLeft();
	int GetTop();
	int state = 0;
	int die_flag = 0;
	int cd = 0;
	void loadstate(int state);
	
};