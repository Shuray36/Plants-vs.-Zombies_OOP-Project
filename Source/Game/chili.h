#pragma once
#include "plant.h"


class Chili :public Plant {
protected:
	game_framework::CMovingBitmap fire;
	vector<shared_ptr<Zombie>> zombies;
	int a[5] = { 40,140,240,340,440 };
public:
	Chili();
	
	void Init() override;
	void Attack() override;
	void Show() override;
	bool CanAttack() override;
	void SetZombies(vector<shared_ptr<Zombie>> z)
	{
		zombies = z;

	}
};