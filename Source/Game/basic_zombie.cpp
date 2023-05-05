#include "stdafx.h"
#include "../Core/Resource.h"
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

void Basic_zombie::init() {
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
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_14.bmp",
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_15.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_16.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_17.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_18.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_19.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_20.bmp" ,
	"Plants_vs_Zombies_Image/zombie/zombie_move/zom_21.bmp"
		}, RGB(255, 255, 255));
	zombie.SetTopLeft(950, 240);
	zombie.SetAnimation(120, false);

	zombie_die.LoadBitmapByString({ "Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_0.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_1.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_2.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_3.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_4.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_5.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_6.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_7.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_8.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_9.bmp" ,
		}, RGB(255, 255, 255));
	zombie_die.SetTopLeft(zombie.GetLeft(), zombie.GetTop());
	zombie_die.SetAnimation(120, true);
	zombie_die.ToggleAnimation();


	zombie_headfall.LoadBitmapByString({ "Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_0.bmp" , 
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_1.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_2.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_3.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_4.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_5.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_6.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_7.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_8.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_9.bmp" , 
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_10.bmp" , 
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_11.bmp" , }, RGB(255, 255, 255));
	zombie_headfall.SetTopLeft(zombie.GetLeft(), zombie.GetTop());
	zombie_headfall.SetAnimation(120, true);
	zombie_headfall.ToggleAnimation();
}

void Basic_zombie::show() {
	if (hp > 0 && state==0) {
		zombie.ShowBitmap();
	}
	else if (hp <= 0 && state==1) {
		
		zombie_die.SetTopLeft(zombie.GetLeft(), zombie.GetTop());
		zombie_die.ShowBitmap();
		speed = 0;
		if(zombie_die.IsAnimationDone()) state = 2;
	}
	else if (state == 2) {
		zombie.SetTopLeft(999, 999);
	}
	else if (state == 3) {
		zombie_headfall.SetTopLeft(zombie.GetLeft(), zombie.GetTop());
		zombie_headfall.ShowBitmap();
		speed = 0;

		if (zombie_headfall.IsAnimationDone()) state = 2;
	}
}

int Basic_zombie::GetLeft() {
	return zombie.GetLeft();
}

int Basic_zombie::GetTop() {
	return zombie.GetTop();
}


void Basic_zombie::loadstate(int state) {
	
}