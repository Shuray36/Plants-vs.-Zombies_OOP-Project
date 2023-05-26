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
//#include "map.h"
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

template<class Plant>
vector<Plant> InitPlantVector(int n)
{
	vector<Plant> plantVector;
	for(int i =0;i<n;i++)
	{
		Plant newFlower = Plant();
		plantVector.push_back(newFlower);
	}
	return plantVector;
}


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
	for(auto&car :carList)
	{
		car.Update();
	}
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
		for(auto &b:bean_plant)
		{
			b.cd+=1;
			if (b.cd >= 50) {
				b.pb_flag = 0;
				b.attack();
			}
			for (int j = 0; j < zombie_max; j++) {
				if (b.PBgetleft() <= basic_zombie[j].GetLeft() + 50 && b.PBgetleft() >= basic_zombie[j].GetLeft() + 45 && b.PBgettop() <= basic_zombie[j].GetTop() + 60 && b.PBgettop() >= basic_zombie[j].GetTop() - 0 && basic_zombie[j].die_flag == 0) {
					b.leave();
					b.pb_flag = 1;
					b.cd = 0;
					basic_zombie[j].hp -= 30;
					if (basic_zombie[j].hp <= 0) {
						basic_zombie[j].state = 1;
						basic_zombie[j].die_flag = 1;
					}

					b.reload();
				}
			}
		}
		//fix me 植物應該在殭屍出現才開始射擊 


		//-----------------------

		//殭屍攻擊---------------

		for (int i = 0; i < (zombie_max-1); i++) {
			//bean-------------------------------------
			for(auto &b:bean_plant)
			{
				if (basic_zombie[i].GetLeft() <= b.GetLeft() + 30 && basic_zombie[i].GetLeft() >= b.GetLeft() + 20 && basic_zombie[i].GetTop() <= b.GetTop() + 0 && basic_zombie[i].GetTop() >= b.GetTop() -60 && basic_zombie[i].die_flag == 0)
				{
					basic_zombie[i].state = 4;
					basic_zombie[i].cd += 1;
					if (basic_zombie[i].cd >= 100 && b.hp > 0) {
						basic_zombie[i].cd = 0;
						b.hp -= 30;
					}
					if (b.hp <= 0) {
						for (int k = 0; k < (zombie_max - 1); k++) {
							if (basic_zombie[k].state == 4) {
								basic_zombie[k].cd = 0;
								basic_zombie[k].state = 0;
								basic_zombie[k].speed = -1;
							}
						}
					}
					clear_seat((int)b.GetCoordinateX(),(int) b.GetCoordinateY());
				}
			}
			//太陽花-------------------------------------
			for (auto &s : sunflower) {
				if (basic_zombie[i].GetLeft() <= s.GetLeft() + 30 && basic_zombie[i].GetLeft() >= s.GetLeft() + 20 && basic_zombie[i].GetTop() <= s.GetTop() + 0 && basic_zombie[i].GetTop() >= s.GetTop() - 60 && basic_zombie[i].die_flag == 0) {
					basic_zombie[i].state = 4;
					basic_zombie[i].cd += 1;
					if (basic_zombie[i].cd >= 100 && s.hp > 0) {
						basic_zombie[i].cd = 0;
						s.hp -= 30;
					}
					if (s.hp <= 0) {
						for (int k = 0; k < (zombie_max - 1); k++) {
							if (basic_zombie[k].state == 4) {
								basic_zombie[k].cd = 0;
								basic_zombie[k].state = 0;
								basic_zombie[k].speed = -1;
							}
						}
						clear_seat((int)s.GetCoordinateX(), (int)s.GetCoordinateY());
					}
				}
				//--------------------------------------------
			}
			//nut-------------------------------------
			for (auto &n : nut) {
				if (basic_zombie[i].GetLeft() <= n.GetLeft() + 30 && basic_zombie[i].GetLeft() >= n.GetLeft() + 20 && basic_zombie[i].GetTop() <= n.GetTop() + 0 && basic_zombie[i].GetTop() >= n.GetTop() - 60 && basic_zombie[i].die_flag == 0) {
					basic_zombie[i].state = 4;
					basic_zombie[i].cd += 1;
					if (basic_zombie[i].cd >= 100 && n.hp > 0) {
						basic_zombie[i].cd = 0;
						n.hp -= 30;
					}
					if (n.hp <= 0) {
						for (int k = 0; k < (zombie_max - 1); k++) {
							if (basic_zombie[k].state == 4) {
								basic_zombie[k].cd = 0;
								basic_zombie[k].state = 0;
								basic_zombie[k].speed = -1;
							}
						}
						clear_seat((int)n.GetCoordinateX(), (int)n.GetCoordinateY());
					}
				}
				//--------------------------------------------
			}
			// fix me 不知道為什麼任何植物放在倒數兩排上 殭屍吃植物的時候會變得非常奇怪 並且植物不會扣血
		}

		//-----------------------
		sun.SetTopLeft(sun.GetLeft() + 0, sun.GetTop() + 2);

		//todo car :zombie list done can kill zombie
		// for(auto &car : carList)
		// {
		// 	for(auto &zombie:zombieList)
		// 	{
		// 		if(CMovingBitmap::IsOverlap((CMovingBitmap)car,zombie))	;
		// 	}
		// }
		
		//太陽花技能----------------------
		for(auto&s :sunflower)
		{
			s.cd += 1;
			if (s.cd >= 245) {
				s.cd_keep += 1;
				s.state = 1;
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
		for (auto &car : carList) {
			for (int i = 0; i < 9; i++) {
				if (car.GetLeft() >= basic_zombie[i].GetLeft() + 0 && car.GetLeft() <= basic_zombie[i].GetLeft() + 100 && car.GetTop() >= basic_zombie[i].GetTop() + 0 && car.GetTop() <= basic_zombie[i].GetTop() + 100) {
					car.Trigger();
					basic_zombie[i].state = 3;
				}
			}
		}

		if (basic_zombie[8].die_flag == 1) {
			overflag = 1;
		}
		
	}
	

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	int roadNum = 5;
	for(int i = 0 ;i< roadNum;i++)
	{
		Car newcar=Car();
		newcar.Init(i);
		carList.push_back(newcar);
	}
	fight_background.LoadBitmapByString({ "Plants_vs_Zombies_Image/Scenes/BG1.bmp" });
	fight_background.SetTopLeft(0, 0);
	for (int i = 0; i < 10; i++)basic_zombie[i].init();
	for (int i = 0; i < 10; i++) basic_zombie[i].speed = 0;

	for(auto& n:nut)
	{
		n.init();
	}
	for(auto& b:bean_plant)
	{
		b.init();
	}
	
	load_sunback();
	sun.LoadSun();
	load_sunflower_card();
	load_sunflower_gray_card();
	load_peashooter_gray_card();
	load_peashooter_card();
	load_nut_card();
	load_nut_gray_card();
	load_zombie_win_picture();
	load_plant_win_picture();
	
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DOWN) {
		for (auto & car : carList)
		{
			car.Trigger();
		}
	}
	if (nChar == VK_UP) {
		GotoGameState(GAME_STATE_INIT);
	}
	if (nChar == 0x52) {
		reset();
	}
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
	if (CMovingBitmap::IsCardClick(pointx, pointy, peashooter_card)&&money>=100) { //245 15  330 50
		item = 1;
		place_flag = 1;
		Bean newflower = Bean();
		newflower.init();
		bean_plant.push_back(newflower);
	}
	if (CMovingBitmap::IsCardClick(pointx, pointy, sunflower_card)&&money>=50){
		item = 0;
		place_flag = 1;
		Sunflower newflower = Sunflower();
		newflower.init();
		sunflower.push_back(newflower);
	}
	if (CMovingBitmap::IsCardClick(pointx, pointy, nut_card) && money >= 75) {
		item = 2;
		place_flag = 1;
		Nut n = Nut();
		n.init();
		nut.push_back(n);
	}

	for(auto &s :sunflower)
	{
		if (pointx >= s.sunGetLeft() - 50 && pointx <= s.sunGetLeft() + 50 && pointy >= s.sunGetTop() - 50 && pointy <= s.sunGetTop() + 50) {
			s.getsun_flag = 0;
			money += 50;
		}
	}

	if (pointx >= plant_win_picture.GetLeft() + 0 && pointx <= plant_win_picture.GetLeft() + 50 && pointy >= plant_win_picture.GetTop() + 0 && pointy <= plant_win_picture.GetTop() + 75) {
		if (overflag == 1) {
			GotoGameState(GAME_STATE_INIT);
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
	if (!sunflower.empty()&&!sunflower.back().GetIsPlace()) {
		sunflower.back().SetTopLeft(pointx - 32, pointy - 25);
	}
	if (!bean_plant.empty()&&!bean_plant.back().GetIsPlace()) {
		bean_plant.back().SetTopLeft(pointx - 32, pointy - 25);
	}
	if (!nut.empty()&&!nut.back().GetIsPlace()) {
		nut.back().SetTopLeft(pointx - 32, pointy - 25);
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
	for(auto &s : sunflower)
	{
		s.show();
	}
	for(auto &n : nut)
	{
		n.show();
	}
	for(auto &b : bean_plant)
	{
		b.show();
	}


	if (BG1_flag1 == 2) {
		
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



		if(sun_flag==0) sun.ShowBitmap();

		for(auto&car:carList){
			car.ShowBitmap();
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

	if (overflag == 1) {
		plant_win_picture.SetTopLeft(733, 313);
		plant_win_picture.ShowBitmap();
	}

	draw_text();
	
}
//-------------------------------------------------------------------------------------------



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

void CGameStateRun::load_peashooter_gray_card() {
	peashooter_gray_card.LoadBitmapByString({ "Plants_vs_Zombies_Image/card/peashooter_card/peashooter_gray.bmp" }, RGB(255, 255, 255));
	peashooter_gray_card.SetTopLeft(350, 0);
}
void CGameStateRun::load_peashooter_card() {
	peashooter_card.LoadBitmapByString({ "Plants_vs_Zombies_Image/card/peashooter_card/peashooter.bmp" }, RGB(255, 255, 255));
	peashooter_card.SetTopLeft(350, 0);
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

void CGameStateRun::load_plant_win_picture() {
	plant_win_picture.LoadBitmapByString({ "Plants_vs_Zombies_Image/end/plantWon.bmp" }, RGB(255, 255, 255));
	plant_win_picture.SetTopLeft(0, 0);
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
					auto &newflower = sunflower.back();
					newflower.SetTopLeft(207+xSize*x, 100+ySize*y);
					newflower.SetCoordinate(x,y);
					newflower.SetIsPlace(true);
					money -= 50;
				}
				else if (item == (int)plant::BEAN_PLANT) {
					money -= 100;
					auto &newflower = bean_plant.back();
					newflower.SetTopLeft(207+xSize*x, 100+ySize*y);
					newflower.SetCoordinate(x,y);
					newflower.SetIsPlace(true);
				}
				else if (item == (int)plant::NUT_PLANT) {
					auto &newnut = nut.back();
					newnut.SetTopLeft(207+xSize*x, 100+ySize*y);
					newnut.SetCoordinate(x,y);
					newnut.SetIsPlace(true);
					money -= 75;
				}
				place_flag = 0;
				seat[x][y] = 2;
			}
		}
	}
}

void  CGameStateRun::clear_seat(int coordinate_x, int coordinate_y) {
	seat[coordinate_x][coordinate_y] = 0;
}

void CGameStateRun::reset() {
	money = 0;
	BG1_flag1 = 0;
	time = 0;
	overflag = 0;
	overtime = 0;
	//---------------
	//map-------------
	place_flag = 0;
	for (unsigned int i = 0; i < nut.size(); i++) {
		//nut.erase(i);
	}
	/*
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 5; y++) {
			seat[x][y] = 0;
		}
	}
	//這行加入後太陽花的放置會變得很奇怪
	*/
	//---------------
	//殭屍-----------
	zombie_index = -1;
	call_time = 0;
	//---------------

	//小太陽-----------
	sun_cooldown = 0;
	//-----------------
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
	CTextDraw::Print(pDC, 900, 485, std::to_string(zombie_index));
	
	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 50, 50, std::to_string(Map::level));
	

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