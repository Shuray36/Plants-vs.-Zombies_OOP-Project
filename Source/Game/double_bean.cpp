#include "stdafx.h"
#include "../Core/Resource.h"
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

void Double_bean::init() {
	LoadBitmapByString({ "Plants_vs_Zombies_Image/plants/double_bean/double_bean_0.bmp",
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
		"Plants_vs_Zombies_Image/plants/double_bean/double_bean_14.bmp", }, RGB(255, 255, 255));
	SetTopLeft(999, 999);//371 292
	SetAnimation(240, false);
	ToggleAnimation();

	pb1.init();
	pb2.init();
	pb1.SetTopLeft(GetLeft() + 65, GetTop());
	pb2.SetTopLeft(GetLeft() + 65, GetTop());
	hp = 100;
}
void Double_bean::show() {
	if (hp > 0) {
		ShowBitmap();
	}
	else {
		SetTopLeft(300, 300);
	}
	//if (pb_flag == 0)pb.ShowBitmap();
	if (pb1.show_flag == 0) pb1.ShowBitmap();
	if (pb2.show_flag == 0) pb2.ShowBitmap();

}

void Double_bean::attack() {
	if (pb1.show_flag == 0)pb1.SetTopLeft(pb1.GetLeft() + 3, pb1.GetTop());
	if (pb2.show_flag == 0) pb2.SetTopLeft(pb2.GetLeft() + 3, pb2.GetTop());


	if (pb1.GetLeft() >= 950) {
		pb1.show_flag = 1;
		pb1.leave();
	}

	if (pb2.GetLeft() >= 950) {
		pb2.show_flag = 1;
		pb2.leave();
	}
}

void Double_bean::reload() {
	//pb.SetTopLeft(GetLeft() + 65, GetTop());

	if (pb1.show_flag == 1) pb1.SetTopLeft(GetLeft() + 65, GetTop());
	if (pb2.show_flag == 1) pb2.SetTopLeft(GetLeft() + 65, GetTop());
}

