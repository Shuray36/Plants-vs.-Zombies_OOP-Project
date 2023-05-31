#pragma once
#include <vector>

#include "Sun.h"

class SunManager
{
    std::vector<Sun> suns;
public:
    void makeSun(Vector2 pos)
    {
        makeSun(pos,pos);
    }
    void makeSun(Vector2 pos, Vector2 goal)
    {
        Sun s = Sun();
        s.SetPosition(pos);
        s.SetGoal(goal);
        s.SetSpeed({0,1});
        suns.push_back(s);
    }
    void Update()
    {
        for(auto &s:suns)
        {
            s.Update();
        }
    }
    int Lbutton(Vector2 point)
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
    void ShowSun()
    {
        for(auto &s:suns)
        {
            s.Show();
        }
    }
};
