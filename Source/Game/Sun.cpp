#include "stdafx.h"
#include "Sun.h"

Sun::Sun()
{
	LoadBitmapByString({ "Plants_vs_Zombies_Image/plants/sun/sun_0.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_1.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_2.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_3.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_4.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_5.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_6.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_7.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_8.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_9.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_10.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_11.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_12.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_13.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_14.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_15.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_16.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_17.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_18.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_19.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_20.bmp",
	"Plants_vs_Zombies_Image/plants/sun/sun_21.bmp", }, RGB(255, 255, 255));
	PZGameObject::Init();
	SetAnimation(120, false);
	ToggleAnimation();
}

void Sun::LoadSun(){
	LoadBitmapByString({"Plants_vs_Zombies_Image/sun/sun_0.bmp",
		"Plants_vs_Zombies_Image/sun/sun_1.bmp", 
		"Plants_vs_Zombies_Image/sun/sun_2.bmp", 
		"Plants_vs_Zombies_Image/sun/sun_3.bmp", 
		"Plants_vs_Zombies_Image/sun/sun_4.bmp", 
		"Plants_vs_Zombies_Image/sun/sun_5.bmp", 
		"Plants_vs_Zombies_Image/sun/sun_6.bmp", 
		"Plants_vs_Zombies_Image/sun/sun_7.bmp", 
		"Plants_vs_Zombies_Image/sun/sun_8.bmp", 
		"Plants_vs_Zombies_Image/sun/sun_9.bmp",
		"Plants_vs_Zombies_Image/sun/sun_10.bmp",
		"Plants_vs_Zombies_Image/sun/sun_11.bmp",
		"Plants_vs_Zombies_Image/sun/sun_12.bmp",
		"Plants_vs_Zombies_Image/sun/sun_13.bmp",
		"Plants_vs_Zombies_Image/sun/sun_14.bmp",
		"Plants_vs_Zombies_Image/sun/sun_15.bmp",
		"Plants_vs_Zombies_Image/sun/sun_16.bmp",
		"Plants_vs_Zombies_Image/sun/sun_17.bmp",
		"Plants_vs_Zombies_Image/sun/sun_18.bmp", 
		"Plants_vs_Zombies_Image/sun/sun_19.bmp", 
		"Plants_vs_Zombies_Image/sun/sun_20.bmp", 
		"Plants_vs_Zombies_Image/sun/sun_21.bmp", }, RGB(255, 255, 255));
	
	SetTopLeft(500, 0);
	SetAnimation(100, false);
	ToggleAnimation();
}

void Sun::SetGoal(Vector2 g)
{
	goal=g;
}

void Sun::Update()
{
	PZGameObject::Update();
	if(!GetActive()||Vector2::distance(GetPosition(),goal)<=(float)1.1)
	{
		SetSpeed({0,0});
	}
}
