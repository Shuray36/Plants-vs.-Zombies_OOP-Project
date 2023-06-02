#include "stdafx.h"
#include "PZGameObject.h"

void PZGameObject::SetPosition(Vector2 position)
{
    SetTopLeft((int)position.x,(int)position.y);
    _position = position;
}

void PZGameObject::SetPositionByCenter(Vector2 position)
{
    _position ={static_cast<float>(position.x - static_cast<float>(GetWidth()) / 2.f),
                       static_cast<float>(position.y-static_cast<float>(GetHeight())/2.f) } ;
    SetTopLeft(static_cast<int>(_position.x),
                static_cast<int>(_position.y));
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

void PZGameObject::Init()
{
    _active = true;
    _position = {0,0};
    _collider = {0,0};
    _speed = {0,0};
}

void PZGameObject::Update()
{
    if(_active)
    {
       SetPosition(Vector2::add(GetPosition(),_speed));
    } 
}

void PZGameObject::Show()
{
    if(_active)
    {
        ShowBitmap();
    }
}

void PZGameObject::SetSpeed(Vector2 s)
{
    _speed = s;
}

bool PZGameObject::IsPoint(Vector2 p)
{
    return 
        p.x>_position.x &&
        p.x<_position.x+(float)GetWidth()&&
        p.y>_position.y &&
        p.y<_position.y+(float)GetHeight();
}
