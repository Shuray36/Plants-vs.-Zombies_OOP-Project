#include "stdafx.h"
#include "../Core/Resource.h"
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

Chili::Chili() {
	SetImange({ "Plants_vs_Zombies_Image/plants/chili/chili_0.bmp",
	"Plants_vs_Zombies_Image/plants/chili/chili_1.bmp",
	"Plants_vs_Zombies_Image/plants/chili/chili_2.bmp",
	"Plants_vs_Zombies_Image/plants/chili/chili_3.bmp",
	"Plants_vs_Zombies_Image/plants/chili/chili_4.bmp",
	"Plants_vs_Zombies_Image/plants/chili/chili_5.bmp",
	"Plants_vs_Zombies_Image/plants/chili/chili_6.bmp",
	"Plants_vs_Zombies_Image/plants/chili/chili_7.bmp" , }, RGB(0, 0, 0), 120);
	
	hp = 900;
}

void Chili::Init() {
	Plant::Init();
#pragma region
	fire.LoadBitmapByString({"Plants_vs_Zombies_Image/plants/chili/fire/fire_0.bmp",
		"Plants_vs_Zombies_Image/plants/chili/fire/fire_1.bmp", 
		"Plants_vs_Zombies_Image/plants/chili/fire/fire_2.bmp", 
		"Plants_vs_Zombies_Image/plants/chili/fire/fire_3.bmp", 
		"Plants_vs_Zombies_Image/plants/chili/fire/fire_4.bmp", 
		"Plants_vs_Zombies_Image/plants/chili/fire/fire_5.bmp", 
		"Plants_vs_Zombies_Image/plants/chili/fire/fire_6.bmp", 
		"Plants_vs_Zombies_Image/plants/chili/fire/fire_7.bmp", }, RGB(0, 0, 0));
#pragma endregion
	fire.SetTopLeft(200, 240);
	fire.SetAnimation(120, true);
	fire.ToggleAnimation();
}

bool Chili::CanAttack() {
	if (GetFrameIndexOfBitmap() == 7) {
		return true;
	}
	return false;
}
void Chili::Attack() {
	
	
	for (auto&z : zombies) {
		if (z->GetTop() == a[GetCoordinateY()]) {
			z->state = 5;
		}
		
	}
	if (fire.GetFrameIndexOfBitmap() == 7) {
		SetActive(false);
	}
	
}

void Chili::Show() {

	if (GetFrameIndexOfBitmap()==7)
	{
		fire.ShowBitmap();
	}
	else
	{
		Plant::Show();
	}
}
