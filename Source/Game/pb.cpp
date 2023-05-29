#include "stdafx.h"
#include "pb.h"

void Pb::init() {
	LoadBitmapByString({ "Plants_vs_Zombies_Image/plants/PB.bmp" }, RGB(255, 255, 255));//440 285
	SetTopLeft(999, 999);

}

void Pb::leave() {
	SetTopLeft(999, 999);
}