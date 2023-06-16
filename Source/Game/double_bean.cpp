#include "stdafx.h"
#include "../Core/Resource.h"
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

Double_bean::Double_bean() {
	SetImange({ "Plants_vs_Zombies_Image/plants/double_bean/double_bean_0.bmp",
		"Plants_vs_Zombies_Image/plants/double_bean/double_bean_1.bmp",
		"Plants_vs_Zombies_Image/plants/double_bean/double_bean_2.bmp",
		"Plants_vs_Zombies_Image/plants/double_bean/double_bean_3.bmp",
		"Plants_vs_Zombies_Image/plants/double_bean/double_bean_4.bmp",
		"Plants_vs_Zombies_Image/plants/double_bean/double_bean_5.bmp",
		"Plants_vs_Zombies_Image/plants/double_bean/double_bean_6.bmp",
		"Plants_vs_Zombies_Image/plants/double_bean/double_bean_7.bmp",
		"Plants_vs_Zombies_Image/plants/double_bean/double_bean_8.bmp",
		"Plants_vs_Zombies_Image/plants/double_bean/double_bean_9.bmp",
		"Plants_vs_Zombies_Image/plants/double_bean/double_bean_10.bmp",
		"Plants_vs_Zombies_Image/plants/double_bean/double_bean_11.bmp",
		"Plants_vs_Zombies_Image/plants/double_bean/double_bean_12.bmp", 
		"Plants_vs_Zombies_Image/plants/double_bean/double_bean_13.bmp",
		"Plants_vs_Zombies_Image/plants/double_bean/double_bean_14.bmp", }, RGB(255, 255, 255),120);
	hp = 100;
}

void Double_bean::Attack()
{
	Bean::Attack();
	SetAttackCounter(2600 - GetAttackCycle());
}


