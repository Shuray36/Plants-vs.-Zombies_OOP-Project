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
#endif 