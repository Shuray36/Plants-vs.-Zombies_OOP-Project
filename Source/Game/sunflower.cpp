#include "stdafx.h"
#include "../Core/Resource.h"
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>



void Sunflower::init() {
	LoadBitmapByString({ "Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_0.bmp",
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
		}, RGB(255, 255, 255)); //315 310}, RGB(255, 255, 255);
	SetTopLeft(999, 999); //283 285
	SetAnimation(100, false);
	ToggleAnimation();

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
	sunflower_getsun.SetTopLeft(GetLeft(), GetTop());
	sunflower_getsun.SetAnimation(120, false);
	sunflower_getsun.ToggleAnimation();

	getsun.LoadBitmapByString({ "Plants_vs_Zombies_Image/plants/sun/sun_0.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_1.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_2.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_3.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_4.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_5.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_6.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_7.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_8.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_9.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_10.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_11.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_12.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_13.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_14.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_15.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_16.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_17.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_18.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_19.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_20.bmp",
		"Plants_vs_Zombies_Image/plants/sun/sun_21.bmp", }, RGB(255, 255, 255));

	getsun.SetTopLeft(GetLeft(), GetTop());
	getsun.SetAnimation(120, false);
	getsun.ToggleAnimation();
}

void Sunflower::show() {
	if (hp > 0 && state == 0) {
		ShowBitmap();
	}
	else if (hp > 0 && state == 1) {
		sunflower_getsun.SetTopLeft(GetLeft(), GetTop());
		sunflower_getsun.ShowBitmap();

		if (cd_keep >= 120) {
			cd = 0;
			cd_keep = 0;
			getsun_flag = 1;
			getsun.SetTopLeft(GetLeft() + 65, GetTop());
			state = 0;
		}

	}
	if (getsun_flag == 1) {
		getsun.ShowBitmap();
	}
}

int Sunflower::sunGetLeft() {
	return getsun.GetLeft();
}
int Sunflower::sunGetTop() {
	return getsun.GetTop();
}