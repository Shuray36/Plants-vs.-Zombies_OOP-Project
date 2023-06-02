#include "stdafx.h"
#include "SunManager.h"

void SunManager::makeSun(Vector2 pos)
{
    makeSun(pos,pos);
}

void SunManager::makeSun(Vector2 pos, Vector2 goal)
{
    Sun s = Sun();
    s.SetPosition(pos);
    s.SetGoal(goal);
    Vector2 moveDirection = Vector2::sub(goal,pos);
    s.SetSpeed(Vector2::normal(moveDirection));
    suns.push_back(s);
}

void SunManager::Update()
{
    for(auto &s:suns)
    {
        s.Update();
    }
}

int SunManager::Lbutton(Vector2 point)
{
    int money =0;
    for(auto &s:suns)
    {
        if( s.IsPoint(point) )
        {
            money+=300;
            s.SetActive(false);
        }
    }
    for(int i =(int)suns.size()-1;i>=0;i--)
    {
        if(!suns[i].GetActive())
        {
            suns.erase(suns.begin()+i);
        }
    }
    return money;
}

void SunManager::ShowSun()
{
    for(auto &s:suns)
    {
        s.Show();
    }
}

void SunManager::clear_sun() {
	suns.clear();
}