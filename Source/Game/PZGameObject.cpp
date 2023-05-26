#include "stdafx.h"
#include "PZGameObject.h"

void PZGameObject::SetPosition(Vector2 position)
{
    SetTopLeft((int)position.x,(int)position.y);
    _position = position;
}

Vector2 PZGameObject::GetPosition()
{
    return _position; 
}

void PZGameObject::SetActive(bool active)
{
    _active = active;
}

bool PZGameObject::GetActive()
{
    return _active; 
}
