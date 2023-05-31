#include "stdafx.h"
#include "Vector2.h"

Vector2 Vector2::add(Vector2 a, Vector2 b)
{
    return {a.x+b.x,a.y+b.y}; 
}

Vector2 Vector2::sub(Vector2 a, Vector2 b)
{
    return {a.x-b.x,a.y-b.y};
}

Vector2 Vector2::normal(Vector2 a)
{
    auto length = distance(a,{0,0});
    if(length==0)
    {
        return {0,0};
    }else
    {
        return {a.x/length,a.y/length};
    }
}

bool Vector2::equal(Vector2 a, Vector2 b)
{
    return a.x==b.x&&a.y==b.y;
}

float Vector2::distance(Vector2 a, Vector2 b)
{
    return (float)sqrt(((a.y - b.y) * (a.y - b.y) + (a.x - b.x) * (a.x - b.x)));
}
