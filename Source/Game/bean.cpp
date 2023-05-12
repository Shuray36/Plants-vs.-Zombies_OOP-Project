#include "stdafx.h"
#include "../Core/Resource.h"
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

void Bean::init() {
	plant.LoadBitmapByString({ "Plants_vs_Zombies_Image/plants/bean/bean_0.bmp",
		"Plants_vs_Zombies_Image/plants/bean/bean_1.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_2.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_3.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_4.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_5.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_6.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_7.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_9.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_10.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_11.bmp", }, RGB(255, 255, 255));
	plant.SetTopLeft(999, 999);
	plant.SetAnimation(240, false);
	plant.ToggleAnimation();
	
	pb.LoadBitmapByString({ "Plants_vs_Zombies_Image/plants/PB.bmp" }, RGB(255, 255, 255));//440 285
	pb.SetTopLeft(plant.GetLeft() + 65, plant.GetTop());
}
void Bean::show() {
	if (hp > 0) {
		plant.ShowBitmap();
	}
	else {
		plant.SetTopLeft(999, 999);
	}
	if (pb_flag == 0)pb.ShowBitmap();

}
int Bean::PBgetleft() {
	return pb.GetLeft();
}
int Bean::PBgettop() {
	return pb.GetTop();
}

void Bean::attack(){
	pb.SetTopLeft(pb.GetLeft() + 3, pb.GetTop());
	if (pb.GetLeft() >= 950) {
		pb_flag = 1;
		cd = 0;
		reload();
	}
}

void Bean::reload() {
	pb.SetTopLeft(plant.GetLeft() + 65, plant.GetTop());
}

void Bean::leave() {
	pb.SetTopLeft(999, 999);
}
	
void Bean::SetTopLeft(int x, int y) {
	plant.SetTopLeft(x, y);
}
int Bean::GetLeft() {
	return plant.GetLeft();
}

int Bean::GetTop() {
	return plant.GetTop();
}