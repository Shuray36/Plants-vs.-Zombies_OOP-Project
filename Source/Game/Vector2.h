#pragma once

class Vector2
{
public:
    Vector2()=default;
    ~Vector2()=default;
    float x=0;
    float y=0;
    static Vector2 add(Vector2 a, Vector2 b);
    static bool equal(Vector2 a, Vector2 b);
    static float distance(Vector2 a, Vector2 b);
};
