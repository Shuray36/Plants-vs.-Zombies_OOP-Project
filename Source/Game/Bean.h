#pragma once
#include "plant.h"
#include "../Library/gameutil.h"
#include "pb.h"

class Bean:public Plant {
public:
	Bean();
	void Init() override;
	void Show() override;
	void Update() override;
	void Attack() override;

	
	Pb pb;
	//game_framework::CMovingBitmap pb;

};
