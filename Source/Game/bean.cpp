#include "stdafx.h"
#include "../Core/Resource.h"
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

Bean::Bean()
{
	SetImange({ "Plants_vs_Zombies_Image/plants/bean/bean_0.bmp",
		"Plants_vs_Zombies_Image/plants/bean/bean_1.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_2.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_3.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_4.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_5.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_6.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_7.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_9.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_10.bmp", 
		"Plants_vs_Zombies_Image/plants/bean/bean_11.bmp", }, RGB(255,255,255),240);
	hp=100;
}
void Bean::Init() {
	Plant::Init();
	pb.init();
}
void Bean::Show() {
	Plant::Show();
	pb.Show();
}

void Bean::Update(){
	Plant::Update();
	pb.Update();
}

void Bean::Attack() {
	pb.SetPosition( Vector2::add(GetPosition(),{65,0}));
	pb.SetActive(true);
}