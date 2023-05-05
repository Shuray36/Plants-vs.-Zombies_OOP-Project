#include "stdafx.h"
#include "../Core/Resource.h"
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

void Plant::show() {
	a.ShowBitmap();
}
void Plant::init() {
	a.LoadBitmapByString({ "Plants_vs_Zombies_Image/zombie/zombie_move/zom_0.bmp" }, RGB(255, 255, 255));
	a.SetTopLeft(50, 50);
}