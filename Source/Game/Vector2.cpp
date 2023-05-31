#include "stdafx.h"
#include "Vector2.h"

Vector2 Vector2::add(Vector2 a, Vector2 b)
{
    return {a.x+b.x,a.y+b.y}; 
}

bool Vector2::equal(Vector2 a, Vector2 b)
{
    return a.x==b.x&&b.x==b.y;
}

float Vector2::distance(Vector2 a, Vector2 b)
{
    return (float)sqrt(((a.y - b.y) * (a.y - b.y) + (a.x - b.x) * (a.x - b.x)));
}
