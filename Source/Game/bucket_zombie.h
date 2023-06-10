#pragma once
#include "zombie.h"
class Bucket_zombie :public Zombie {
protected:
private:
public:
	Bucket_zombie() = default;
	void init();
	void show();
	//int state = 0;
	//int die_flag = 0;
	//int cd = 0;
	void loadstate(int state);
};