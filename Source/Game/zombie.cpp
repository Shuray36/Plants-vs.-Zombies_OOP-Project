#include "stdafx.h"
#include "../Core/Resource.h"
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

void Zombie::show() {
	if (hp > 0 && state==0) {
		//speed = 0;
		zombie.ShowBitmap();
	}
	else if (hp <= 0 && state==1) {
		
		zombie_die.SetTopLeft(zombie.GetLeft(), zombie.GetTop());
		zombie_die.ShowBitmap();
		speed = 0;
		die_flag = 1;
		if(zombie_die.IsAnimationDone()) state = 2;
	}
	else if (state == 2) {
		zombie.SetTopLeft(999, 999);
	}
	else if (state == 3) {
		zombie_headfall.SetTopLeft(zombie.GetLeft(), zombie.GetTop());
		zombie_headfall.ShowBitmap();
		speed = 0;
		die_flag = 1;
		if (zombie_headfall.IsAnimationDone()) state = 2;
	}
	else if (state == 4) {
		zombie_atk.SetTopLeft(zombie.GetLeft(), zombie.GetTop());
		zombie_atk.ShowBitmap();
		speed = 0;

	}
}
void Zombie::init() {
	zombie.LoadBitmapByString({ "Plants_vs_Zombies_Image/zombie/zombie_move/zom_0.bmp",
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_1.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_2.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_3.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_4.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_5.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_6.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_7.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_8.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_9.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_10.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_11.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_12.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_13.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_14.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_15.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_16.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_17.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_18.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_19.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_20.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_21.bmp"
		}, RGB(255, 255, 255));
	zombie.SetTopLeft(50, 50);
	zombie.SetAnimation(120, false);
	zombie.ToggleAnimation();
}
void Zombie::SetTopLeft(int x,int y) {
	zombie.SetTopLeft( x, y);
}

int Zombie::GetLeft()
{
	return zombie.GetLeft();
}

int Zombie::GetTop()
{
	return zombie.GetTop();
}
