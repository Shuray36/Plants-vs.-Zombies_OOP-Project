#pragma once
#include "Vector2.h"
#include "../Library/gameutil.h"

class PZGameObject :public game_framework::CMovingBitmap
{
private:
    bool _active;
    Vector2 _position;
    
public:
    void SetPosition(Vector2 position);
    Vector2 GetPosition();
    void SetActive(bool active);
    bool GetActive();
};
