#include "stdafx.h"
#include "../Core/Resource.h"
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

void Bucket_zombie::init() {
	zombie.LoadBitmapByString({ "Plants_vs_Zombies_Image/zombie/bucket_zombie/walk/bucket_zom_0.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/walk/bucket_zom_1.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/walk/bucket_zom_2.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/walk/bucket_zom_3.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/walk/bucket_zom_4.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/walk/bucket_zom_5.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/walk/bucket_zom_6.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/walk/bucket_zom_7.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/walk/bucket_zom_8.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/walk/bucket_zom_9.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/walk/bucket_zom_10.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/walk/bucket_zom_11.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/walk/bucket_zom_12.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/walk/bucket_zom_13.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/walk/bucket_zom_14.bmp",
		}, RGB(255, 255, 255));
	zombie.SetTopLeft(999, 999);//950 240
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

	zombie_atk.LoadBitmapByString({ "Plants_vs_Zombies_Image/zombie/bucket_zombie/eat/bucket_zom_eat_0.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/eat/bucket_zom_eat_1.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/eat/bucket_zom_eat_2.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/eat/bucket_zom_eat_3.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/eat/bucket_zom_eat_4.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/eat/bucket_zom_eat_5.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/eat/bucket_zom_eat_6.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/eat/bucket_zom_eat_7.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/eat/bucket_zom_eat_8.bmp",
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/eat/bucket_zom_eat_9.bmp", 
		"Plants_vs_Zombies_Image/zombie/bucket_zombie/eat/bucket_zom_eat_10.bmp", }, RGB(255, 255, 255));
	zombie_atk.SetTopLeft(zombie.GetLeft(), zombie.GetTop());
	zombie_atk.SetAnimation(120, false);
	zombie_atk.ToggleAnimation();
}

void Bucket_zombie::show() {
	if (hp > 0 && state == 0) {
		//speed = 0;
		zombie.ShowBitmap();
	}
	else if (hp <= 0 && state == 1) {

		zombie_die.SetTopLeft(zombie.GetLeft(), zombie.GetTop());
		zombie_die.ShowBitmap();
		speed = 0;
		die_flag = 1;
		if (zombie_die.IsAnimationDone()) state = 2;
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
void Bucket_zombie::loadstate(int state) {

}