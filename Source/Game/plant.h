#ifndef PLANT_H
#define PLANT_H

#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

#include <string>

class Plant {
private:
	int hp;  //血量
	int state; // 狀態
protected:
	int atk; //攻擊力
	int counter; // 次數
	int time;  //時間
public:
	Plant() {

	}
	~Plant() = default;
	virtual void Skill() {};

};

#endif // PLANT_H