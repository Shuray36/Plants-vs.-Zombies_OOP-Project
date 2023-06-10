#pragma once
#include "plant.h"
#include "../Library/gameutil.h"
#include "pb.h"

class Bean:public Plant {
public:
	Bean() = default;
	void init();
	void show();
	void attack();
	void reload();
	void leave();

	
	Pb pb;
	//game_framework::CMovingBitmap pb;

};
