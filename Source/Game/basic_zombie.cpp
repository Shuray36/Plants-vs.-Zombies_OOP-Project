#include "stdafx.h"
#include "../Core/Resource.h"
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

void Basic_zombie::init() {
	PZGameObject::Init();
	LoadBitmapByString({ "Plants_vs_Zombies_Image/zombie/zombie_move/zom_0.bmp",
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
		}, RGB(255,255,255));
	SetTopLeft(999,999);//950 240
	SetAnimation(120, false);

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
	zombie_die.SetTopLeft(GetLeft(), GetTop());
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
	zombie_headfall.SetTopLeft(GetLeft(), GetTop());
	zombie_headfall.SetAnimation(120, true);
	zombie_headfall.ToggleAnimation();

	
	zombie_atk.LoadBitmapByString({ "Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_0.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_1.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_2.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_3.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_4.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_5.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_6.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_7.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_8.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_9.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_10.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_11.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_12.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_13.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_14.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_15.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_16.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_17.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_18.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_19.bmp", 
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_20.bmp", }, RGB(255, 255, 255));
	zombie_atk.SetTopLeft(GetLeft(), GetTop());
	zombie_atk.SetAnimation(120, false);
	zombie_atk.ToggleAnimation();
	
	zombie_fire.LoadBitmapByString({ "Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_0.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_1.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_2.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_3.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_4.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_5.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_6.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_7.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_8.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_9.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_10.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_11.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_12.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_13.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_14.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_15.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_16.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_17.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_18.bmp",
		"Plants_vs_Zombies_Image/zombie/zombie_fire/BoomDie_19.bmp", }, RGB(255, 255, 255));
	zombie_fire.SetAnimation(120, true);
	zombie_fire.ToggleAnimation();

	SetSpeed({ -0.5f,0.0f });

	attack = 30;
}
