#include "stdafx.h"
#include "../Core/Resource.h"
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

void Bean::init() {
	LoadBitmapByString({ "Plants_vs_Zombies_Image/plants/bean/bean_0.bmp",
		"Plants_vs_Zombies_Image/plants/bean/bean_1.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_2.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_3.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_4.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_5.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_6.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_7.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_9.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_10.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_11.bmp", }, RGB(255,255,255));
	SetTopLeft(999, 999);
	SetAnimation(240, false);
	ToggleAnimation();
	
	pb.init();
	pb.SetTopLeft(GetLeft() + 65, GetTop());

	hp=100;
}
void Bean::show() {
	if (hp > 0) {
		ShowBitmap();
	}
	else {
		SetTopLeft(999, 999);
	}
	pb.Show();

}

void Bean::attack(){
	pb.Update();
}

void Bean::reload() {
	pb.SetPosition( Vector2::add(GetPosition(),{65,0}));
}

void Bean::leave() {
	pb.SetActive(false);
}
	