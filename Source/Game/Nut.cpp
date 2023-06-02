#include "stdafx.h"
#include "../Core/Resource.h"
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>


void Nut::Init()
{
	Plant::Init();
	LoadBitmapByString({ "Plants_vs_Zombies_Image/plants/nut_one/nut_one_0.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_1.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_2.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_3.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_4.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_5.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_6.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_7.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_8.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_9.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_10.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_11.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_12.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_13.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_14.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_15.bmp",
		}, RGB(0, 0, 0));
	SetAnimation(100, false);
	ToggleAnimation();
	hp = 200;
}

