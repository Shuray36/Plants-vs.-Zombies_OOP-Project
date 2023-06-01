#include "stdafx.h"
#include "../Core/Resource.h"
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>


bool Plant::CanAttack()
{
    return true;
}

void Plant::Attack()
{
}

void Plant::Init()
{
    PZGameObject::Init();
    attack.Set(100,0);
    hp = 100;
    _isPlace = false;
}

void Plant::Update()
{
    if(attack.counter>=attack.cycle)
    {
        if(CanAttack())
        {
            Attack();
            attack.counter =0;
        }
    }else
    {
        attack.counter+=PZTIME;
    }
    if(hp<=0)
    {
        SetActive(false);
    }
}

void Plant::SetCoordinate(int x, int y)
{
    SetCoordinate((float)x,(float)y);	
}

void Plant::SetCoordinate(float x, float y)
{
    coordinate.x = x;
    coordinate.y = y;
}
void Plant::SetCoordinate(Vector2 v)
{
    coordinate = v;
}

void Plant::Show()
{
    PZGameObject::Show();
}

int Plant::GetCoordinateX()
{
    return (int)coordinate.x;
}

int Plant::GetCoordinateY()
{
    return (int)coordinate.y;
}

bool Plant::GetIsPlace()
{
    return _isPlace;
}

void Plant::SetIsPlace(bool status)
{
    _isPlace = status;	
}

void Plant::SetAttackCounter(float cycle)
{
    attack.Set(cycle,0);
}
