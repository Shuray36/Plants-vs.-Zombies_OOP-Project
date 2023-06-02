#pragma once
#include <vector>

#include "Sun.h"

class SunManager
{
    std::vector<Sun> suns;
public:
    void makeSun(Vector2 pos);
    void makeSun(Vector2 pos, Vector2 goal);
    void Update();
    int Lbutton(Vector2 point);
    void ShowSun();
	void clear_sun();
};
