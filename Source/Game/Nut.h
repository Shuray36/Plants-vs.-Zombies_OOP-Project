#pragma once
#include "plant.h"

class Nut:public Plant {
public:
	Nut() :Plant() {}
	void init();
	void show();
};
