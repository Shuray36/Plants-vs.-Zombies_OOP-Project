#include "stdafx.h"
#include "PbManager.h"

void PbManager::MakePb(Vector2 pos)
{
    Pb s = Pb();
    s.init();
    s.SetPosition(pos);
    Vector2 moveDirection = {1,0};
    s.SetSpeed(Vector2::normal(moveDirection));
    pbs.push_back(s);
}

void PbManager::Update()
{
    for(auto &s:pbs)
    {
        s.Update();
    }
}

void PbManager::Show()
{
    for(auto &s:pbs)
    {
        s.Show();
    }
}

void PbManager::clear()
{
    pbs.clear();
}
