#ifndef PLANT_H
#define PLANT_H

#include <string>

class Plant :public game_framework::CMovingBitmap{
protected:
	int state;
	
public:
	Plant() = default;
	~Plant() = default;
	void show();
	void init();
	int atk_speed = 0;
	int hp = 100;
	int cd = 0;
	int coordinate_x = 0;
	int coordinate_y = 0;
	int die_flag = 0;
};


class Sunflower:public Plant {
protected:
	game_framework::CMovingBitmap sunflower_getsun;
	game_framework::CMovingBitmap getsun;
public:
	Sunflower() = default;
	void init();
	void show();
	int state = 0;
	int getsun_flag = 0;
	int sunGetLeft();
	int sunGetTop();
	int cd_keep = 0;
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
	game_framework::CMovingBitmap pb;

};
class Nut:public Plant {
public:
	Nut() :Plant() {}
	void init();
	void show();
};

#endif 