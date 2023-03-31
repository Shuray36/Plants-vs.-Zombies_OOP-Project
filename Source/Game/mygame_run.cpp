#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "zombie.h"
#include <string>



using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////



CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	//遊戲剛開始的移動 往右到一定程度後 往回到原本樣式
	if (fight_background.GetLeft() >= (-350) && BG1_flag1==0){
		fight_background.SetTopLeft(fight_background.GetLeft() - 50, 0);
		if (fight_background.GetLeft() <= (-350)) {
			BG1_flag1 = 1;
		}
	}
	else if (fight_background.GetLeft() <= (350) && BG1_flag1==1) {
		time += 1;
		if (time >= 20) {
			fight_background.SetTopLeft(fight_background.GetLeft() + 50, 0);
			if (fight_background.GetLeft() >= (-80)) BG1_flag1 = 2;
		}
	}
	if (BG1_flag1 == 2) {        //遊戲跑換地圖後正式開始 
		if (CMovingBitmap::IsOverlap_new(zombie[0], sunflower[0])) { 
			zombie[0].SetTopLeft(zombie[0].GetLeft(), zombie[0].GetTop());
			zombie_change_flag = 1;
		}
		else zombie[0].SetTopLeft(zombie[0].GetLeft() - 3, zombie[0].GetTop() + 0);

		sun.SetTopLeft(sun.GetLeft() + 0, sun.GetTop() + 2);
		if (car_run == 1) { //除草機的細節
			if(car[2].GetLeft()<=1500)
			car[2].SetTopLeft(car[2].GetLeft() + 10, car[2].GetTop());
		}
	}
	

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	fight_background.LoadBitmapByString({ "Plants_vs_Zombies_Image/Scenes/BG1.bmp" });
	fight_background.SetTopLeft(0, 0);
	test.init();
	load_zombie_move();
	load_zombie_eat();
	load_sunflower();
	load_sunback();
	load_sun();
	load_car();
	load_sunflower_card();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	money += 50;
	sun_flag = 1;
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	/*
	if (nChar == VK_DOWN) {
		car[0].SetTopLeft(car[0].GetLeft() + 0, car[0].GetTop() + 5);
	}
	if (nChar == VK_UP) {
		car[0].SetTopLeft(car[0].GetLeft() + 0, car[0].GetTop() - 5);
	}
	if (nChar == VK_LEFT) {
		car[0].SetTopLeft(car[0].GetLeft() - 5, car[0].GetTop() + 0);
	}
	if (nChar == VK_RIGHT) {
		car[0].SetTopLeft(car[0].GetLeft() + 5, car[0].GetTop() + 0);
	}
	*/
	if (nChar == VK_DOWN) {
		car_run = 1;
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	
	if(CMovingBitmap::IsMouseClick(pointx,pointy,sun)){
		money += 150;
		sun_flag = 1;
	}
	if (CMovingBitmap::IsMouseClick(pointx, pointy, sunflower_card)&&money>=50){
		sunflower_click_show = true;
		
		money -= 50;
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	pointx = point.x;
	pointy = point.y;
	if(sunflower_click_show) sunflower[1].SetTopLeft(pointx - 32, pointy - 25);
	
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	fight_background.ShowBitmap();
	
	if (BG1_flag1 == 2) {
		if (zombie_change_flag == 0) {
			zombie[0].ShowBitmap();
		}
		else if (zombie_change_flag == 1) {
			zombie[1].SetTopLeft(sunflower[0].GetLeft()-20, sunflower[0].GetTop()-50);
			zombie[1].ShowBitmap();
		}
		
		sunflower[0].ShowBitmap();
		if(sunflower_click_show) sunflower[1].ShowBitmap();
		if(sun_flag==0) sun.ShowBitmap();
		car[0].ShowBitmap();
		car[1].ShowBitmap();
		car[2].ShowBitmap();
		car[3].ShowBitmap();
		car[4].ShowBitmap();
	}
	sunback.ShowBitmap();
	sunflower_card.ShowBitmap();
	test.show();
	draw_text();
	
}
//-------------------------------------------------------------------------------------------
void CGameStateRun::load_zombie_move() {
	zombie[0].LoadBitmapByString({ "Plants_vs_Zombies_Image/zombie/zombie_move/zom_0.bmp",
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
		}, RGB(255, 255, 255));
	zombie[0].SetTopLeft(950, 240);
	zombie[0].SetAnimation(120, false);
	zombie[0].ToggleAnimation();
}
void CGameStateRun::load_zombie_eat() {
	zombie[1].LoadBitmapByString({ "Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_0.bmp",
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
		"Plants_vs_Zombies_Image/zombie/zombie_eat/zom_eat_20.bmp",
		}, RGB(255, 255, 255));
	zombie[1].SetTopLeft(0, 0);
	zombie[1].SetAnimation(120, false);
	zombie[1].ToggleAnimation();
}

void CGameStateRun::load_sunflower() {
	for (int i = 0; i < 3; i++) {
		sunflower[i].LoadBitmapByString({ "Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_0.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_1.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_2.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_3.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_4.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_5.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_6.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_7.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_8.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_9.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_10.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_11.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_12.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_13.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_14.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_15.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_16.bmp",
		"Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_17.bmp",
		}, RGB(255, 255, 255));//315 310

		
	}
	sunflower[0].SetTopLeft(283, 285);
	sunflower[0].SetAnimation(100, false);
	sunflower[0].ToggleAnimation();

	sunflower[1].SetTopLeft(283, 185);
	sunflower[1].SetAnimation(100, false);
	sunflower[1].ToggleAnimation();
}

void CGameStateRun::load_sunback() {
	sunback.LoadBitmapByString({ "Plants_vs_Zombies_Image/SunBack.bmp", }, RGB(255, 255, 255));
	sunback.SetTopLeft(115, 0);

}
void CGameStateRun::load_sunflower_card() {
	sunflower_card.LoadBitmapByString({ "Plants_vs_Zombies_Image/card/sunflower_card/sunflower_card.bmp" }, RGB(255, 255, 255));
	sunflower_card.SetTopLeft(240, 0);
}
void CGameStateRun::load_sun() {
	sun.LoadBitmapByString({"Plants_vs_Zombies_Image/sun/sun_0.bmp",
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
	sun.SetTopLeft(500, 0);
	sun.SetAnimation(100, false);
	sun.ToggleAnimation();
}
void CGameStateRun::load_car() {
	car[0].LoadBitmapByString({ "Plants_vs_Zombies_Image/car/car.bmp" }, RGB(255, 255, 255));
	car[0].SetTopLeft(140, 125);
	car[1].LoadBitmapByString({ "Plants_vs_Zombies_Image/car/car.bmp" }, RGB(255, 255, 255));
	car[1].SetTopLeft(140, 220);
	car[2].LoadBitmapByString({ "Plants_vs_Zombies_Image/car/car.bmp" }, RGB(255, 255, 255));
	car[2].SetTopLeft(140, 315);
	car[3].LoadBitmapByString({ "Plants_vs_Zombies_Image/car/car.bmp" }, RGB(255, 255, 255));
	car[3].SetTopLeft(140, 405);
	car[4].LoadBitmapByString({ "Plants_vs_Zombies_Image/car/car.bmp" }, RGB(255, 255, 255));
	car[4].SetTopLeft(140, 500);
}
void CGameStateRun::draw_text() {
	CDC *pDC = CDDraw::GetBackCDC();
	//CDC *number = CDDraw::GetBackCDC();
	/* Print title */

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 0, 0, std::to_string(pointx));
	CTextDraw::Print(pDC, 50, 0, std::to_string(pointy));

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 157, 5, std::to_string(money));

	CDDraw::ReleaseBackCDC();
}