#pragma once
#include "plant.h"
#include "../Library/gameutil.h"

class Sunflower:public Plant {
protected:
	game_framework::CMovingBitmap sunflower_getsun;
	game_framework::CMovingBitmap getsun;
public:
	Sunflower() = default;
	void init();
	void show();
	int state = 0;
	int getsun_flag = 0;
	int sunGetLeft();
	int sunGetTop();
	int cd_keep = 0;
};
