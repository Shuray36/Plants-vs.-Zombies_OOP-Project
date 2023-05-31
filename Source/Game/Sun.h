#pragma once
#include "PZGameObject.h"
#include "../Library/gameutil.h"

class Sun: public PZGameObject{
    Vector2 goal;
public:
    Sun ();
    void LoadSun();
    void SetGoal(Vector2 g);
    void Update() override;
};
