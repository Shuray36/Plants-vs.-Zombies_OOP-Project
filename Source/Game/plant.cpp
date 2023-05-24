#include "stdafx.h"
#include "../Core/Resource.h"
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>

void Plant::show() {
}
void Plant::init() {
    cd = 0;
    hp = 100;
    atk_speed = 0;
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

int Plant::GetCoordinateX()
{
    return (int)coordinate.x;
}

int Plant::GetCoordinateY()
{
    return (int)coordinate.y;
}
