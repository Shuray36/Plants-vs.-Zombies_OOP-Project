#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>
#include <random>

#define ZOMBIE_END 6



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
	reset();
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	plantManager.Update();
	plantManager.SetZombies(zombies);
	sun_manager->Update();
	pb_manager->Update();
	pb_manager->SetZombies(zombies);
	

	if(Map::level == 1)
	{
		
			if (basic_counter < ZOMBIE_END) call_time += 1;
			if (call_time == 200) {
				auto z = make_shared<Basic_zombie>();
				z->init();
				z->SetTopLeft(950, zb_y_random());
				zombies.push_back(z);
				basic_counter += 1;
				call_time = 0;
			}
			//召喚殭屍----------------------------------
	}
	if (Map::level == 2)
	{
		if (basic_counter < 3) call_time += 1;
		if (call_time == 200) {
			auto z = make_shared<Basic_zombie>();
			z->init();
			z->SetTopLeft(950, zb_y_random());
			zombies.push_back(z);
			basic_counter += 1;
			call_time = 0;
		}
		if (tri_counter < 3) tri_call_time += 1;
		call_tir_zombie(); //召喚三角殭屍
		//召喚殭屍------------------------------------
	}
	if (Map::level == 3)
	{
		
			if (basic_counter < 3) call_time += 1;
			if (call_time == 200) {
				auto z = make_shared<Basic_zombie>();
				z->init();
				z->SetTopLeft(950, zb_y_random());
				zombies.push_back(z);
				basic_counter += 1;
				call_time = 0;
			}
			if (tri_counter < 3) tri_call_time += 1;
			call_tir_zombie(); //召喚三角殭屍
			if (bucket_counter < 3) bucketcall_time += 1;
			call_bucket_zombie();
			//召喚殭屍------------------------------------
	}
	for(auto&car :carList)
	{
		car.Update();
	}
	//遊戲剛開始的移動 往右到一定程度後 往回到原本樣式
	if (Map::level == 1) {
		if (L1_map.GetLeft() >= (-350) && BG1_flag1 == 0) {
			L1_map.SetTopLeft(L1_map.GetLeft() - 10, 0);
			if (L1_map.GetLeft() <= (-350)) {
				BG1_flag1 = 1;
			}
		}
		else if (L1_map.GetLeft() <= (350) && BG1_flag1 == 1) {
			time += 1;
			if (time >= 20) {
				L1_map.SetTopLeft(L1_map.GetLeft() + 10, 0);
				if (L1_map.GetLeft() >= (-50)) BG1_flag1 = 2;
			}
		}
	}
	else if (Map::level == 2) {
		if (L2_map.GetLeft() >= (-350) && BG1_flag1 == 0) {
			L2_map.SetTopLeft(L2_map.GetLeft() - 10, 0);
			if (L2_map.GetLeft() <= (-350)) {
				BG1_flag1 = 1;
			}
		}
		else if (L2_map.GetLeft() <= (350) && BG1_flag1 == 1) {
			time += 1;
			if (time >= 20) {
				L2_map.SetTopLeft(L2_map.GetLeft() + 10, 0);
				if (L2_map.GetLeft() >= (-50)) BG1_flag1 = 2;
			}
		}
	}
	else if (Map::level == 3) {
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
	}
	

	if (BG1_flag1 == 2) {        //遊戲跑換地圖後正式開始 
		for (auto&zom : zombies)zom->SetTopLeft(zom->GetLeft() + zom->speed, zom->GetTop());
		//------------------------------------------------------
		//花開始落下--------------------------------------------z
		sun_cooldown += 1;
		if (sun_cooldown >= 200) {
			int r = (rand() % 900 + 100);
			int y = (rand() % 700 + 100);
			sun_manager->makeSun({(float)r,0},{(float)r,(float)y});
			sun_flag = 0;
			sun_cooldown = 0;
		}
		//植物攻擊-----------
		//bean射擊
		//double_bean 射擊
		//fix me 植物應該在殭屍出現才開始射擊 
		//-----------------------
		//殭屍攻擊---------------

			//double_bean-------------------------------------

		for (auto&zom : zombies) {
			for (auto &s : plantManager.GetPlants()) {
				if (s->GetIsPlace()&&(zom->GetLeft() <= s->GetLeft() + 30 && zom->GetLeft() >= s->GetLeft() + 20 && zom->GetTop() <= s->GetTop() + 0 && zom->GetTop() >= s->GetTop() - 60 && zom->die_flag == 0) ){
					zom->state = 4;
					zom->cd += 1;
					if (zom->cd >= 100 && s->hp > 0) {
						zom->cd = 0;
						s->hp -= zom->attack;
					}
					if (s->hp <= 0) {
						for (auto& z : zombies) {
							if (z->state == 4) {
   								z->cd = 0;
								z->state = 0;
								z->speed = -1;
							}
						}
						clear_seat((int)s->GetCoordinateX(), (int)s->GetCoordinateY());
					}
				}
			}
		}

		//太陽花技能----------------------
		//--------------------------------
		
		for (auto &car : carList) {
			for (auto&zom : zombies) {
				if (car.GetLeft() >= zom->GetLeft() + 0 && car.GetLeft() <= zom->GetLeft() + 100 && car.GetTop() >= zom->GetTop() + 0 && car.GetTop() <= zom->GetTop() + 100)
				{
					car.Trigger();
					zom->state = 3;
				}
			}
		}		
	}

	judge_plant_victory();
	judge_zombie_victory();
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

	L1_map.LoadBitmapByString({ "Plants_vs_Zombies_Image/Scenes/level1_map.bmp" });
	L1_map.SetTopLeft(0, 0);
	L2_map.LoadBitmapByString({ "Plants_vs_Zombies_Image/Scenes/level2_map.bmp" });
	L2_map.SetTopLeft(0, 0);
	fight_background.LoadBitmapByString({ "Plants_vs_Zombies_Image/Scenes/BG1.bmp" });
	fight_background.SetTopLeft(0, 0);

	shovel_box.LoadBitmapByString({"Plants_vs_Zombies_Image/shovel_box.bmp"}, RGB(255, 255, 255));
	shovel_box.SetTopLeft(870, 0);

	shovel.LoadBitmapByString({ "Plants_vs_Zombies_Image/Shovel1.bmp" }, RGB(255, 255, 255));
	load_sunback();

	load_sunflower_card();
	load_sunflower_gray_card();
	load_peashooter_gray_card();
	load_peashooter_card();
	load_nut_card();
	load_nut_gray_card();
	load_db_card();
	load_db_gray_card();
	load_chili_card();

	load_zombie_win_picture();
	load_plant_win_picture();

	plantManager.setSunmanager(sun_manager);
	plantManager.setPbmanager(pb_manager);
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
	if (nChar == VK_RIGHT) {
	}
	if (nChar == 0x52) {//r
		reset();
	}
	if (nChar == 0x4D) {//m
		money += 1000;
	}
	if (nChar == 0x31) {//1
		auto z = make_shared<Basic_zombie>();
		z->init();
		z->SetTopLeft(950, 40);
		zombies.push_back(z);
	}
	if (nChar == 0x32) {//2
		auto z = make_shared<Basic_zombie>();
		z->init();
		z->SetTopLeft(950, 140);
		zombies.push_back(z);
	}
	if (nChar == 0x33) {//3
		auto z = make_shared<Basic_zombie>();
		z->init();
		z->SetTopLeft(950, 240);
		zombies.push_back(z);
	}
	if (nChar == 0x34) {//4
		auto z = make_shared<Basic_zombie>();
		z->init();
		z->SetTopLeft(950, 340);
		zombies.push_back(z);
	}
	if (nChar == 0x35) {//5
		auto z = make_shared<Basic_zombie>();
		z->init();
		z->SetTopLeft(950, 440);
		zombies.push_back(z);
	}
	if (nChar == 0x4A) {//j

		auto z = make_shared<Basic_zombie>();
		z->init();
		z->SetTopLeft(950, zb_y_random());
		zombies.push_back(z);
		
	}
	if (nChar == 0x4B) {//k
		auto t = make_shared<Triangle_zombie>();
		t->init();
		t->SetTopLeft(950, zb_y_random());
		zombies.push_back(t);

	}
	if (nChar == 0x4C) {//L

		auto bz = make_shared<Bucket_zombie>();
		bz->init();
		bz->SetTopLeft(950, zb_y_random());
		zombies.push_back(bz);

	}
	if (nChar == 0x4F) {//o
		end_flag = 1;
	}
	if (nChar == 0x50) {//p
		overflag = 1;
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	Vector2 mousePosition = {(float)pointx,(float)pointy};
	money+=sun_manager->Lbutton(mousePosition);
	// sun_flag=1;

	if (CMovingBitmap::IsCardClick(pointx, pointy, sunflower_card) && money >= 50) {
		item = 0;
		place_flag = 1;
		plantManager.MakePlant(PlantType::SUN_FLOWER,mousePosition);
	}

	if (CMovingBitmap::IsCardClick(pointx, pointy, peashooter_card)&&money>=100) { //245 15  330 50
		item = 1;
		place_flag = 1;
		plantManager.MakePlant(PlantType::BEAN_PLANT,mousePosition);
	}
	
	if (CMovingBitmap::IsCardClick(pointx, pointy, nut_card) && money >= 75) {
		item = 2;
		place_flag = 1;
		plantManager.MakePlant(PlantType::NUT_PLANT,mousePosition);
	}

	if (CMovingBitmap::IsCardClick(pointx, pointy, db_card) && money >= 100 && Map::level != 1) {
		item = 3;
		place_flag = 1;
		plantManager.MakePlant(PlantType::DOUBLE_BEAN,mousePosition);
	}
	if (CMovingBitmap::IsCardClick(pointx, pointy, chili_card) && money >= 150) {
		item = 4;
		place_flag = 1;
		plantManager.MakePlant(PlantType::CHILI_PLANT, mousePosition);
	}

	if (pointx >= plant_win_picture.GetLeft() + 0 && pointx <= plant_win_picture.GetLeft() + 50 && pointy >= plant_win_picture.GetTop() + 0 && pointy <= plant_win_picture.GetTop() + 75) {
		if (overflag == 1) {
			GotoGameState(GAME_STATE_INIT);
		}
	}
	if (CMovingBitmap::IsCardClick(pointx, pointy, shovel_box) ) {
		shovel_flag = 1;
	}

	if (place_flag == 1) {
		place_seat(pointx, pointy, item);
	}

	if (shovel_flag == 1) {
		uproot(pointx, pointy);
	}

}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	pointx = point.x;
	pointy = point.y;
	plantManager.OnMouseMove({ static_cast<float>(point.x),static_cast<float>(point.y)});
	if (shovel_flag == 1) {
		shovel.SetTopLeft(pointx - shovel.GetWidth() / 2-1, pointy - shovel.GetHeight() / 2-1);
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
	if (Map::level == 1) {
		L1_map.ShowBitmap();
	}
	else if (Map::level == 2) {
		L2_map.ShowBitmap();
	}
	else if (Map::level == 3) {
		fight_background.ShowBitmap();
	}
	if (BG1_flag1 == 2) {
		for (auto &zom : zombies) zom->show();
		pb_manager->Show();
		for (auto&car : carList) {
			car.ShowBitmap();
		}
		plantManager.Show();
		sun_manager->ShowSun();
	}

	sunback.ShowBitmap();


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
	if (money >= 200) db_flag = 1;
	else if (money < 200) db_flag = 0;
	
	if (money >= 150) chili_flag = 1;
	else if (money < 150) chili_flag = 0;


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

	if (db_flag == 0 && Map::level != 1) {
		db_gray_card.ShowBitmap();
	}
	else if (db_flag == 1 && Map::level != 1) {
		db_card.ShowBitmap();
	}
	if (chili_flag == 0) {
		chili_gray_card.ShowBitmap();
	}
	else if (chili_flag == 1) {
		chili_card.ShowBitmap();
	}
	
	shovel_box.ShowBitmap();
	if (shovel_flag == 1) {
		shovel.ShowBitmap();
	}

	if (overflag == 1) {
		call_time = 0;
		tri_call_time = 0;
		bucketcall_time = 0;
		plant_win_picture.SetTopLeft(733, 313);
		plant_win_picture.ShowBitmap();
	}

	if (end_flag == 1) zombie_win_picture.ShowBitmap();
	draw_text();
}
//-------------------------------------------------------------------------------------------
void CGameStateRun::judge_plant_victory() {

	if (Map::level == 1) {
		bool overr = true;
		for (auto&z :zombies)
		{
			if (z->die_flag != 1)
			{
				overr = false;
			}

		}
		if (overr && ((int)zombies.size() >= ZOMBIE_END)) overflag = 1;
	}
	else if (Map::level == 2) {
		int die_num = 0;
		for (auto&z : zombies) {
			die_num += z->die_flag;
		}
		if (die_num == 6) overflag = 1;
	}
	else if (Map::level == 3) {
		int die_num = 0;
		for (auto&z : zombies) {
			die_num += z->die_flag;
		}
		if (die_num == 9) overflag = 1;
	}
	

}

void CGameStateRun::judge_zombie_victory() {
	//結束---------------------
	bool over = false;
	for (auto &z : zombies) {
		if (z->GetLeft() <= 100) {
			over = true;
		}
	}
	if (over == true) {
		end_flag = 1;
	}
	
	if (end_flag == 1) {
		call_time = 0;
		tri_call_time = 0;
		bucketcall_time = 0;
		end_time += 1;
		if (end_time >= 300) {
			end_flag = 0;
			end_time = 0;
			GotoGameState(GAME_STATE_OVER);
		}
	}
	
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

void CGameStateRun::load_db_card() {
	db_card.LoadBitmapByString({ "Plants_vs_Zombies_Image/card/double_bean_card/db_card.bmp" }, RGB(255, 255, 255));
	db_card.SetTopLeft(570, 0);
}

void CGameStateRun::load_db_gray_card() {
	db_gray_card.LoadBitmapByString({ "Plants_vs_Zombies_Image/card/double_bean_card/db_gray_card.bmp" }, RGB(255, 255, 255));
	db_gray_card.SetTopLeft(570, 0);
}

void CGameStateRun::load_chili_card() {
	chili_card.LoadBitmapByString({"Plants_vs_Zombies_Image/card/chili_card/chili_card.bmp"}, RGB(0, 0, 0));
	chili_card.SetTopLeft(690, 0);

	chili_gray_card.LoadBitmapByString({"Plants_vs_Zombies_Image/card/chili_card/chili_gray_card.bmp"}, RGB(0, 0, 0));
	chili_gray_card.SetTopLeft(690, 0);
}

void CGameStateRun::place_seat(int targetx, int targety,int item){
	
	//int seat_x[9];
	int map_topleftX = 200;
	int map_topleftY =  90;
	if (Map::level == 1) {
		int y = 2;
		for (int x = 0; x < 9; x++) {
			if (targetx >= map_topleftX + x * BLOCK_WIDTH && targetx < map_topleftX + (x + 1)*(BLOCK_WIDTH) && targety > map_topleftY + y * BLOCK_HEIGHT && targety < map_topleftY + (y + 1) * BLOCK_HEIGHT  && seat[x][y] != 2) {
				seat[x][y] = 1;
			}
		}
	}
	else if (Map::level == 2) {
		for (int y = 1; y < 4; y++) {
			for (int x = 0; x < 9; x++) {
				if (targetx >= map_topleftX + x * BLOCK_WIDTH && targetx < map_topleftX + (x + 1)*(BLOCK_WIDTH) && targety > map_topleftY + y * BLOCK_HEIGHT && targety < map_topleftY + (y + 1) * BLOCK_HEIGHT  && seat[x][y] != 2) {
					seat[x][y] = 1;
				}
			}
		}
	}
	else {
		for (int y = 0; y < 5; y++){
			for (int x = 0; x < 9; x++){
				if (targetx >= map_topleftX +x*BLOCK_WIDTH && targetx < map_topleftX+(x+1)*(BLOCK_WIDTH) && targety > map_topleftY + y * BLOCK_HEIGHT && targety < map_topleftY + (y + 1) * BLOCK_HEIGHT  && seat[x][y] != 2){
					seat[x][y] = 1;
				}
			}
		}
	}
	
	
	for (int y = 0; y < 5; y++){
		for (int x = 0; x < 9; x++){
			if (seat[x][y] == 1 ) {
				if (item == (int)PlantType::SUN_FLOWER) {
					plantManager.OnLButtonDown({(float)x,(float)y});
					money -= 50;
				}
				else if (item == (int)PlantType::BEAN_PLANT) {
					plantManager.OnLButtonDown({(float)x,(float)y});
					money -= 100;
				}
				else if (item == (int)PlantType::NUT_PLANT) {
					plantManager.OnLButtonDown({(float)x,(float)y});
					money -= 75;
				}
				else if (item == (int)PlantType::DOUBLE_BEAN) {
					plantManager.OnLButtonDown({(float)x,(float)y});
					money -= 200;
				}
				else if (item == (int)PlantType::CHILI_PLANT) {
					plantManager.OnLButtonDown({ (float)x,(float)y });
					money -= 150;
				}
				place_flag = 0;
				seat[x][y] = 2;
			}
		}
	}
}

void CGameStateRun::uproot(int targetx, int targety) {
	int map_topleftX = 200;
	int map_topleftY = 90;
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 9; x++) {
			if (targetx >= map_topleftX + x * BLOCK_WIDTH && targetx < map_topleftX + (x + 1)*(BLOCK_WIDTH) && targety > map_topleftY + y * BLOCK_HEIGHT && targety < map_topleftY + (y + 1) * BLOCK_HEIGHT ) {
				plantManager.PlantByShovel({ (float)x,(float)y});
				if (seat[x][y] != 0) {//表示一定有植物
					for (auto &z : zombies) {
						if (z->state == 4) {
							z->state = 0;
							z->speed = -1;
						}
					}
					clear_seat(x, y);
				}
				shovel.SetTopLeft(999, 999);
				shovel_flag = 0;
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
	//車車-------------------
	carList.clear();
	for (int i = 0; i < 5; i++)
	{
		Car newcar = Car();
		newcar.Init(i);
		carList.push_back(newcar);
	}
	//豌豆-----------------------
	//-----------------------------

	//雙豌豆-----------------------
	//-----------------------------
	//map-------------
	place_flag = 0;
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 5; y++) {
			seat[x][y] = 0;
		}
	}
	//---------------
	//殭屍-----------
	call_time = 0;
	tri_call_time = 0;
	bucketcall_time= 0;
	basic_counter = 0;
	tri_counter = 0;
	bucket_counter = 0;
	zombies.clear();
	//---------------

	//小太陽-----------
	sun_manager->clear_sun();
	pb_manager->clear();
	sun_cooldown = 0;
	//-----------------
	
	plantManager.clear_plant();
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
	CTextDraw::Print(pDC, 900, 185, std::to_string(tri_call_time));

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 215, std::to_string(bucketcall_time));

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 430, std::to_string(zombies.size()));


	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 50, 50, std::to_string(Map::level));

	CDDraw::ReleaseBackCDC();
}

int CGameStateRun::zb_y_random() {
	//[40, 140, 240, 340, 440] 殭屍的道路
	int zb_y[5];
	for (int i = 0; i < 5; i++) zb_y[i] = 40 + 100 * i;
	int ry = 0;
	if (Map::level == 1) {
		return 240;
	}
	else if (Map::level == 2) {
		ry = rand() % 3 + 1;
		return zb_y[ry];
	}
	else {
		ry = rand() % 5;
		return zb_y[ry];
	}
}

void CGameStateRun::call_tir_zombie() {
	if (tri_call_time == 210) {
		auto t = make_shared<Triangle_zombie>();
		t->init();
		t->SetTopLeft(950, zb_y_random());
		zombies.push_back(t);
		tri_counter += 1;
		tri_call_time = 0;
	}
	
}

void CGameStateRun::call_bucket_zombie() {
	if (bucketcall_time == 220) {
		auto bz = make_shared<Bucket_zombie>();
		bz->init();
		bz->SetTopLeft(950, zb_y_random());
		zombies.push_back(bz);
		bucket_counter += 1;
		bucketcall_time = 0;
	}
}