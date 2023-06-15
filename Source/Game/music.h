#pragma once

#include "../Library/gameutil.h"
#include "../Library/audio.h"

class Music :public game_framework::CMovingBitmap{
private:
	game_framework::CAudio* sound;
public:
	Music() = default;
	void load_music();
	void play(int x,bool j);
	void pause();
	void Stop(int n);
};