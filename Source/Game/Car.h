#pragma once

class Car :public game_framework::CMovingBitmap{
    
private:
    int speed;
    bool trigger;
    bool active;

public:
    void Init();
    void Update();
    void Trigger();

};