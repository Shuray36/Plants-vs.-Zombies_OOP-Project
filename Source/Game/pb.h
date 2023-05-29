#pragma once
#include "../Library/gameutil.h"
#include <vector>
class Pb : public game_framework::CMovingBitmap {
public:
	void init();
	int show_flag = 1;
	void leave();
};