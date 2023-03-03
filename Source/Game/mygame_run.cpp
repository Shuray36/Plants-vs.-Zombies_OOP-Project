#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
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

bool CGameStateRun::OnMove(CMovingBitmap A, CMovingBitmap B)							// ���ʹC������
{
	if (A.Left() >=B.Left()-50 && A.Left() <= B.Left() + 50 && A.Top() >= B.Top() - 50 && A.Top() <= B.Top() + 50){
		return true;
	}
	else {
		return false;
	}
		
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	background.LoadBitmapByString({ 
		"resources/phase11_background.bmp", 
		"resources/phase12_background.bmp", 
		"resources/phase21_background.bmp", 
		"resources/phase22_background.bmp", 
		"resources/phase31_background.bmp", 
		"resources/phase32_background.bmp",
		"resources/phase41_background.bmp",
		"resources/phase42_background.bmp",
		"resources/phase51_background.bmp",
		"resources/phase52_background.bmp",
		"resources/phase61_background.bmp",
		"resources/phase62_background.bmp",
	});
	background.SetTopLeft(0, 0);

	character.LoadBitmapByString({ "resources/giraffe.bmp" });
	character.SetTopLeft(150, 265);

	chest_and_key.LoadBitmapByString({ "resources/chest.bmp", "resources/chest_ignore.bmp" }, RGB(255, 255, 255));
	chest_and_key.SetTopLeft(150, 430);

	bee.LoadBitmapByString({ "resources/bee_1.bmp", "resources/bee_2.bmp" });
	bee.SetTopLeft(462, 265);
	bee.SetAnimation(300, false);

	ball.LoadBitmapByString({ "resources/ball-3.bmp", "resources/ball-2.bmp", "resources/ball-1.bmp", "resources/ball-ok.bmp" });
	ball.SetTopLeft(150, 430);
	ball.SetAnimation(1000, true);
	ball.ToggleAnimation();

	for (int i = 0; i < 3; i++) {
		door[i].LoadBitmapByString({ "resources/door_close.bmp", "resources/door_open.bmp" }, RGB(255, 255, 255));
		door[i].SetTopLeft(462 - 100 * i, 265);
	}
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RETURN) {
		if (phase == 1) {
			if (sub_phase == 1) {
				sub_phase += validate_phase_1();
			}
			else if (sub_phase == 2) {
				sub_phase = 1;
				phase += 1;
			}
		} else if (phase == 2) {
			if (sub_phase == 1) {
				sub_phase += validate_phase_2();
			}
			else if (sub_phase == 2) {
				sub_phase = 1;
				phase += 1;
			}
		}else if (phase == 3) {
			if (sub_phase == 1) {
				sub_phase += validate_phase_3();
			}
			else if (sub_phase == 2) {
				sub_phase = 1;
				phase += 1;
			}
		}else if (phase == 4) {
			if (sub_phase == 1) {
				sub_phase += validate_phase_4();
			}
			else if (sub_phase == 2) {
				sub_phase = 1;
				phase += 1;
			}
		}else if (phase == 5) {
			if (sub_phase == 1) {
				sub_phase += validate_phase_5();
			}
			else if (sub_phase == 2) {
				sub_phase = 1;
				phase += 1;
			}
		}else if (phase == 6) {
			if (sub_phase == 1) {
				sub_phase += validate_phase_6();
			}
			else if (sub_phase == 2) {
				sub_phase = 1;
				phase += 1;
				GotoGameState(GAME_STATE_OVER);
			}
		}
	}
	if (nChar == VK_RIGHT) {
		// Do something...
		character.SetTopLeft(character.Left() + 30, character.Top() + 0);
	}
	if (nChar == VK_LEFT) {
		// Do something...
		character.SetTopLeft(character.Left() - 30, character.Top() + 0);
	}
	if (nChar == VK_UP) {
		// Do something...
		character.SetTopLeft(character.Left() + 0, character.Top() - 30);
	}
	if (nChar == VK_DOWN) {
		// Do something...
		character.SetTopLeft(character.Left() + 0, character.Top() + 30);
	}
	if (OnMove(character, chest_and_key) && phase==3) {
		chest_and_key.SelectShowBitmap(1);
	}
	if (OnMove(character, door[0]) && phase == 5) {
		door[0].SelectShowBitmap(1);
	}
	if (OnMove(character, door[1]) && phase == 5) {
		door[1].SelectShowBitmap(1);
	}
	if (OnMove(character, door[2]) && phase == 5) {
		door[2].SelectShowBitmap(1);
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnShow()
{
	show_image_by_phase();
	show_text_by_phase();
}

void CGameStateRun::show_image_by_phase() {
	if (phase <= 6) {
		background.SelectShowBitmap((phase - 1) * 2 + (sub_phase - 1));
		background.ShowBitmap();
		character.ShowBitmap();
		if (phase == 3 && sub_phase == 1) {
			chest_and_key.ShowBitmap();
		}
		if (phase == 4 && sub_phase == 1) {
			bee.ShowBitmap();
		}
		if (phase == 5 && sub_phase == 1) {
			for (int i = 0; i < 3; i++) {
				door[i].ShowBitmap();
			}
		}
		if (phase == 6 && sub_phase == 1) {
			ball.ShowBitmap();
		}
	}
}

void CGameStateRun::show_text_by_phase() {
	CDC *pDC = CDDraw::GetBackCDC();
	CFont* fp;

	CTextDraw::ChangeFontLog(pDC, fp, 21, "�L�n������", RGB(0, 0, 0), 800);

	if (phase == 1 && sub_phase == 1) {
		CTextDraw::Print(pDC, 237, 128, "�ק�A���D���I");
		CTextDraw::Print(pDC, 55, 163, "�N�Ǧ��洫�� resources ���� giraffe.bmp �ϼˡI");
		CTextDraw::Print(pDC, 373, 537, "���U Enter �������");
	} else if (phase == 2 && sub_phase == 1) {
		CTextDraw::Print(pDC, 26, 128, "�U�@�Ӷ��q�A�����V������z�L�W�U���k���ʨ�o�Ӧ�m�I");
		CTextDraw::Print(pDC, 373, 537, "���U Enter �������");
	} else if (phase == 3 && sub_phase == 1) {
		CTextDraw::Print(pDC, 205, 128, "���A�ǳƤF�@���_�c");
		CTextDraw::Print(pDC, 68, 162, "�]�p�{�������V���N���_�c��A�N�_�c�����I");
		CTextDraw::Print(pDC, 68, 196, "�O�o�_�c�n�h�I�A�ϥ� RGB(255, 255, 255)");
		CTextDraw::Print(pDC, 373, 537, "���U Enter �������");
	} else if (phase == 4 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "���A�ǳƤF�@�ӻe���n�B��");
		CTextDraw::Print(pDC, 89, 162, "�w�g�������F��V���ʵe�A�����i�H�W�U����");
		CTextDraw::Print(pDC, 110, 196, "�g�ӵ{�������A���e���n�B�;֦��ʵe�I");
		CTextDraw::Print(pDC, 373, 537, "���U Enter �������");
	} else if (phase == 5 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "���A�ǳƤF�T����");
		CTextDraw::Print(pDC, 89, 162, "�]�p�{�������V���N�������A���|���}");
		CTextDraw::Print(pDC, 373, 537, "���U Enter �������");
	} else if (phase == 6 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "���A�ǳƤF�@���|�˼ƪ��y");
		CTextDraw::Print(pDC, 89, 162, "�]�p�{�����y�˼ơA�M����� OK �ᰱ��ʵe");
		CTextDraw::Print(pDC, 373, 537, "���U Enter �������");
	} else if (sub_phase == 2) {
		CTextDraw::Print(pDC, 268, 128, "�����I");
	}

	CDDraw::ReleaseBackCDC();
}

bool CGameStateRun::validate_phase_1() {
	return character.GetImageFilename() == "resources/giraffe.bmp";
}

bool CGameStateRun::validate_phase_2() {
	return character.Top() > 204 && character.Top() < 325 && character.Left() > 339 && character.Left() < 459;
}

bool CGameStateRun::validate_phase_3() {
	return (
		character.Top() + character.Height() >= chest_and_key.Top()
		&& character.Left() + character.Width() >= chest_and_key.Left()
		&& chest_and_key.GetSelectShowBitmap() == 1
		&& chest_and_key.GetFilterColor() == RGB(255, 255, 255) 
	);
}

bool CGameStateRun::validate_phase_4() {
	return bee.IsAnimation() && bee.GetMovingBitmapFrame() == 2;
}

bool CGameStateRun::validate_phase_5() {
	bool check_all_door_is_open = true;
	for (int i = 0; i < 3; i++) {
		check_all_door_is_open &= (door[i].GetSelectShowBitmap() == 1);
	}
	return check_all_door_is_open;
}

bool CGameStateRun::validate_phase_6() {
	return ball.IsAnimationDone() && !ball.IsAnimation();
}