#pragma once
#include "plant.h"

class Nut:public Plant {
public:
	Nut() = default;
	void init();
	void show();
};
