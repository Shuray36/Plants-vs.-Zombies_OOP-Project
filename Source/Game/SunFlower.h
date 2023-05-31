#pragma once
#include "plant.h"
#include "SunManager.h"
#include "../Library/gameutil.h"

class Sunflower:public Plant {
protected:
	game_framework::CMovingBitmap sunflower_getsun;
	game_framework::CMovingBitmap getsun;
	shared_ptr<SunManager> sun_manager;
public:
	Sunflower() = default;
	void init();
	void show();
	void skillUpdate();
	int getsun_flag = 0;
	int sunGetLeft();
	int sunGetTop();
	int cd_keep = 0;
	void setSunmanager(shared_ptr<SunManager> sm)
	{
		sun_manager = sm;
	}
};
