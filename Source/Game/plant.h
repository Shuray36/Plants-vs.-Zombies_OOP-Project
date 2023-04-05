#ifndef PLANT_H
#define PLANT_H

#include <string>

class Plant {
protected:
	int hp;
	int atk;
	int state;
	double speed;
	game_framework::CMovingBitmap a;
	game_framework::CMovingBitmap plant;
public:
	Plant() {}
	~Plant() = default;
	void show();
	virtual void init();
};
class Sunflower:public Plant{
public:
	Sunflower():Plant(){}
	void init();
	void show(); 
};
#endif 