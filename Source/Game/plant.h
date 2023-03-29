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
	int hp;  //��q
	int state; // ���A
protected:
	int atk; //�����O
	int counter; // ����
	int time;  //�ɶ�
public:
	Plant() {

	}
	~Plant() = default;
	virtual void Skill() {};

};

#endif // PLANT_H