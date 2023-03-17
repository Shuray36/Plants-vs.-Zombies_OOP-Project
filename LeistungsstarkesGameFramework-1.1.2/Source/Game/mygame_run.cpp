#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
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
		fight_background.SetTopLeft(fight_background.GetLeft() - 3, 0);
		if (fight_background.GetLeft() <= (-350)) {
			BG1_flag1 = 1;
		}
	}
	else if (fight_background.GetLeft() <= (350) && BG1_flag1==1) {
		time += 1;
		if (time >= 20) {
			fight_background.SetTopLeft(fight_background.GetLeft() + 3, 0);
			if (fight_background.GetLeft() >= (-80)) BG1_flag1 = 2;
		}
	}
	if (BG1_flag1 == 2) {
		if (CMovingBitmap::IsOverlap(zombie[0], sunflower)) {
			zombie[0].SetTopLeft(zombie[0].GetLeft(), zombie[0].GetTop());
			zombie_change_flag = 1;
		}
		else zombie[0].SetTopLeft(zombie[0].GetLeft() - 3, zombie[0].GetTop() + 0);
	}
	

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	fight_background.LoadBitmapByString({ "Plants_vs_Zombies_Image/Scenes/BG1.bmp" });
	fight_background.SetTopLeft(0, 0);
	
	load_zombie_move();
	load_zombie_eat();
	load_sunflower();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	pointx = point.x;
	pointy = point.y;
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
			zombie[1].SetTopLeft(sunflower.GetLeft(), sunflower.GetTop()-10);
			zombie[1].ShowBitmap();
		}
		
		sunflower.ShowBitmap();
	}
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
	zombie[0].SetTopLeft(950, 250);
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
	sunflower.LoadBitmapByString({ "Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_0.bmp",
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
		}, RGB(255, 255, 255));
	sunflower.SetTopLeft(283, 275);
	sunflower.SetAnimation(100, false);
	sunflower.ToggleAnimation();
}
void CGameStateRun::draw_text() {
	CDC *pDC = CDDraw::GetBackCDC();
	/* Print title */

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 0, 0, std::to_string(pointx));
	CTextDraw::Print(pDC, 50, 0, std::to_string(pointy));

	CDDraw::ReleaseBackCDC();
}