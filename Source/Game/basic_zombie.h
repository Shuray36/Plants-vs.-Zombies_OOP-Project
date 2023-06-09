#pragma once
#include "zombie.h"
class Basic_zombie :public Zombie {
protected:
private:
public:
	Basic_zombie() = default;
	void init() override;
	void show() override;
	//int state = 0;
	//int die_flag = 0;
	int cd = 0;
	void loadstate(int state);
	
};