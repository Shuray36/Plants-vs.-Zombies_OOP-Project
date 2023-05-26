#pragma once
#include "plant.h"
#include "../Library/gameutil.h"

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
