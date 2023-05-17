#ifndef PLANT_H
#define PLANT_H

#include <string>

class Plant {
protected:
	int state;
	
	game_framework::CMovingBitmap plant;
public:
	Plant() = default;
	~Plant() = default;
	void show();
	virtual void init();
	int atk_speed = 0;
	int hp = 100;
	int cd = 0;

};


class Sunflower:public Plant {
public:
	Sunflower() = default;
	void init();
	void show(); 
	void SetTopLeft(int x, int y);
};



class Bean:public Plant {
public:
	Bean() = default;

	int pb_x = 0;
	int pb_y = 0;
	void init();
	void show();
	int PBgetleft();
	int PBgettop();
	void attack();
	int pb_flag = 0;
	void reload();
	void leave();
	void SetTopLeft(int x, int y);
	int GetLeft();
	int GetTop();
	game_framework::CMovingBitmap pb;

};
class Nut:public Plant {
public:
	Nut() :Plant() {}
	void init();
	void show();
	void SetTopLeft(int x, int y);
	int GetLeft();
	int GetTop();
};

#endif 