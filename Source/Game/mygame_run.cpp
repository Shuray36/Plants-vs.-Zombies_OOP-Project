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
		//測試物件移動查看位置
		if (move_right == 1) test.SetTopLeft(test.GetLeft() + 1, test.GetTop());
		if (move_left == 1) test.SetTopLeft(test.GetLeft() - 1, test.GetTop());
		if (move_up == 1) test.SetTopLeft(test.GetLeft(), test.GetTop() - 1);
		if (move_down == 1) test.SetTopLeft(test.GetLeft(), test.GetTop() + 1);
		test_x = test.GetLeft();
		test_y = test.GetTop();
		basic_zombie.SetTopLeft(basic_zombie.GetLeft() + basic_zombie.speed, 240);
		//花開始落下--------------------------------------------
		sun_cooldown += 1;
		if (sun_cooldown >= 300) {
			int r = (rand() % 900 + 100);
			sun.SetTopLeft(r, 0);
			sun_flag = 0;
			sun_cooldown = 0;
		}
		sun.SetTopLeft(sun.GetLeft() + 0, sun.GetTop() + 2);
		if (car[2].GetLeft() >= basic_zombie.GetLeft() -150 && car[2].GetLeft() <= basic_zombie.GetLeft() + 150 && car[2].GetTop() >= basic_zombie.GetTop()-150 && car[2].GetTop() <= basic_zombie.GetTop()+150){
			car_run = 1;
			basic_zombie.state = 3;
		}
		//------------------------------------------------------
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
	basic_zombie.init();
	bean_plant.init();
	load_zombie_eat();
	sunflower.init();
	load_sunflower();
	load_sunback();
	load_sun();
	load_car();
	load_sunflower_card();
	load_sunflower_gray_card();
	load_peashooter_gray_card();
	load_peashooter_card();
	load_test();//查看物件位置 可移動的
	for (int i = 0; i < 9; i++) {
		testflower[i].init();
	}
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RIGHT) move_right = 1;
	if (nChar == VK_LEFT) move_left = 1;
	if (nChar == VK_UP) move_up = 1;
	if (nChar == VK_DOWN) {
		move_down = 1;
		car_run = 1;
	} 

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RIGHT) move_right = 0;
	if (nChar == VK_LEFT) move_left = 0;
	if (nChar == VK_UP) move_up = 0;
	if (nChar == VK_DOWN) move_down = 0;
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	
	if(CMovingBitmap::IsMouseClick(pointx,pointy,sun)){
		money += 300;
		sun_flag = 1;
	}
	if (CMovingBitmap::IsMouseClick(pointx, pointy, peashooter_card)&&money>=100) {
		money -= 100;
		pershooter_show_flag = 1;
	}
	if (CMovingBitmap::IsMouseClick(pointx, pointy, sunflower_card)&&money>=50){
		//money -= 50;
		sunflower_show_flag = 1;
		sunflower_index += 1;
		place_flag = 1;
		sunflower_with_mouse_show = 1;
	}
	if (place_flag == 1) {
		place_seat(pointx, pointy);
	}

}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	pointx = point.x;
	pointy = point.y;
	//if(sunflower_click_show) sunflower[1].SetTopLeft(pointx - 32, pointy - 25);
	if (sunflower_with_mouse_show == 1) {
		sunflower_with_mouse.SetTopLeft(pointx - 32, pointy - 25);
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
	for (int i = 0; i < 9; i++) {
		testflower[i].show();
	}
	if (BG1_flag1 == 2) {



		if (sunflower_with_mouse_show == 1) {
			sunflower_with_mouse.ShowBitmap();
		}
		
		basic_zombie.show();
		if (sunflower_show_flag == 0) {
			sunflower.SetTopLeft(999, 999);
			sunflower.show();
		}
		else if (sunflower_show_flag == 1) {
			testflower[sunflower_index].SetTopLeft((sunflower_index + 50)*sunflower_index, (sunflower_index + 50)*sunflower_index);
			//testflower[sunflower_index].show();
			sunflower.show();
		}
		if(sun_flag==0) sun.ShowBitmap();
		for (int i = 0; i < 5; i++) car[i].ShowBitmap();
		if (pershooter_show_flag == 0) {
			bean_plant.SetTopLeft(999, 999);
			bean_plant.show();
		}
		else if (pershooter_show_flag == 1) {
			bean_plant.SetTopLeft(375, 285);
			bean_plant.show();
		}
		bean_plant.atk_speed += 1;
		if (bean_plant.atk_speed >= 100) {
			
			bean_plant.pb_flag = 0;
			bean_plant.attack();
		}
		if (bean_plant.PBgetleft() <= basic_zombie.GetLeft()+50 && bean_plant.PBgetleft() >= basic_zombie.GetLeft()+45 && bean_plant.PBgettop() <= basic_zombie.GetTop() + 50 && bean_plant.PBgettop() >= basic_zombie.GetTop() - 50) {
			bean_plant.leave();
			bean_plant.pb_flag = 1;
			bean_plant.atk_speed = 0;
			basic_zombie.hp -= 500;
			if (basic_zombie.hp <= 0) basic_zombie.state = 1;
			bean_plant.reload();
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
	test.ShowBitmap();
	test2.SetTopLeft(test.GetLeft() + 50, test.GetTop() + 10);
	//test2.ShowBitmap();
	draw_text();
	
}
//-------------------------------------------------------------------------------------------
void CGameStateRun::load_zombie_move() {
	/*
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
	*/
	
	//test1.init();
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




void CGameStateRun::load_test() {
	
	/*
	"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_0.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_1.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_2.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_3.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_4.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_5.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_6.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_7.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_8.bmp" ,
		"Plants_vs_Zombies_Image/zombie/basic_zombie_die/falldown_9.bmp" ,
	*/
	test.LoadBitmapByString({ "Plants_vs_Zombies_Image/plants/sunflower_0/sunflower_1.bmp"
		}, RGB(255, 255, 255)); //440 285
	test.SetTopLeft(0, 0);
	test.SetAnimation(140, false);
	test.ToggleAnimation();
	
	test2.LoadBitmapByString({
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_0.bmp",
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_1.bmp",
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_2.bmp",
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_3.bmp",
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_4.bmp",
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_5.bmp",
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_6.bmp",
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_7.bmp",
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_8.bmp",
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_9.bmp",
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_10.bmp",
		"Plants_vs_Zombies_Image/zombie/basic_zombie_headfall/headfall_11.bmp",
		}, RGB(255, 255, 255)); //440 285
	test2.SetTopLeft(test.GetLeft(), test.GetTop());
	test2.SetAnimation(140, false);
	test2.ToggleAnimation();
}


void CGameStateRun::place_seat(int x, int y){
	
	//int seat_x[9];
	int map_length = 200;
	int map_high = 90;
	if (x >= 200 && x < 282 && y > 90 && y < 179 && seat[0][0] !=2) seat[0][0] = 1; //82 96
	else if (x >= 282 && x < 364 && y > 90 && y < 179 && seat[1][0] != 2) seat[1][0] = 1;
	else if (x >= 364 && x < 446 && y > 90 && y < 179 && seat[2][0] != 2) seat[2][0] = 1;
	else if (x >= 446 && x < 528 && y > 90 && y < 179 && seat[3][0] != 2) seat[3][0] = 1;
	else if (x >= 528 && x < 610 && y > 90 && y < 179 && seat[4][0] != 2) seat[4][0] = 1;
	else if (x >= 610 && x < 692 && y > 90 && y < 179 && seat[5][0] != 2) seat[5][0] = 1;
	else if (x >= 692 && x < 774 && y > 90 && y < 179 && seat[6][0] != 2) seat[6][0] = 1;
	else if (x >= 774 && x < 856 && y > 90 && y < 179 && seat[7][0] != 2) seat[7][0] = 1;
	else if (x >= 856 && x < 938 && y > 90 && y < 179 && seat[8][0] != 2) seat[8][0] = 1;
	//------------------------------------------------------------------------------------
	if (x >= 200 && x < 282 && y>180 && y < 276 && seat[0][1] != 2) seat[0][1] = 1; //82 96
	else if (x >= 282 && x < 364 && y > 180 && y < 276 && seat[1][1] != 2) seat[1][1] = 1;
	else if (x >= 364 && x < 446 && y > 180 && y < 276 && seat[2][1] != 2) seat[2][1] = 1;
	else if (x >= 446 && x < 528 && y > 180 && y < 276 && seat[3][1] != 2) seat[3][1] = 1;
	else if (x >= 528 && x < 610 && y > 180 && y < 276 && seat[4][1] != 2) seat[4][1] = 1;
	else if (x >= 610 && x < 692 && y > 180 && y < 276 && seat[5][1] != 2) seat[5][1] = 1;
	else if (x >= 692 && x < 774 && y > 180 && y < 276 && seat[6][1] != 2) seat[6][1] = 1;
	else if (x >= 774 && x < 856 && y > 180 && y < 276 && seat[7][1] != 2) seat[7][1] = 1;
	else if (x >= 856 && x < 938 && y > 180 && y < 276 && seat[8][1] != 2) seat[8][1] = 1;
	//------------------------------------------------------------------------------------
	if (x >= 200 && x < 282 && y > 276 && y < 372 && seat[0][1] != 2) seat[0][2] = 1; //82 96
	else if (x >= 282 && x < 364 && y > 276 && y < 372 && seat[1][2] != 2) seat[1][2] = 1;
	else if (x >= 364 && x < 446 && y > 276 && y < 372 && seat[2][2] != 2) seat[2][2] = 1;
	else if (x >= 446 && x < 528 && y > 276 && y < 372 && seat[3][2] != 2) seat[3][2] = 1;
	else if (x >= 528 && x < 610 && y > 276 && y < 372 && seat[4][2] != 2) seat[4][2] = 1;
	else if (x >= 610 && x < 692 && y > 276 && y < 372 && seat[5][2] != 2) seat[5][2] = 1;
	else if (x >= 692 && x < 774 && y > 276 && y < 372 && seat[6][2] != 2) seat[6][2] = 1;
	else if (x >= 774 && x < 856 && y > 276 && y < 372 && seat[7][2] != 2) seat[7][2] = 1;
	else if (x >= 856 && x < 938 && y > 276 && y < 372 && seat[8][2] != 2) seat[8][2] = 1;
	//------------------------------------------------------------------------------------
	if (x >= 200 && x < 282 && y > 372 && y < 468 && seat[0][3] != 2) seat[0][3] = 1; //82 96
	else if (x >= 282 && x < 364 && y > 372 && y < 468 && seat[1][3] != 2) seat[1][3] = 1;
	else if (x >= 364 && x < 446 && y > 372 && y < 468 && seat[2][3] != 2) seat[2][3] = 1;
	else if (x >= 446 && x < 528 && y > 372 && y < 468 && seat[3][3] != 2) seat[3][3] = 1;
	else if (x >= 528 && x < 610 && y > 372 && y < 468 && seat[4][3] != 2) seat[4][3] = 1;
	else if (x >= 610 && x < 692 && y > 372 && y < 468 && seat[5][3] != 2) seat[5][3] = 1;
	else if (x >= 692 && x < 774 && y > 372 && y < 468 && seat[6][3] != 2) seat[6][3] = 1;
	else if (x >= 774 && x < 856 && y > 372 && y < 468 && seat[7][3] != 2) seat[7][3] = 1;
	else if (x >= 856 && x < 938 && y > 372 && y < 468 && seat[8][3] != 2) seat[8][3] = 1;
	//------------------------------------------------------------------------------------
	if (x >= 200 && x < 282 && y > 468 && y < 564 && seat[0][4] != 2) seat[0][4] = 1; //82 96
	else if (x >= 282 && x < 364 && y > 468 && y < 564 && seat[1][4] != 2) seat[1][4] = 1;
	else if (x >= 364 && x < 446 && y > 468 && y < 564 && seat[2][4] != 2) seat[2][4] = 1;
	else if (x >= 446 && x < 528 && y > 468 && y < 564 && seat[3][4] != 2) seat[3][4] = 1;
	else if (x >= 528 && x < 610 && y > 468 && y < 564 && seat[4][4] != 2) seat[4][4] = 1;
	else if (x >= 610 && x < 692 && y > 468 && y < 564 && seat[5][4] != 2) seat[5][4] = 1;
	else if (x >= 692 && x < 774 && y > 468 && y < 564 && seat[6][4] != 2) seat[6][4] = 1;
	else if (x >= 774 && x < 856 && y > 468 && y < 564 && seat[7][4] != 2) seat[7][4] = 1;
	else if (x >= 856 && x < 938 && y > 468 && y < 564 && seat[8][4] != 2) seat[8][4] = 1;
	//------------------------------------------------------------------------------------
	if (seat[0][0] == 1 ) {
		//207 100
		//第一格跟第二格差85
		sunflower.SetTopLeft(207, 100);
		money -= 50;
		place_flag = 0;
		seat[0][0] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[1][0] == 1) {
		sunflower.SetTopLeft(292, 100);
		money -= 50;
		place_flag = 0;
		seat[1][0] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[2][0] == 1) {
		sunflower.SetTopLeft(366, 100);
		money -= 50;
		place_flag = 0;
		seat[2][0] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[3][0] == 1) {
		sunflower.SetTopLeft(449, 100);
		money -= 50;
		place_flag = 0;
		seat[3][0] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[4][0] == 1) {
		sunflower.SetTopLeft(532, 100);
		money -= 50;
		place_flag = 0;
		seat[4][0] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[5][0] == 1) {
		sunflower.SetTopLeft(614, 100);
		money -= 50;
		place_flag = 0;
		seat[5][0] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[6][0] == 1) {
		sunflower.SetTopLeft(696, 100);
		money -= 50;
		place_flag = 0;
		seat[6][0] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[7][0] == 1) {
		sunflower.SetTopLeft(778, 100);
		money -= 50;
		place_flag = 0;
		seat[7][0] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[8][0] == 1) {
		sunflower.SetTopLeft(860, 100);
		money -= 50;
		place_flag = 0;
		seat[8][0] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	//第一排-----------------------------------------------
	if (seat[0][1] == 1) {
		//207 100
		//第一格跟第二格差85
		sunflower.SetTopLeft(207, 189);
		money -= 50;
		place_flag = 0;
		seat[0][1] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[1][1] == 1) {
		sunflower.SetTopLeft(292, 189);
		money -= 50;
		place_flag = 0;
		seat[1][1] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[2][1] == 1) {
		sunflower.SetTopLeft(366, 189);
		money -= 50;
		place_flag = 0;
		seat[2][1] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[3][1] == 1) {
		sunflower.SetTopLeft(449, 189);
		money -= 50;
		place_flag = 0;
		seat[3][1] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[4][1] == 1) {
		sunflower.SetTopLeft(532, 189);
		money -= 50;
		place_flag = 0;
		seat[4][1] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[5][1] == 1) {
		sunflower.SetTopLeft(614, 189);
		money -= 50;
		place_flag = 0;
		seat[5][1] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[6][1] == 1) {
		sunflower.SetTopLeft(696, 189);
		money -= 50;
		place_flag = 0;
		seat[6][1] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[7][1] == 1) {
		sunflower.SetTopLeft(778, 189);
		money -= 50;
		place_flag = 0;
		seat[7][1] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[8][1] == 1) {
		sunflower.SetTopLeft(860, 189);
		money -= 50;
		place_flag = 0;
		seat[8][1] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	//第二排----------------------------------------------
	if (seat[0][2] == 1) {
		//207 100
		//第一格跟第二格差85
		sunflower.SetTopLeft(207, 290);
		money -= 50;
		place_flag = 0;
		seat[0][2] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[1][2] == 1) {
		sunflower.SetTopLeft(292, 290);
		money -= 50;
		place_flag = 0;
		seat[1][2] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[2][2] == 1) {
		sunflower.SetTopLeft(366, 290);
		money -= 50;
		place_flag = 0;
		seat[2][2] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}

	else if (seat[3][2] == 1) {
		sunflower.SetTopLeft(449, 290);
		money -= 50;
		place_flag = 0;
		seat[3][2] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[4][2] == 1) {
		sunflower.SetTopLeft(532, 290);
		money -= 50;
		place_flag = 0;
		seat[4][2] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[5][2] == 1) {
		sunflower.SetTopLeft(614, 290);
		money -= 50;
		place_flag = 0;
		seat[5][2] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[6][2] == 1) {
		sunflower.SetTopLeft(696, 290);
		money -= 50;
		place_flag = 0;
		seat[6][2] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動

	}
	else if (seat[7][2] == 1) {
		sunflower.SetTopLeft(778, 290);
		money -= 50;
		place_flag = 0;
		seat[7][2] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動

	}
	else if (seat[8][2] == 1) {
		sunflower.SetTopLeft(860, 290);
		money -= 50;
		place_flag = 0;
		seat[8][2] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動

	}
	//第三排--------------------------------
	if (seat[0][3] == 1) {
		//207 100
		//第一格跟第二格差85
		sunflower.SetTopLeft(207, 390);
		money -= 50;
		place_flag = 0;
		seat[0][3] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動


	}
	else if (seat[1][3] == 1) {
		sunflower.SetTopLeft(292, 390);
		money -= 50;
		place_flag = 0;
		seat[1][3] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[2][3] == 1) {
		sunflower.SetTopLeft(366, 390);
		money -= 50;
		place_flag = 0;
		seat[2][3] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[3][3] == 1) {
		sunflower.SetTopLeft(449, 390);
		money -= 50;
		place_flag = 0;
		seat[3][3] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[4][3] == 1) {
		sunflower.SetTopLeft(532, 390);
		money -= 50;
		place_flag = 0;
		seat[4][3] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[5][3] == 1) {
		sunflower.SetTopLeft(614, 390);
		money -= 50;
		place_flag = 0;
		seat[5][3] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[6][3] == 1) {
		sunflower.SetTopLeft(696, 390);
		money -= 50;
		place_flag = 0;
		seat[6][3] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[7][3] == 1) {
		sunflower.SetTopLeft(778, 390);
		money -= 50;
		place_flag = 0;
		seat[7][3] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[8][3] == 1) {
		sunflower.SetTopLeft(860, 390);
		money -= 50;
		place_flag = 0;
		seat[8][3] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	//第四排--------------------------------
	if (seat[0][4] == 1) {
		//207 100
		//第一格跟第二格差85
		sunflower.SetTopLeft(207, 490);
		money -= 50;
		place_flag = 0;
		seat[0][4] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[1][4] == 1) {
		sunflower.SetTopLeft(292, 490);
		money -= 50;
		place_flag = 0;
		seat[1][4] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[2][4] == 1) {
		sunflower.SetTopLeft(366, 490);
		money -= 50;
		place_flag = 0;
		seat[2][4] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[3][4] == 1) {
		sunflower.SetTopLeft(449, 490);
		money -= 50;
		place_flag = 0;
		seat[3][4] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[4][4] == 1) {
		sunflower.SetTopLeft(532, 490);
		money -= 50;
		place_flag = 0;
		seat[4][4] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[5][4] == 1) {
		sunflower.SetTopLeft(614, 490);
		money -= 50;
		place_flag = 0;
		seat[5][4] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[6][4] == 1) {
		sunflower.SetTopLeft(696, 490);
		money -= 50;
		place_flag = 0;
		seat[6][4] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[7][4] == 1) {
		sunflower.SetTopLeft(778, 490);
		money -= 50;
		place_flag = 0;
		seat[7][4] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	else if (seat[8][4] == 1) {
		sunflower.SetTopLeft(860, 490);
		money -= 50;
		place_flag = 0;
		seat[8][4] = 2;
		sunflower_with_mouse_show = 0; //CMovie的太陽花圖示會跟著滑鼠移動
	}
	//第五排--------------------------------
}

void CGameStateRun::draw_text() {
	CDC *pDC = CDDraw::GetBackCDC();
	//CDC *number = CDDraw::GetBackCDC();
	/* Print title */
	std::string str_x;
	str_x = "test_x:"+std::to_string(test_x);
	std::string str_y;
	str_y = "test_y:" + std::to_string(test_y);

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 0, 0, std::to_string(pointx));
	CTextDraw::Print(pDC, 50, 0, std::to_string(pointy));

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 157, 5, std::to_string(money));

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 5, std::to_string(sun_cooldown));

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 30, str_x);

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 55, str_y);

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 80, std::to_string(basic_zombie.hp));

	CDDraw::ReleaseBackCDC();
}