#pragma once
#include "zombie.h"
class Triangle_zombie :public Zombie {
protected:
private:
public:
	Triangle_zombie() = default;
	void init();
	void show();
	int state = 0;
	int die_flag = 0;
	int cd = 0;
	void loadstate(int state);

};