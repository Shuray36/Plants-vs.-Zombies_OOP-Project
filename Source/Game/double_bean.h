#pragma once
#include "plant.h"
#include "../Library/gameutil.h"
#include "pb.h"

class Double_bean :public Plant {
public:
	Double_bean() = default;

	int pb_x = 0;
	int pb_y = 0;
	void init();
	void show();
	void attack();
	void reload();
	Pb pb1;
	Pb pb2;
};
