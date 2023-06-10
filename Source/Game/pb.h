#pragma once
#include "../Library/gameutil.h"
#include <vector>

#include "PZGameObject.h"

class Pb : public PZGameObject {
public:
	void init() {
		LoadBitmapByString({ "Plants_vs_Zombies_Image/plants/PB.bmp" }, RGB(255, 255, 255));//440 285
		SetSpeed({3.0f,0.0f});
		SetActive(true);
	}
	int show_flag = 1;
	void Update() override
	{
		PZGameObject::Update();
		if(GetPosition().x>950)
		{
			SetActive(false);
		}
	}
	void leave() {
		SetTopLeft(999, 999);
	}
};
