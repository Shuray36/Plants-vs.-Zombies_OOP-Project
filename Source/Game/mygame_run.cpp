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
	sun_manager->Update();
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
	
		for(auto& z : basic_zombie){
			z.SetTopLeft(z.GetLeft() + z.speed, z.GetTop());
		}
		for (auto&t : tri_zombie) t.SetTopLeft(t.GetLeft() + t.speed, t.GetTop());
		for (auto&bz : bucket_zombie) bz.SetTopLeft(bz.GetLeft() + bz.speed, bz.GetTop());
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
		for(auto &b:bean_plant)
		{
			b.cd+=1;
			if (b.cd >= 50) {
				b.pb.show_flag = 0;
			}
			b.attack();
			for(auto& z : basic_zombie){
				if (b.pb.GetLeft() <= z.GetLeft() + 50 && b.pb.GetLeft() >= z.GetLeft() + 45 && b.pb.GetTop() <= z.GetTop() + 60 && b.pb.GetTop() >= z.GetTop() - 0 && z.die_flag == 0) {
					b.leave();
					b.pb.show_flag = 1;
					z.hp -= 30;
					if (z.hp <= 0) {
						z.state = 1;
						z.die_flag = 1;
					}
				}
			}
			//triangle_zombie------------------------
			for (auto& t : tri_zombie) {
				if (b.pb.GetLeft() <= t.GetLeft() + 50 && b.pb.GetLeft() >= t.GetLeft() + 45 && b.pb.GetTop() <= t.GetTop() + 60 && b.pb.GetTop() >= t.GetTop() - 0 && t.die_flag == 0) {
					b.leave();
					b.pb.show_flag = 1;
					t.hp -= 30;
					if (t.hp <= 0) {
						t.state = 1;
						t.die_flag = 1;
					}
				}
			}
			if (b.cd >= 250) {
				b.reload();
				b.cd = 0;
			}
			//bucket_zombie----------------------------
			for (auto& bz : bucket_zombie) {
				if (b.pb.GetLeft() <= bz.GetLeft() + 50 && b.pb.GetLeft() >= bz.GetLeft() + 45 && b.pb.GetTop() <= bz.GetTop() + 60 && b.pb.GetTop() >= bz.GetTop() - 0 && bz.die_flag == 0) {
					b.leave();
					b.pb.show_flag = 1;
					bz.hp -= 30;
					if (bz.hp <= 0) {
						bz.state = 1;
						bz.die_flag = 1;
					}
				}
			}
			if (b.cd >= 250) {
				b.reload();
				b.cd = 0;
			}
			//-----------------------------------------
		}
		//double_bean 射擊
		for (auto &🥒🥒 : double_bean) {
			🥒🥒.cd += 1;
			if (🥒🥒.cd >= 50) {
				🥒🥒.pb1.show_flag = 0;
				if (🥒🥒.cd >= 60) 🥒🥒.pb2.show_flag = 0;
				
			}
			🥒🥒.attack();
			for(auto& z : basic_zombie){
				if (🥒🥒.pb1.GetLeft() <= z.GetLeft() + 50 && 🥒🥒.pb1.GetLeft() >= z.GetLeft() + 45 && 🥒🥒.pb1.GetTop() <= z.GetTop() + 60 && 🥒🥒.pb1.GetTop() >= z.GetTop() - 0 && z.die_flag == 0) {
					🥒🥒.pb1.leave();
					🥒🥒.pb1.show_flag = 1;
					z.hp -= 30;
					if (z.hp <= 0) {
						z.state = 1;
						z.die_flag = 1;
					}
				}
				if (🥒🥒.pb2.GetLeft() <= z.GetLeft() + 50 && 🥒🥒.pb2.GetLeft() >= z.GetLeft() + 45 && 🥒🥒.pb2.GetTop() <= z.GetTop() + 60 && 🥒🥒.pb2.GetTop() >= z.GetTop() - 0 && z.die_flag == 0) {
					🥒🥒.pb2.leave();
					🥒🥒.pb2.show_flag = 1;
					z.hp -= 30;
					if (z.hp <= 0) {
						z.state = 1;
						z.die_flag = 1;
					}
				}
				
			}
			//triangle_zombie----------------------
			for (auto& t : tri_zombie) {
				if (🥒🥒.pb1.GetLeft() <= t.GetLeft() + 50 && 🥒🥒.pb1.GetLeft() >= t.GetLeft() + 45 && 🥒🥒.pb1.GetTop() <= t.GetTop() + 60 && 🥒🥒.pb1.GetTop() >= t.GetTop() - 0 && t.die_flag == 0) {
					🥒🥒.pb1.leave();
					🥒🥒.pb1.show_flag = 1;
					t.hp -= 30;
					if (t.hp <= 0) {
						t.state = 1;
						t.die_flag = 1;
					}
				}
				if (🥒🥒.pb2.GetLeft() <= t.GetLeft() + 50 && 🥒🥒.pb2.GetLeft() >= t.GetLeft() + 45 && 🥒🥒.pb2.GetTop() <= t.GetTop() + 60 && 🥒🥒.pb2.GetTop() >= t.GetTop() - 0 && t.die_flag == 0) {
					🥒🥒.pb2.leave();
					🥒🥒.pb2.show_flag = 1;
					t.hp -= 30;
					if (t.hp <= 0) {
						t.state = 1;
						t.die_flag = 1;
					}
				}

			}
			//bucket_zombie-------------------------
			for (auto& bz : bucket_zombie) {
				if (🥒🥒.pb1.GetLeft() <= bz.GetLeft() + 50 && 🥒🥒.pb1.GetLeft() >= bz.GetLeft() + 45 && 🥒🥒.pb1.GetTop() <= bz.GetTop() + 60 && 🥒🥒.pb1.GetTop() >= bz.GetTop() - 0 && bz.die_flag == 0) {
					🥒🥒.pb1.leave();
					🥒🥒.pb1.show_flag = 1;
					bz.hp -= 30;
					if (bz.hp <= 0) {
						bz.state = 1;
						bz.die_flag = 1;
					}
				}
				if (🥒🥒.pb2.GetLeft() <= bz.GetLeft() + 50 && 🥒🥒.pb2.GetLeft() >= bz.GetLeft() + 45 && 🥒🥒.pb2.GetTop() <= bz.GetTop() + 60 && 🥒🥒.pb2.GetTop() >= bz.GetTop() - 0 && bz.die_flag == 0) {
					🥒🥒.pb2.leave();
					🥒🥒.pb2.show_flag = 1;
					bz.hp -= 30;
					if (bz.hp <= 0) {
						bz.state = 1;
						bz.die_flag = 1;
					}
				}

			}
			//--------------------------------------
			if (🥒🥒.cd >= 200) {
				🥒🥒.reload();
				🥒🥒.cd = 0;
			}

		}
		//fix me 植物應該在殭屍出現才開始射擊 
		//-----------------------



		//殭屍攻擊---------------

		for(auto &z : basic_zombie){
			//bean-------------------------------------
			for(auto &b:bean_plant)
			{
				if (z.GetLeft() <= b.GetLeft() + 30 && z.GetLeft() >= b.GetLeft() + 20 && z.GetTop() <= b.GetTop() + 0 && z.GetTop() >= b.GetTop() -60 && z.die_flag == 0)
				{
					z.state = 4;
					z.cd += 1;
					if (z.cd >= 100 && b.hp > 0) {
						z.cd = 0;
						b.hp -= 30;
					}
					if (b.hp <= 0) {
						for (auto& zz : basic_zombie) {
							if (zz.state == 4) {
								zz.cd = 0;
								zz.state = 0;
								zz.speed = -1;
							}
						}
						clear_seat((int)b.GetCoordinateX(),(int) b.GetCoordinateY());
					}
				}
			}
			//太陽花-------------------------------------
			for (auto &s : plantManager.GetPlants()) {
				if (z.GetLeft() <= s->GetLeft() + 30 && z.GetLeft() >= s->GetLeft() + 20 && z.GetTop() <= s->GetTop() + 0 && z.GetTop() >= s->GetTop() - 60 && z.die_flag == 0) {
					z.state = 4;
					z.cd += 1;
					if (z.cd >= 100 && s->hp > 0) {
						z.cd = 0;
						s->hp -= 50;
					}
					if (s->hp <= 0) {
						for (auto& zz : basic_zombie) {
							if (zz.state == 4) {
								zz.cd = 0;
								zz.state = 0;
								zz.speed = -1;
							}
						}
						clear_seat((int)s->GetCoordinateX(), (int)s->GetCoordinateY());
					}
				}
				//--------------------------------------------
			}
			//nut-------------------------------------
				//--------------------------------------------
			//double_bean-------------------------------------
			for (auto &db : double_bean) {
				if (z.GetLeft() <= db.GetLeft() + 30 && z.GetLeft() >= db.GetLeft() + 20 && z.GetTop() <= db.GetTop() + 0 && z.GetTop() >= db.GetTop() - 60 && z.die_flag == 0) {
					z.state = 4;
					z.cd += 1;
					if (z.cd >= 100 && db.hp > 0) {
						z.cd = 0;
						db.hp -= 30;
					}
					if (db.hp <= 0) {
						for (auto& zz : basic_zombie) {
							if (zz.state == 4) {
								zz.cd = 0;
								zz.state = 0;
								zz.speed = -1;
							}
						}
						clear_seat((int)db.GetCoordinateX(), (int)db.GetCoordinateY());
					}
				}
				//--------------------------------------------
			}
		}
		tri_zombie_attack(); //三角殭屍攻擊
		bucket_zombie_attack(); //鐵桶殭屍攻擊

		//太陽花技能----------------------
		//--------------------------------
		
		for (auto &car : carList) {
			for(auto&z : basic_zombie)
			{
				if (car.GetLeft() >= z.GetLeft() + 0 && car.GetLeft() <= z.GetLeft() + 100 && car.GetTop() >= z.GetTop() + 0 && car.GetTop() <= z.GetTop() + 100)
				{
					car.Trigger();
					z.state=3;
				}
			}
			for (auto&t : tri_zombie)
			{
				if (car.GetLeft() >= t.GetLeft() + 0 && car.GetLeft() <= t.GetLeft() + 100 && car.GetTop() >= t.GetTop() + 0 && car.GetTop() <= t.GetTop() + 100)
				{
					car.Trigger();
					t.state = 3;
				}
			}
			for (auto&bz : bucket_zombie)
			{
				if (car.GetLeft() >= bz.GetLeft() + 0 && car.GetLeft() <= bz.GetLeft() + 100 && car.GetTop() >= bz.GetTop() + 0 && car.GetTop() <= bz.GetTop() + 100)
				{
					car.Trigger();
					bz.state = 3;
				}
			}
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
	
	
	for(auto& b:bean_plant) b.init();
	for (auto& db : double_bean) db.init();
	load_sunback();
	load_sunflower_card();
	load_sunflower_gray_card();
	load_peashooter_gray_card();
	load_peashooter_card();
	load_nut_card();
	load_nut_gray_card();
	load_db_card();
	load_db_gray_card();
	load_zombie_win_picture();
	load_plant_win_picture();

	plantManager.setSunmanager(sun_manager);
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
		auto z = Basic_zombie();
		z.init();
		z.SetTopLeft(950, 40);
		basic_zombie.push_back(z);
	}
	if (nChar == 0x32) {//2
		auto z = Basic_zombie();
		z.init();
		z.SetTopLeft(950, 140);
		basic_zombie.push_back(z);
	}
	if (nChar == 0x33) {//3
		auto z = Basic_zombie();
		z.init();
		z.SetTopLeft(950, 240);
		basic_zombie.push_back(z);
	}
	if (nChar == 0x34) {//4
		auto z = Basic_zombie();
		z.init();
		z.SetTopLeft(950, 340);
		basic_zombie.push_back(z);
	}
	if (nChar == 0x35) {//5
		auto z = Basic_zombie();
		z.init();
		z.SetTopLeft(950, 440);
		basic_zombie.push_back(z);
	}
	if (nChar == 0x4A) {//j
		/*
		auto z = Basic_zombie();
		z.init();
		z.SetTopLeft(950, zb_y_random());
		basic_zombie.push_back(z);
		*/
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
		/*
		auto t = Triangle_zombie();
		t.init();
		t.SetTopLeft(950, 240);
		tri_zombie.push_back(t);
		*/
		
	}
	if (nChar == 0x4C) {//L

		auto bz = make_shared<Bucket_zombie>();
		bz->init();
		bz->SetTopLeft(950, zb_y_random());
		zombies.push_back(bz);
		/*
		auto bz = Bucket_zombie();
		bz.init();
		bz.SetTopLeft(950, 240);
		bucket_zombie.push_back(bz);
		*/
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
		Bean newflower = Bean();
		newflower.init();
		bean_plant.push_back(newflower);
	}
	
	if (CMovingBitmap::IsCardClick(pointx, pointy, nut_card) && money >= 75) {
		item = 2;
		place_flag = 1;
		plantManager.MakePlant(PlantType::NUT_PLANT,mousePosition);
	}

	if (CMovingBitmap::IsCardClick(pointx, pointy, db_card) && money >= 100 && Map::level != 1) {
		item = 3;
		place_flag = 1;
		Double_bean d = Double_bean();
		d.init();
		double_bean.push_back(d);
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
	plantManager.OnMouseMove({ static_cast<float>(point.x),static_cast<float>(point.y)});
	if (!bean_plant.empty()&&!bean_plant.back().GetIsPlace()) {
		bean_plant.back().SetTopLeft(pointx - 32, pointy - 25);
	}
	if (!double_bean.empty() && !double_bean.back().GetIsPlace()) {
		double_bean.back().SetTopLeft(pointx - 32, pointy - 25);
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
		if (BG1_flag1 == 2) {
			for (auto &z : basic_zombie) z.show();
			for (auto &t : tri_zombie) t.show();
			for (auto &bz : bucket_zombie) bz.show();
			for (auto &zom : zombies) zom->show();
			//if ((int)basic_zombie.size() < ZOMBIE_END) call_time += 1;
			if (call_time == 200) {
				auto z = Basic_zombie();
				z.init();
				z.SetTopLeft(950, zb_y_random());
				basic_zombie.push_back(z);
				call_time = 0;
			}
			//召喚殭屍------------------------------------
			sun_manager->ShowSun();
			for (auto&car : carList) {
				car.ShowBitmap();
			}
			plantManager.Show();
			
		}
	}
	else if (Map::level == 2) {
		L2_map.ShowBitmap();
		if (BG1_flag1 == 2) {
			for (auto &z : basic_zombie) z.show();
			for (auto &t : tri_zombie) t.show();
			for (auto &bz : bucket_zombie) bz.show();
			if ((int)basic_zombie.size() < 3) call_time += 1;
			if (call_time == 200) {
				auto z = Basic_zombie();
				z.init();
				z.SetTopLeft(950, zb_y_random());
				basic_zombie.push_back(z);
				call_time = 0;
			}
			if ((int)tri_zombie.size() < 3) tri_call_time += 1;
			call_tir_zombie(); //召喚三角殭屍
			//召喚殭屍------------------------------------
			sun_manager->ShowSun();
			for (auto&car : carList) {
				car.ShowBitmap();
			}
			plantManager.Show();
		}
	}
	else if (Map::level == 3) {
		fight_background.ShowBitmap();
		if (BG1_flag1 == 2) {
			for (auto &z : basic_zombie) z.show();
			for (auto &t : tri_zombie) t.show();
			for (auto &bz : bucket_zombie) bz.show();
			if ((int)basic_zombie.size() < 3) call_time += 1;
			if (call_time == 200) {
				auto z = Basic_zombie();
				z.init();
				z.SetTopLeft(950, zb_y_random());
				basic_zombie.push_back(z);
				call_time = 0;
			}
			if ((int)tri_zombie.size() < 3) tri_call_time += 1;
			call_tir_zombie(); //召喚三角殭屍
			if ((int)bucket_zombie.size() < 3) bucketcall_time += 1;
			call_bucket_zombie();
			//召喚殭屍------------------------------------
			sun_manager->ShowSun();
			for (auto&car : carList) {
				car.ShowBitmap();
			}
			plantManager.Show();
		}
	}

	for(auto &b : bean_plant) b.show();
	for (auto &db : double_bean) db.show();
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
	
	if (overflag == 1) {
		basic_zombie.clear();
		tri_zombie.clear();
		bucket_zombie.clear();
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
		for (auto&z : basic_zombie)
		{
			if (z.die_flag != 1)
			{
				overr = false;
			}

		}
		if (overr && ((int)basic_zombie.size() >= ZOMBIE_END)) overflag = 1;
	}
	else if (Map::level == 2) {
		bool overr = true;
		for (auto&z : basic_zombie){
			if (z.die_flag != 1)
			{
				overr = false;
			}

		}
		for (auto&t : tri_zombie) {
			if (t.die_flag != 1) {
				overr = false;
			}
		}
		if(overr && ((int)basic_zombie.size() >= 3) && (int)tri_zombie.size()>=3) overflag = 1;
	}
	else if (Map::level == 3) {
		bool overr = true;
		for (auto&z : basic_zombie) {
			if (z.die_flag != 1)
			{
				overr = false;
			}

		}
		for (auto&t : tri_zombie) {
			if (t.die_flag != 1) {
				overr = false;
			}
		}
		for (auto& bz : bucket_zombie) {
			if (bz.die_flag != 1) {
				overr = false;
			}
		}
		if (overr && ((int)basic_zombie.size() >= 3) && (int)tri_zombie.size() >= 3 && (int)bucket_zombie.size() >= 3) overflag = 1;
	}
	

}

void CGameStateRun::judge_zombie_victory() {
	//結束---------------------
	bool over = false;
	if (Map::level == 1) {
		for (auto &z : basic_zombie) {
			if (z.GetLeft() <= 100) {
				over = true;
			}
		}
	}
	else if (Map::level == 2) {
		
		for (auto &z : basic_zombie) {
			if (z.GetLeft() <= 100) {
				over = true;
			}
		}
		for (auto &t : tri_zombie) {
			if (t.GetLeft() <= 100) {
				over = true;
			}
		}
	}
	else if (Map::level == 3) {
		for (auto &z : basic_zombie) {
			if (z.GetLeft() <= 100) {
				over = true;
			}
		}
		for (auto &t : tri_zombie) {
			if (t.GetLeft() <= 100) {
				over = true;
			}
		}
		for (auto &bz : bucket_zombie) {
			if (bz.GetLeft() <= 100) {
				over = true;
			}
		}
	}
	
	if (over == true) {
		end_flag = 1;
	}
	
	if (end_flag == 1) {
		basic_zombie.clear();
		tri_zombie.clear();
		bucket_zombie.clear();
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
					auto &newflower = bean_plant.back();
					newflower.SetTopLeft(207+BLOCK_WIDTH*x, 100+BLOCK_HEIGHT*y);
					newflower.SetCoordinate(x,y);
					newflower.SetIsPlace(true);
					money -= 100;
				}
				else if (item == (int)PlantType::NUT_PLANT) {
					plantManager.OnLButtonDown({(float)x,(float)y});
					money -= 75;
				}
				else if (item == (int)PlantType::DOUBLE_BEAN) {
					auto &newdb = double_bean.back();
					newdb.SetTopLeft(207 + BLOCK_WIDTH * x, 100 + BLOCK_HEIGHT * y);
					newdb.SetCoordinate(x, y);
					newdb.SetIsPlace(true);
					money -= 200;
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
	//車車-------------------
	carList.clear();
	for (int i = 0; i < 5; i++)
	{
		Car newcar = Car();
		newcar.Init(i);
		carList.push_back(newcar);
	}
	//-----------------------------
	//太陽花-----------------------
	//-----------------------------
	//豌豆-----------------------
	bean_plant.clear();
	//-----------------------------
	//堅果-----------------------
	//-----------------------------
	//雙豌豆-----------------------
	double_bean.clear();
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
	basic_zombie.clear();
	tri_zombie.clear();
	bucket_zombie.clear();
	//---------------

	//小太陽-----------
	sun_manager->clear_sun();
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
	CTextDraw::Print(pDC, 900, 485, std::to_string(basic_zombie.size()));

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 515, std::to_string(tri_zombie.size()));

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(0, 0, 0));
	CTextDraw::Print(pDC, 900, 545, std::to_string(bucket_zombie.size()));

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

void CGameStateRun::tri_zombie_attack() {
	for (auto &z : tri_zombie) {
		//bean-------------------------------------
		for (auto &b : bean_plant)
		{
			if (z.GetLeft() <= b.GetLeft() + 30 && z.GetLeft() >= b.GetLeft() + 20 && z.GetTop() <= b.GetTop() + 0 && z.GetTop() >= b.GetTop() - 60 && z.die_flag == 0)
			{
				z.state = 4;
				z.cd += 1;
				if (z.cd >= 100 && b.hp > 0) {
					z.cd = 0;
					b.hp -= 30;
				}
				if (b.hp <= 0) {
					for (auto& zz : tri_zombie) {
						if (zz.state == 4) {
							zz.cd = 0;
							zz.state = 0;
							zz.speed = -1;
						}
					}
					clear_seat((int)b.GetCoordinateX(), (int)b.GetCoordinateY());
				}
			}
		}
		//太陽花-------------------------------------
		for (auto &s : plantManager.GetPlants()) {
			if (z.GetLeft() <= s->GetLeft() + 30 && z.GetLeft() >= s->GetLeft() + 20 && z.GetTop() <= s->GetTop() + 0 && z.GetTop() >= s->GetTop() - 60 && z.die_flag == 0) {
				z.state = 4;
				z.cd += 1;
				if (z.cd >= 100 && s->hp > 0) {
					z.cd = 0;
					s->hp -= 50;
				}
				if (s->hp <= 0) {
					for (auto& zz : tri_zombie) {
						if (zz.state == 4) {
							zz.cd = 0;
							zz.state = 0;
							zz.speed = -1;
						}
					}
					clear_seat((int)s->GetCoordinateX(), (int)s->GetCoordinateY());
				}
			}
			//--------------------------------------------
		}
		//nut-------------------------------------
		//--------------------------------------------
		//double_bean-------------------------------------
		for (auto &db : double_bean) {
			if (z.GetLeft() <= db.GetLeft() + 30 && z.GetLeft() >= db.GetLeft() + 20 && z.GetTop() <= db.GetTop() + 0 && z.GetTop() >= db.GetTop() - 60 && z.die_flag == 0) {
				z.state = 4;
				z.cd += 1;
				if (z.cd >= 100 && db.hp > 0) {
					z.cd = 0;
					db.hp -= 30;
				}
				if (db.hp <= 0) {
					for (auto& zz : tri_zombie) {
						if (zz.state == 4) {
							zz.cd = 0;
							zz.state = 0;
							zz.speed = -1;
						}
					}
					clear_seat((int)db.GetCoordinateX(), (int)db.GetCoordinateY());
				}
			}
			//--------------------------------------------
		}
	}
}

void CGameStateRun::bucket_zombie_attack() {
	for (auto &z : bucket_zombie) {
		//bean-------------------------------------
		for (auto &b : bean_plant)
		{
			if (z.GetLeft() <= b.GetLeft() + 30 && z.GetLeft() >= b.GetLeft() + 20 && z.GetTop() <= b.GetTop() + 0 && z.GetTop() >= b.GetTop() - 60 && z.die_flag == 0)
			{
				z.state = 4;
				z.cd += 1;
				if (z.cd >= 100 && b.hp > 0) {
					z.cd = 0;
					b.hp -= 50;
				}
				if (b.hp <= 0) {
					for (auto& zz : bucket_zombie) {
						if (zz.state == 4) {
							zz.cd = 0;
							zz.state = 0;
							zz.speed = -1;
						}
					}
					clear_seat((int)b.GetCoordinateX(), (int)b.GetCoordinateY());
				}
			}
		}
		//太陽花-------------------------------------
		for (auto &s : plantManager.GetPlants()) {
			if (z.GetLeft() <= s->GetLeft() + 30 && z.GetLeft() >= s->GetLeft() + 20 && z.GetTop() <= s->GetTop() + 0 && z.GetTop() >= s->GetTop() - 60 && z.die_flag == 0) {
				z.state = 4;
				z.cd += 1;
				if (z.cd >= 100 && s->hp > 0) {
					z.cd = 0;
					s->hp -= 50;
				}
				if (s->hp <= 0) {
					for (auto& zz : bucket_zombie) {
						if (zz.state == 4) {
							zz.cd = 0;
							zz.state = 0;
							zz.speed = -1;
						}
					}
					clear_seat((int)s->GetCoordinateX(), (int)s->GetCoordinateY());
				}
			}
			//--------------------------------------------
		}
		//nut-------------------------------------
		//--------------------------------------------
		//double_bean-------------------------------------
		for (auto &db : double_bean) {
			if (z.GetLeft() <= db.GetLeft() + 30 && z.GetLeft() >= db.GetLeft() + 20 && z.GetTop() <= db.GetTop() + 0 && z.GetTop() >= db.GetTop() - 60 && z.die_flag == 0) {
				z.state = 4;
				z.cd += 1;
				if (z.cd >= 100 && db.hp > 0) {
					z.cd = 0;
					db.hp -= 50;
				}
				if (db.hp <= 0) {
					for (auto& zz : bucket_zombie) {
						if (zz.state == 4) {
							zz.cd = 0;
							zz.state = 0;
							zz.speed = -1;
						}
					}
					clear_seat((int)db.GetCoordinateX(), (int)db.GetCoordinateY());
				}
			}
			//--------------------------------------------
		}
	}
}

void CGameStateRun::call_tir_zombie() {
	if (tri_call_time == 210) {
		auto t = Triangle_zombie();
		t.init();
		t.SetTopLeft(950, zb_y_random());
		tri_zombie.push_back(t);
		tri_call_time = 0;
	}
}

void CGameStateRun::call_bucket_zombie() {
	if (bucketcall_time == 220) {
		auto bz = Bucket_zombie();
		bz.init();
		bz.SetTopLeft(950, zb_y_random());
		bucket_zombie.push_back(bz);
		bucketcall_time = 0;
	}
}