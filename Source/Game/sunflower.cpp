#include "stdafx.h"
#include "../Core/Resource.h"
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>


void Sunflower::Init()
{
	{
	SetImange({ "Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_0.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_1.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_2.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_3.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_4.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_5.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_6.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_7.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_8.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_9.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_10.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_11.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_12.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_13.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_14.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_15.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_16.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_17.bmp",
		}, RGB(255, 255, 255),100); //315 310}, RGB(255, 255, 255);
	}
	Plant::Init();
	hp = 100;
#pragma region 
	sunflower_getsun.LoadBitmapByString({ "Plants_vs_Zombies_Image/plants/sunflower_getsun/sunflower_getsun_0.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_getsun/sunflower_getsun_1.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_getsun/sunflower_getsun_2.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_getsun/sunflower_getsun_3.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_getsun/sunflower_getsun_4.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_getsun/sunflower_getsun_5.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_getsun/sunflower_getsun_6.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_getsun/sunflower_getsun_7.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_getsun/sunflower_getsun_8.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_getsun/sunflower_getsun_9.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_getsun/sunflower_getsun_10.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_getsun/sunflower_getsun_11.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_getsun/sunflower_getsun_12.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_getsun/sunflower_getsun_13.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_getsun/sunflower_getsun_14.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_getsun/sunflower_getsun_15.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_getsun/sunflower_getsun_16.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_getsun/sunflower_getsun_17.bmp", }, RGB(255, 255, 255));
#pragma endregion 
	sunflower_getsun.SetTopLeft(GetLeft(), GetTop());
	sunflower_getsun.SetAnimation(120, false);
	sunflower_getsun.ToggleAnimation();
}

void Sunflower::Attack()
{
	sun_manager->makeSun({(float)GetLeft() + 65, (float)GetTop() });
}



void Sunflower::show() {
	if (hp > 0 && state == 0) {
		ShowBitmap();
	}
	else if (hp > 0 && state == 1) {
		sunflower_getsun.SetTopLeft(GetLeft(), GetTop());
		sunflower_getsun.ShowBitmap();
		if (cd_keep >= 120)
		{
			cd = 0;
			cd_keep = 0;
			getsun_flag = 1;
			sun_manager->makeSun({(float)GetLeft() + 65, (float)GetTop() });
			state = 0;
		}
	}
}

void Sunflower::skillUpdate()
{
	cd += 1;
	if (cd >= 245) {
		cd_keep += 1;
		state = 1;
	}
}


void Sunflower::setSunmanager(shared_ptr<SunManager> sm)
{
	sun_manager = sm;
}
