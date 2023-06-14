/*
 * mygame.h: 本檔案儲遊戲本身的class的interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/
#include "zombie.h"
#include "plant.h"
#include <vector>
#include "map.h"
#include "Bean.h"
#include "double_bean.h"
#include "Car.h"
#include "Nut.h"
#include "chili.h"
#include "PlantManager.h"
#include "Sun.h"
#include "SunFlower.h"
#include "chili.h"
#include "SunManager.h"
#include "basic_zombie.h"
#include "triangle_zombie.h"
#include "bucket_zombie.h"
#include "ZombieManager.h"


namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
		void OnMove();
	private:
		CMovingBitmap logo;								// csie的logo
		void load_background();
		void draw_text();
		CMovingBitmap background;   
		CMovingBitmap start_button_1;
		CMovingBitmap start_button_2;
		int pointx = 0;
		int pointy = 0;

		CMovingBitmap level_menu;
		void load_level_menu();
		int menu_flag = 0;

		CMovingBitmap close_button;
		void load_close_button();

		CMovingBitmap L1;
		CMovingBitmap L2;
		CMovingBitmap L3;
		CMovingBitmap L4;
		CMovingBitmap L5;
		CMovingBitmap L6;
		void load_level();

	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
		void draw_text();
	private:
		int test = 0;
		//main
		PlantManager plantManager;
		int pointx = 0;
		int pointy = 0;
		int money = 1000;
		CMovingBitmap fight_background;
		CMovingBitmap L1_map;
		CMovingBitmap L2_map;
		// BG1的判斷變數
		int BG1_flag1 = 0;
		int time = 0;
		int overflag = 0;
		int overtime = 0;
		
		//map-------------------
		int place_flag = 0;
		void place_seat(int x,int y,int item);
		int item = -1;
		//----------------------
		
		//殭屍---------------
		int zombie_index = -1;
		int call_time = 0;
		int tri_call_time = 0;
		int bucketcall_time = 0;
		void call_tir_zombie();
		void call_bucket_zombie();
		int basic_counter = 0;
		int tri_counter = 0;
		int bucket_counter = 0;

		ZombieManager zombieManager;

		//-------------------

		//太陽花-----------------
		//--------------------------

		//射手-----------------------
		//---------------------------

		//堅果--------------------------
		//------------------------------

		//太陽記分板-----------------------------------------------------------------
		CMovingBitmap sunback;
		void load_sunback();
		//-------------------------------------------------------------------

		//小太陽-----------------------------------------------------------------
		int sun_flag = 0;
		int sun_cooldown = 500;
		shared_ptr<SunManager> sun_manager = make_shared<SunManager>();
		shared_ptr<PbManager> pb_manager = make_shared<PbManager>();
		//-------------------------------------------------------------------

		//車-----------------------------------------------------------------
		std::vector<Car> carList;
		//-------------------------------------------------------------------

		//card------------------------------------------------------------
		//太陽花----------------------------------------------------------
		CMovingBitmap sunflower_card;
		void load_sunflower_card();
		CMovingBitmap sunflower_gray_card;
		void load_sunflower_gray_card();
		int sunflower_flag = 0;
		//射手----------------------------------------------------
		CMovingBitmap peashooter_card;
		void load_peashooter_card();
		CMovingBitmap peashooter_gray_card;
		void load_peashooter_gray_card();
		int pershooter_flag = 0;
		//堅果----------------------------------------------------
		CMovingBitmap nut_card;
		void load_nut_card();
		CMovingBitmap nut_gray_card;
		void load_nut_gray_card();
		int nut_flag = 0;
		//雙重豌豆射手---------------------------------------------
		CMovingBitmap db_card;
		void load_db_card();
		CMovingBitmap db_gray_card;
		void load_db_gray_card();
		int db_flag = 0;
		//辣椒------------------------------------------------------
		CMovingBitmap chili_card;
		void load_chili_card();
		CMovingBitmap chili_gray_card;
		int chili_flag = 0;
		//-------------------------------------------------------------------
		//地圖 位置左上(200,85) 右上(940,85) 左下(200,570) 右下(940,570)


		//end--------------------------
		CMovingBitmap zombie_win_picture;
		void load_zombie_win_picture();
		int end_flag = 0;
		int end_time = 0;

		void judge_plant_victory();
		void judge_zombie_victory();
		//int zombie_end = 6;
		//鏟子--------------------
		CMovingBitmap shovel_box;
		CMovingBitmap shovel;
		int shovel_flag = 0;
		CMovingBitmap plant_win_picture;
		void load_plant_win_picture();
		void uproot(int x, int y);
		//--------------------------
		//reset--------------------
		void reset();
		//-------------------------
		//隨機---------------------
		int zb_y_random();
		//------------------------
		
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
	};
}
