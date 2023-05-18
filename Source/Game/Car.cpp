#include "stdafx.h"


void Car::Init(){
    trigger = false;
	LoadBitmapByString({ "Plants_vs_Zombies_Image/car/car.bmp" }, RGB(255, 255, 255));
    active = true;
}

void Car::Update(){
    if(active){
        if(trigger){
            auto x = GetLeft();
            setTopLeft(x+speed,GetTop());
            if(x>mapRight){
                active = false;
            }
        }
    }
}

void Car::Trigger(){
    trigger = true;

}