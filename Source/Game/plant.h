#ifndef PLANT_H
#define PLANT_H

#include <string>

class Plant {
protected:
	int pb_x = 0;
	int pb_y = 0;
	double speed;
	
	game_framework::CMovingBitmap a;
	game_framework::CMovingBitmap plant;
	game_framework::CMovingBitmap pb;
	game_framework::CMovingBitmap sunflower_getsun;
	game_framework::CMovingBitmap getsun;

public:
	Plant() {}
	~Plant() = default;
	void show();
	virtual void init();
	int atk_speed = 0;
	int hp = 100;
	int cd = 0;

};
class Sunflower:public Plant {
public:
	Sunflower():Plant(){}
	void init();
	void show(); 
	void SetTopLeft(int x, int y);
	int state = 0;
	int getsun_flag = 0;
	int GetLeft();
	int GetTop();
	int sunGetLeft();
	int sunGetTop();
	int cd_keep = 0;
};
class Bean:public Plant {
public:
	Bean() : Plant(){}
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
	int state = 0;
};
class Nut :public Plant {
public:
	Nut() :Plant() {}
	void init();
	void show();
	void SetTopLeft(int x, int y);
	int GetLeft();
	int GetTop();
};


#endif 