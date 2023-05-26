#ifndef PLANT_H
#define PLANT_H

#include <string>

#include "PZGameObject.h"


class Plant :public PZGameObject{
protected:
	int state;
	Vector2 coordinate;
	
public:
	Plant() = default;
	~Plant() = default;
	void show();
	void init();
	void SetCoordinate(int x,int y);
	void SetCoordinate(float x,float y);
	int GetCoordinateX();
	int GetCoordinateY();
	int atk_speed = 0;
	int hp = 100;
	int cd = 0;
	int die_flag = 0;
};
#endif 