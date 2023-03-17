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
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	load_initialbackground();
	ShowInitProgress(0, "Plants_vs_Zombies_Image/Scenes/openingscene.bmp");	// 一開始的loading進度為0%
	Sleep(200);
	//
	// 開始載入資料
	//
	load_background();

	ShowInitProgress(66, "Initialize...");
	Sleep(200);
	//Sleep(1000);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (pointx >= 476 && pointx <= 797 && pointy >= 80 && pointy <= 188) {
		GotoGameState(GAME_STATE_RUN);
	}
}

void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
{
	pointx = point.x;
	pointy = point.y;
}

void CGameStateInit::OnShow()
{
	initialbackground.ShowBitmap();
	//background.ShowBitmap();
	start_button_1.ShowBitmap();
	draw_text();
}
void CGameStateInit::load_initialbackground() {
	initialbackground.LoadBitmapByString({ "Plants_vs_Zombies_Image/Scenes/openingscene.bmp" });
	initialbackground.SetTopLeft(0, 0);
}
void CGameStateInit::load_background() {
	background.LoadBitmapByString({ "Plants_vs_Zombies_Image/Scenes/Surface.bmp" });
	background.SetTopLeft(0, 0);

	start_button_1.LoadBitmapByString({ "Plants_vs_Zombies_Image/Scenes/SelectorScreenStartAdventure_1.bmp","Plants_vs_Zombies_Image/Scenes/SelectorScreenStartAdventure_2.bmp" }, RGB(255, 255, 255));
	start_button_1.SetTopLeft(475, 75);
}

void CGameStateInit::draw_text() {
	CDC *pDC = CDDraw::GetBackCDC();
	/* Print title */

	CTextDraw::ChangeFontLog(pDC,24, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 0, 0, std::to_string(pointx));
	CTextDraw::Print(pDC, 50, 0, std::to_string(pointy));

	CDDraw::ReleaseBackCDC();
}
void CGameStateInit::OnMove() {
	if (pointx >= 476 && pointx <= 797 && pointy >= 80 && pointy <= 188) {
		start_button_1.SetFrameIndexOfBitmap(1); //SetFrameIndexOfBitmap選擇圖片
	}
	else {
		start_button_1.SetFrameIndexOfBitmap(0);
	}
}