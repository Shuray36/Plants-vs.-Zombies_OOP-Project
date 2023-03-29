#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>





namespace game_framework {
class Zombie {
private:
	int hp;
	int atk;
	int state;
	double speed;
	CMovingBitmap a;
public:
	Zombie() {

	}
	~Zombie() = default;
	
};
}

#endif // ZOMBIE_H



