#pragma once
#include "Vector2.h"
#include "../Library/gameutil.h"
#include "Counter.h"
#define PZTIME 10
#define BLOCK_WIDTH  82
#define BLOCK_HEIGHT  96
#define  BoardTop 100
#define  BoardLeft 207

class PZGameObject :public game_framework::CMovingBitmap
{
private:
    bool _active=true;
    Vector2 _position;
    Vector2 _collider;
    Vector2 _speed;
    
public:
    virtual void SetPosition(Vector2 position);
    void SetPositionByCenter(Vector2 position);
    Vector2 GetPosition();
    void SetActive(bool active);
    bool GetActive();
    virtual void Init();
    virtual void Update();
    virtual void Show();
    void SetSpeed(Vector2 s);

    //todo isOverlap with _collider
    bool IsPoint(Vector2 p);
};
