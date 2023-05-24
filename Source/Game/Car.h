#pragma once
#include "../Library/gameutil.h"

class Car :public game_framework::CMovingBitmap{
    
private:
    int speed;
    bool trigger;
    bool active;
    int goal;

public:
    void Init(int line);
    void Update();
    void Trigger();
    void SetGoal(int Goal);
    void ShowBitmap();

};
