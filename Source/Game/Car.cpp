#include "stdafx.h"

#include "Car.h"

void Car::Init(){
    trigger = false;
	LoadBitmapByString({ "Plants_vs_Zombies_Image/car/car.bmp" }, RGB(255, 255, 255));
    active = true;
}

void Car::Update(){
    if(active){
        if(trigger){
            auto x = GetLeft();
            SetTopLeft(x+speed,GetTop());
            if(x>goal){
                active = false;
            }
        }
    }
}

void Car::SetGoal(int Goal)
{
    goal = Goal;
}
