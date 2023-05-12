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
<<<<<<< HEAD


		int seat[9][5];
		int place_flag = 0;
		void place_seat(int x,int y,int item);
		int plant_place_max = 45;
		int item = -1;
		//----------------------
		
		//殭屍---------------
		Basic_zombie basic_zombie[3];
		int zombie_index = 0;
		int call_time = 0;
		int zombie_atk = 0;
		int zombie_atk_time = 0;
		//-------------------

		Sunflower sunflower[45];
		Sunflower testflower[9];
		int sunflower_index = 0;

		//射手-----------------------
		CMovingBitmap bean_plant_with_mouse;
		Bean bean_plant[20];
		Bean test_bean[10];
		int bean_plant_index = 0;
		int bean_plant_with_mouse_show = 0;
		void load_bean_plant_with_mouse();
		//---------------------------

=======
		int seat[9][5];
		int place_flag = 0;
		void place_seat(int x,int y);
		Basic_zombie basic_zombie;
		Sunflower sunflower;
		Sunflower testflower[9];
		int sunflower_index = 0;
		Bean bean_plant;
>>>>>>> c62af637a7982c05ddd401ddc0a01cb624279f35
		int pointx = 0;
		int pointy = 0;
		int money = 0;
		CMovingBitmap fight_background;

		//物件測試
		int move_right = 0;
		int move_left = 0;
		int move_up = 0;
		int move_down = 0;
		int test_x = 0;
		int test_y = 0;
		//--------

		// BG1的判斷變數
		int BG1_flag1 = 0;
		int time = 0;
		//殭屍---------------------------------------------------------------
		CMovingBitmap zombie[2];
		int zombie_change_flag = 0;
		void load_zombie_move();//殭屍移動圖片載入
		void load_zombie_eat();//殭屍吃圖片載入
		//-------------------------------------------------------------------

		//太陽花-------------------------------------------------------------
		CMovingBitmap sunflower_with_mouse;
		int sunflower_with_mouse_show = 0;
		bool sunflower_click_show = false;
		void load_sunflower();//太陽花圖片載入
		//-------------------------------------------------------------------

		//太陽記分板-----------------------------------------------------------------
		CMovingBitmap sunback;
		void load_sunback();
		//-------------------------------------------------------------------
<<<<<<< HEAD
=======

		//小太陽-----------------------------------------------------------------
		int sun_flag = 0;
		int sun_cooldown = 0;
		CMovingBitmap sun;
		void load_sun();
		//-------------------------------------------------------------------

		//車-----------------------------------------------------------------
		CMovingBitmap car[7];
		int car_run = 0;
		void load_car();
		//-------------------------------------------------------------------
		CMovingBitmap sunflower_card;
		void load_sunflower_card();
		CMovingBitmap sunflower_gray_card;
		void load_sunflower_gray_card();
		int sunflower_flag = 0;
		int sunflower_show_flag = 0;
		//
		//-------------------------------------------------------------------
		CMovingBitmap peashooter_card;
		void load_peashooter_card();
		CMovingBitmap peashooter_gray_card;
		void load_peashooter_gray_card();
		int pershooter_flag = 0;
		int pershooter_show_flag = 0;
		//


		//看位置的物件-------------------------------------------------------
		CMovingBitmap test;
		CMovingBitmap test2;
		void load_test();
		//-------------------------------------------------------------------
		int die_flag = 0;
		int die_time = 0;
		//地圖 位置左上(200,85) 右上(940,85) 左下(200,570) 右下(940,570)
>>>>>>> c62af637a7982c05ddd401ddc0a01cb624279f35

		//小太陽-----------------------------------------------------------------
		int sun_flag = 0;
		int sun_cooldown = 0;
		CMovingBitmap sun;
		void load_sun();
		//-------------------------------------------------------------------

		//車-----------------------------------------------------------------
		CMovingBitmap car[7];
		int car_run = 0;
		void load_car();
		//-------------------------------------------------------------------
		CMovingBitmap sunflower_card;
		void load_sunflower_card();
		CMovingBitmap sunflower_gray_card;
		void load_sunflower_gray_card();
		int sunflower_flag = 0;
		int sunflower_show_flag = 0;
		//
		//-------------------------------------------------------------------
		CMovingBitmap peashooter_card;
		void load_peashooter_card();
		CMovingBitmap peashooter_gray_card;
		void load_peashooter_gray_card();
		int pershooter_flag = 0;
		int pershooter_show_flag = 0;
		//


		//看位置的物件-------------------------------------------------------
		CMovingBitmap test;
		CMovingBitmap test2;
		void load_test();
		//-------------------------------------------------------------------
		int die_flag = 0;
		int die_time = 0;
		//地圖 位置左上(200,85) 右上(940,85) 左下(200,570) 右下(940,570)

		//int item = 0;
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