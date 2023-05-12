#ifndef PLANT_H
#define PLANT_H

#include <string>

class Plant {
protected:
	int state;
	int pb_x = 0;
	int pb_y = 0;
	double speed;
	
	game_framework::CMovingBitmap a;
	game_framework::CMovingBitmap plant;
	game_framework::CMovingBitmap pb;
public:
	Plant() {}
	~Plant() = default;
	void show();
	virtual void init();
	int atk_speed = 0;
	int hp = 100;
<<<<<<< HEAD
	int cd = 0;

=======
>>>>>>> c62af637a7982c05ddd401ddc0a01cb624279f35
};
class Sunflower:public Plant {
public:
	Sunflower():Plant(){}
	void init();
	void show(); 
	void SetTopLeft(int x, int y);
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
<<<<<<< HEAD
	int GetLeft();
	int GetTop();
=======
>>>>>>> c62af637a7982c05ddd401ddc0a01cb624279f35
};
#endif 