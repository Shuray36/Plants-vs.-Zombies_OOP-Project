#include "stdafx.h"

#include "Car.h"

void Car::Init(int line){
    trigger = false;
	LoadBitmapByString({ "Plants_vs_Zombies_Image/car/car.bmp" }, RGB(255, 255, 255));
    active = true;
    int mapLeft = 140;
    int mapTop = 125;
    int yDistance = 85;
    int xDistance = 85;//not sure
    int mapXNum =9;
    speed = 10;
    SetTopLeft(mapLeft,mapTop+line*yDistance);
    SetGoal(mapLeft+xDistance*mapXNum);
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

void Car::Trigger()
{
    trigger=true;
}

void Car::SetGoal(int Goal)
{
    goal = Goal;
}

void Car::ShowBitmap()
{
    if(active)
    {
        CMovingBitmap::ShowBitmap();
    }
}
