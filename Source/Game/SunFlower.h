#pragma once
#include "plant.h"
#include "SunManager.h"
#include "../Library/gameutil.h"

class Sunflower:public Plant {
protected:
	game_framework::CMovingBitmap sunflower_getsun;
	shared_ptr<SunManager> sun_manager;
public:
	Sunflower();
	void Init() override;
	void Attack() override;
	void Show() override;
	void SetPosition(Vector2 position);
	void setSunmanager(shared_ptr<SunManager> sm);
};
