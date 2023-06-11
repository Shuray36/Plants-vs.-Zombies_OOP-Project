#include "stdafx.h"
#include "../Core/Resource.h"
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

void Chili::init() {
	LoadBitmapByString({ "Plants_vs_Zombies_Image/plants/chili/chili_0.bmp",
	"Plants_vs_Zombies_Image/plants/chili/chili_1.bmp",
	"Plants_vs_Zombies_Image/plants/chili/chili_2.bmp",
	"Plants_vs_Zombies_Image/plants/chili/chili_3.bmp",
	"Plants_vs_Zombies_Image/plants/chili/chili_4.bmp",
	"Plants_vs_Zombies_Image/plants/chili/chili_5.bmp",
	"Plants_vs_Zombies_Image/plants/chili/chili_6.bmp",
	"Plants_vs_Zombies_Image/plants/chili/chili_7.bmp" , }, RGB(0, 0, 0));
	SetTopLeft(250, 250);
	SetAnimation(120, false);
	ToggleAnimation();

}

void Chili::show() {
	ShowBitmap();
}