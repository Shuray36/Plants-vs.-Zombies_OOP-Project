#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
//#include "zombie.h"
//#include "plant.h"
#include <string>
#include <random>



enum class plant {
	SUN_FLOWER=0,
	BEAN_PLANT=1,
	NUT_PLANT=2
};

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
	if (fight_background.GetLeft() >= (-350) && BG1_flag1 == 0) {
		fight_background.SetTopLeft(fight_background.GetLeft() - 10, 0);
		if (fight_background.GetLeft() <= (-350)) {
			BG1_flag1 = 1;
		}
	}
	else if (fight_background.GetLeft() <= (350) && BG1_flag1 == 1) {
		time += 1;
		if (time >= 20) {
			fight_background.SetTopLeft(fight_background.GetLeft() + 10, 0);
			if (fight_background.GetLeft() >= (-50)) BG1_flag1 = 2;
		}
	}
	if (BG1_flag1 == 2) {        //遊戲跑換地圖後正式開始 
	
		for (int i = 0; i < zombie_max; i++){
			if (basic_zombie[i].die_flag == 0 && zombie_index >= 0)basic_zombie[zombie_index].speed = -1;
			basic_zombie[i].SetTopLeft(basic_zombie[i].GetLeft() + basic_zombie[i].speed, basic_zombie[i].GetTop());
		}
		//------------------------------------------------------
		//花開始落下--------------------------------------------
		sun_cooldown += 1;
		if (sun_cooldown >= 700) {
			int r = (rand() % 900 + 100);
			sun.SetTopLeft(r, 0);
			sun_flag = 0;
			sun_cooldown = 0;
		}
		//植物攻擊-----------
		for (int i = 0; i < 20; i++) bean_plant[i].cd += 1;
		for (int i = 0; i < 20; i++) {
			if (bean_plant[i].cd >= 50) {
				bean_plant[i].pb_flag = 0;
				bean_plant[i].attack();
			}
			for (int j = 0; j < zombie_max; j++) {
				if (bean_plant[i].PBgetleft() <= basic_zombie[j].GetLeft() + 50 && bean_plant[i].PBgetleft() >= basic_zombie[j].GetLeft() + 45 && bean_plant[i].PBgettop() <= basic_zombie[j].GetTop() + 60 && bean_plant[i].PBgettop() >= basic_zombie[j].GetTop() - 0 && basic_zombie[j].die_flag == 0) {
					bean_plant[i].leave();
					bean_plant[i].pb_flag = 1;
					bean_plant[i].cd = 0;
					basic_zombie[j].hp -= 10;
					if (basic_zombie[j].hp <= 0) {
						basic_zombie[j].state = 1;
						basic_zombie[j].die_flag = 1;
					}

					bean_plant[i].reload();
				}
			}

		}

		//-----------------------

		//殭屍攻擊---------------

		for (int i = 0; i < (zombie_max-1); i++) {
			for (int j = 0; j < 20; j++) {
				if (basic_zombie[i].GetLeft() <= bean_plant[j].GetLeft() + 30 && basic_zombie[i].GetLeft() >= bean_plant[j].GetLeft() + 20 && basic_zombie[i].GetTop() <= bean_plant[j].GetTop() + 0 && basic_zombie[i].GetTop() >= bean_plant[j].GetTop() -60 && basic_zombie[i].die_flag == 0) {
					basic_zombie[i].state = 4;
					basic_zombie[i].cd += 1;
					if (basic_zombie[i].cd >= 100 && bean_plant[j].hp > 0) {
						basic_zombie[i].cd = 0;
						bean_plant[j].hp -= 30;
					}
					if (bean_plant[j].hp <= 0) {
						for (int k = 0; k < (zombie_max - 1); k++) {
							if (basic_zombie[k].state == 4) {
								basic_zombie[k].cd = 0;
								basic_zombie[k].state = 0;
								basic_zombie[k].speed = -1;
							}
						}
					}
				}
				//堅果--------------------------------------
				if (basic_zombie[i].GetLeft() <= nut[j].GetLeft() + 30 && basic_zombie[i].GetLeft() >= nut[j].GetLeft() + 20 && basic_zombie[i].GetTop() <= nut[j].GetTop() + 0 && basic_zombie[i].GetTop() >= nut[j].GetTop() - 60 && basic_zombie[i].die_flag == 0) {
					basic_zombie[i].state = 4;
					basic_zombie[i].cd += 1;
					if (basic_zombie[i].cd >= 100 && nut[j].hp > 0) {
						basic_zombie[i].cd = 0;
						nut[j].hp -= 70;

					}
					if (nut[j].hp <= 0) {
						for (int k = 0; k < (zombie_max - 1); k++) {
							if (basic_zombie[k].state == 4) {
								basic_zombie[k].cd = 0;
								basic_zombie[k].state = 0;
								basic_zombie[k].speed = -1;
							}
						}
						clear_seat(nut[j].coordinate_x, nut[j].coordinate_y);
					}
				}
				//太陽花-------------------------------------
				if (basic_zombie[i].GetLeft() <= sunflower[j].GetLeft() + 30 && basic_zombie[i].GetLeft() >= sunflower[j].GetLeft() + 20 && basic_zombie[i].GetTop() <= sunflower[j].GetTop() + 0 && basic_zombie[i].GetTop() >= sunflower[j].GetTop() - 60 && basic_zombie[i].die_flag == 0) {
					basic_zombie[i].state = 4;
					//zombie_atk_time += 1;
					basic_zombie[i].cd += 1;
					if (basic_zombie[i].cd >= 100 && sunflower[j].hp > 0) {
						basic_zombie[i].cd = 0;
						sunflower[j].hp -= 30;
					}
					if (sunflower[j].hp <= 0) {
						for (int k = 0; k < (zombie_max - 1); k++) {
							if (basic_zombie[k].state == 4) {
								//zombie_atk_time = 0;
								basic_zombie[k].cd = 0;
								basic_zombie[k].state = 0;
								basic_zombie[k].speed = -1;
							}
						}
					}
				}
				//--------------------------------------------
			}
		}

		//-----------------------
		sun.SetTopLeft(sun.GetLeft() + 0, sun.GetTop() + 2);
		for (int i = 0; i < (zombie_max - 1); i++) {
			if (car[2].GetLeft() >= basic_zombie[i].GetLeft() + 0 && car[2].GetLeft() <= basic_zombie[i].GetLeft() + 100 && car[2].GetTop() >= basic_zombie[i].GetTop() + 0 && car[2].GetTop() <= basic_zombie[i].GetTop() + 100) {
				car_run = 1;
				basic_zombie[i].state = 3;
			}
		}
		
		//------------------------------------------------------
		if (car_run == 1) { //除草機的細節
			if (car[2].GetLeft() <= 1500) car[2].SetTopLeft(car[2].GetLeft() + 10, car[2].GetTop());
		}
		
		//太陽花技能----------------------
		for (int i = 0; i < 45; i++) {
			sunflower[i].cd += 1;
			if (sunflower[i].cd >= 245) {
				sunflower[i].cd_keep += 1;
				sunflower[i].state = 1;
			}
		}
		//--------------------------------
		for (int i = 0; i < (zombie_index - 1); i++) {
			if (basic_zombie[i].GetLeft() < 500) {
				end_flag = 1;
			}
		}
		
		//結束---------------------
		/*
		if (basic_zombie[2].die_flag == 1) {
			overflag = 1;
			//GotoGameState(GAME_STATE_OVER);
		}
		if (overflag == 1) {
			overtime += 1;
			if (overtime == 100) {
				basic_zombie[2].die_flag = 0;
				overflag = 0;
				overtime = 0;
				GotoGameState(GAME_STATE_OVER);
			}
		}
		*/
		
		
	}
	

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	fight_background.LoadBitmapByString({ "Plants_vs_Zombies_Image/Scenes/BG1.bmp" });
	fight_background.SetTopLeft(0, 0);
	for (int i = 0; i < 10; i++)basic_zombie[i].init();
	for (int i = 0; i < 10; i++) basic_zombie[i].speed = 0;
	for (int i = 0; i < 20; i++) nut[i].init();
	for (int i = 0; i < 20; i++) bean_plant[i].init();
	for (int i = 0; i < plant_place_max; i++) sunflower[i].init();
	
	load_bean_plant_with_mouse();
	load_nut_with_mouse();
	load_sunflower();//with_mouse
	load_sunback();
	load_sun();
	load_car();
	load_sunflower_card();
	load_sunflower_gray_card();
	load_peashooter_gray_card();
	load_peashooter_card();
	load_nut_card();
	load_nut_gray_card();
	load_zombie_win_picture();
	
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DOWN) car_run = 1;
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	
	if(CMovingBitmap::IsMouseClick(pointx,pointy,sun)){
		money += 300;
		sun_flag = 1;
	}
	if (CMovingBitmap::IsMouseClick(pointx, pointy, peashooter_card)&&money>=100) {
		pershooter_show_flag = 1;
		item = 1;
		place_flag = 1;
		bean_plant_with_mouse_show = 1;

		
	}
	if (CMovingBitmap::IsMouseClick(pointx, pointy, sunflower_card)&&money>=50){
		sunflower_show_flag = 1;
		sunflower_index += 1;
		item = 0;
		place_flag = 1;
		sunflower_with_mouse_show = 1;
	}
	if (CMovingBitmap::IsMouseClick(pointx, pointy, nut_card) && money >= 75) {
		nut_show_flag = 1;
		//nut_plant_index += 1;
		item = 2;
		place_flag = 1;
		nut_with_mouse_show = 1;
	}

	for (int i = 0; i < 45; i++) {
		if (pointx >= sunflower[i].sunGetLeft() - 50 && pointx <= sunflower[i].sunGetLeft() + 50 && pointy >= sunflower[i].sunGetTop() - 50 && pointy <= sunflower[i].sunGetTop() + 50) {
			sunflower[i].getsun_flag = 0;
			money += 50;
		}
	}


	if (place_flag == 1) {
		place_seat(pointx, pointy, item);
	}


}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	pointx = point.x;
	pointy = point.y;
	if (sunflower_with_mouse_show == 1) {
		sunflower_with_mouse.SetTopLeft(pointx - 32, pointy - 25);
	}
	if (bean_plant_with_mouse_show == 1) {
		bean_plant_with_mouse.SetTopLeft(pointx - 32, pointy - 25);
	}
	if (nut_with_mouse_show == 1) {
		nut_plant_with_mouse.SetTopLeft(pointx - 32, pointy - 25);
	}
	
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
	for (int i = 0; i < plant_place_max; i++) sunflower[i].show();
	for (int i = 0; i < 20; i++) nut[i].show();
	for (int i = 0; i < 20; i++) bean_plant[i].show();


	if (BG1_flag1 == 2) {
		if (sunflower_with_mouse_show == 1) {
			sunflower_with_mouse.ShowBitmap();
		}
		else if (sunflower_with_mouse_show == 0) {
			sunflower_with_mouse.SetTopLeft(999, 999);
		}
		if (bean_plant_with_mouse_show == 1) {
			bean_plant_with_mouse.ShowBitmap();
		}
		else if (bean_plant_with_mouse_show == 0) {
			bean_plant_with_mouse.SetTopLeft(999, 999);
		}
		if (nut_with_mouse_show == 1) {
			nut_plant_with_mouse.ShowBitmap();
		}
		else if (nut_with_mouse_show == 0) {
			nut_plant_with_mouse.SetTopLeft(999, 999);
		}

		if (place_flag == 0) {
			bean_plant_with_mouse_show = 0;
			nut_with_mouse_show = 0;
		}

		//物件跟隨滑鼠----------------------------------------------------
	
		
		for (int i = 0; i < (zombie_max - 1); i++)  basic_zombie[i].show();
		call_time += 1;
		if (call_time == 200) {
			if (zombie_index < (zombie_max-1)) {
				zombie_index += 1; 
				basic_zombie[zombie_index].SetTopLeft(950, 240);
			}
			call_time = 0;
		}
		//召喚殭屍------------------------------------


		if (sunflower_show_flag == 0) {
			sunflower[sunflower_index].SetTopLeft(999, 999);
			sunflower[sunflower_index].show();
		}
		else if (sunflower_show_flag == 1) {
			sunflower[sunflower_index].show();
		}
		if(sun_flag==0) sun.ShowBitmap();
		for (int i = 0; i < 5; i++) car[i].ShowBitmap();

		if (pershooter_show_flag == 0) {
			bean_plant[bean_plant_index].SetTopLeft(999, 999);
			bean_plant[bean_plant_index].show();
		}
		else if (pershooter_show_flag == 1) {
			bean_plant[bean_plant_index].show();
		}
		
		if (end_flag == 2) {
			end_time += 1;
			if (end_time < 200) {
				zombie_win_picture.ShowBitmap();
			}
			else {
				end_flag = 0;
				end_time = 0;
				GotoGameState(GAME_STATE_OVER);
			}
		}
	}
	sunback.ShowBitmap();
	sunflower_card.ShowBitmap();
	if (money >= 100) {
		pershooter_flag = 1;
	}
	else if (money < 100) {
		pershooter_flag = 0;
	}
	if (money >= 50) {
		sunflower_flag = 1;
	}
	else if (money < 50) {
		sunflower_flag = 0;
	}
	if (money >= 75) {
		nut_flag = 1;
	}
	else if (money < 75) {
		nut_flag = 0;
	}


	if (pershooter_flag == 0) {
		peashooter_gray_card.ShowBitmap();
	}
	else if (pershooter_flag == 1) {
		peashooter_card.ShowBitmap();
	}
	if (sunflower_flag == 0) {
		sunflower_gray_card.ShowBitmap();
	}
	else if (sunflower_flag == 1) {
		sunflower_card.ShowBitmap();
	}
	if (nut_flag == 0) {
		nut_gray_card.ShowBitmap();
	}
	else if (nut_flag == 1) {
		nut_card.ShowBitmap();
	}


	draw_text();
	
}
//-------------------------------------------------------------------------------------------



void CGameStateRun::load_sunflower() {
	
	sunflower_with_mouse.LoadBitmapByString({ "Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_0.bmp",
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

		
	sunflower_with_mouse.SetTopLeft(1000, 1000);
	sunflower_with_mouse.SetAnimation(100, false);
	sunflower_with_mouse.ToggleAnimation();
	

}
void CGameStateRun::load_sunback() {
	sunback.LoadBitmapByString({ "Plants_vs_Zombies_Image/SunBack.bmp", }, RGB(255, 255, 255));
	sunback.SetTopLeft(115, 0);

}
void CGameStateRun::load_sunflower_card() {
	sunflower_card.LoadBitmapByString({ "Plants_vs_Zombies_Image/card/sunflower_card/sunflower_card.bmp" }, RGB(255, 255, 255));
	sunflower_card.SetTopLeft(240, 0);
}
void CGameStateRun::load_sunflower_gray_card() {
	sunflower_gray_card.LoadBitmapByString({ "Plants_vs_Zombies_Image/card/sunflower_card/sunflower_gray_card.bmp" }, RGB(255, 255, 255));
	sunflower_gray_card.SetTopLeft(240, 0);
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
void CGameStateRun::load_peashooter_gray_card() {
	peashooter_gray_card.LoadBitmapByString({ "Plants_vs_Zombies_Image/card/peashooter_card/peashooter_gray.bmp" }, RGB(255, 255, 255));
	peashooter_gray_card.SetTopLeft(350, 0);
}
void CGameStateRun::load_peashooter_card() {
	peashooter_card.LoadBitmapByString({ "Plants_vs_Zombies_Image/card/peashooter_card/peashooter.bmp" }, RGB(255, 255, 255));
	peashooter_card.SetTopLeft(350, 0);
}

void CGameStateRun::load_bean_plant_with_mouse() {
	bean_plant_with_mouse.LoadBitmapByString({ "Plants_vs_Zombies_Image/plants/bean/bean_0.bmp",
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

	bean_plant_with_mouse.SetTopLeft(999, 999);
	bean_plant_with_mouse.SetAnimation(240, false);
	bean_plant_with_mouse.ToggleAnimation();

}

void CGameStateRun::load_nut_with_mouse() {
	nut_plant_with_mouse.LoadBitmapByString({ "Plants_vs_Zombies_Image/plants/nut_one/nut_one_0.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_1.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_2.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_3.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_4.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_5.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_6.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_7.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_8.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_9.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_10.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_11.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_12.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_13.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_14.bmp",
		"Plants_vs_Zombies_Image/plants/nut_one/nut_one_15.bmp",
		}, RGB(0, 0, 0));

	nut_plant_with_mouse.SetTopLeft(999, 999);
	nut_plant_with_mouse.SetAnimation(240, false);
	nut_plant_with_mouse.ToggleAnimation();
}

void CGameStateRun::load_nut_gray_card() {
	nut_gray_card.LoadBitmapByString({ "Plants_vs_Zombies_Image/card/nut_card/nut_card_gray.bmp" }, RGB(0, 0, 0));
	nut_gray_card.SetTopLeft(460, 0);
}

void CGameStateRun::load_nut_card() {
	nut_card.LoadBitmapByString({ "Plants_vs_Zombies_Image/card/nut_card/nut_card.bmp" }, RGB(0, 0, 0));
	nut_card.SetTopLeft(460, 0);
}

void CGameStateRun::load_zombie_win_picture() {
	zombie_win_picture.LoadBitmapByString({ "Plants_vs_Zombies_Image/end/ZombiesWon.bmp" }, RGB(255, 255, 255));
	zombie_win_picture.SetTopLeft(350, 100);
}


void CGameStateRun::place_seat(int targetx, int targety,int item){
	
	//int seat_x[9];
	int map_topleftX = 200;
	int map_topleftY =  90;

	const int xSize = 82;
	const int ySize = 96;
	for (int y = 0; y < 5; y++){
		for (int x = 0; x < 9; x++){
			if (targetx >= map_topleftX +x*xSize && targetx < map_topleftX+(x+1)*(xSize) && targety > map_topleftY + y * ySize && targety < map_topleftY + (y + 1) * ySize  && seat[x][y] != 2){
				seat[x][y] = 1;
			}
		}
	}
	
	for (int y = 0; y < 5; y++){
		for (int x = 0; x < 9; x++){
			if (seat[x][y] == 1 ) {
				if (item == (int)plant::SUN_FLOWER) {
					sunflower[sunflower_index].SetTopLeft(207+xSize*x, 100+ySize*y);
					money -= 50;
				}
				else if (item == (int)plant::BEAN_PLANT) {
					bean_plant[bean_plant_index].SetTopLeft(207 + xSize * x, 100 + ySize * y);
					money -= 100;
					bean_plant_index += 1;
				}
				else if (item == (int)plant::NUT_PLANT) {
					nut[nut_plant_index].SetTopLeft(207 + xSize * x, 100 + ySize * y);
					money -= 75;
					nut[nut_plant_index].coordinate_x = x;
					nut[nut_plant_index].coordinate_y = y;
					nut_plant_index += 1;
				}
				place_flag = 0;
				seat[x][y] = 2;
				sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
			}
		}
	}
}

void  CGameStateRun::clear_seat(int coordinate_x, int coordinate_y) {
	seat[coordinate_x][coordinate_y] = 0;
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


	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 155, std::to_string(call_time));

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 200, std::to_string(nut[0].hp));

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 255, std::to_string(nut[1].hp));

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 320, std::to_string(nut[2].hp));

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 375, std::to_string(nut_plant_index));

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 485, std::to_string(zombie_index));
	
	

	/*
	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 105, std::to_string(bean_plant[0].hp));

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 80, std::to_string(basic_zombie[0].hp));

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 5, std::to_string(sun_cooldown));

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 430, std::to_string(bean_plant[0].GetLeft()));

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 700, 540, std::to_string(bean_plant[0].GetLeft()));

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 540, std::to_string(bean_plant[0].PBgettop()));
	*/
	CDDraw::ReleaseBackCDC();
}