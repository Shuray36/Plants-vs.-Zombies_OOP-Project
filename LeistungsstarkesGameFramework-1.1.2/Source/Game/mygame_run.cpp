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
		fight_background.SetTopLeft(fight_background.GetLeft() - 5, 0);
		if (fight_background.GetLeft() <= (-350)) BG1_flag1 = 1;
	}
	else if (fight_background.GetLeft() <= (350) && BG1_flag1==1 ) {
		fight_background.SetTopLeft(fight_background.GetLeft() + 5, 0);
		if (fight_background.GetLeft() >= (350)) BG1_flag1 = 2;
	}
	

}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	fight_background.LoadBitmapByString({ "Plants_vs_Zombies_Image/Scenes/BG1.bmp" });
	fight_background.SetTopLeft(0, 0);
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
	draw_text();
}
//-------------------------------------------------------------------------------------------
void CGameStateRun::draw_text() {
	CDC *pDC = CDDraw::GetBackCDC();
	/* Print title */

	CTextDraw::ChangeFontLog(pDC, 24, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 0, 0, std::to_string(pointx));
	CTextDraw::Print(pDC, 50, 0, std::to_string(pointy));

	CDDraw::ReleaseBackCDC();
}