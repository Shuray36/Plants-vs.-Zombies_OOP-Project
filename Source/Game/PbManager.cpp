#include "stdafx.h"
#include "PbManager.h"


void PbManager::MakePb(Vector2 pos,int y)
{
	
	
	for (auto z : zombies) {
		if ((int)z->GetTop() == a[y]) {
			Pb s = Pb();
			s.init();
			s.SetPosition(pos);
			pbs.push_back(s);
			break;
		}
	}
	
	
    
}

void PbManager::Update()
{
    for(auto &s:pbs)
    {
		for (auto&zom : zombies)
		{
			if (s.GetLeft() <= zom->GetLeft() + 50 && s.GetLeft() >= zom->GetLeft() + 45 && s.GetTop() <= zom->GetTop() + 60 && s.GetTop() >= zom->GetTop() - 0 && zom->die_flag == 0) {
				game_framework::CAudio* audio = game_framework::CAudio::Instance();
				audio->Play(2, false);
				s.leave();
				zom->hp -= 30;
				if (zom->hp <= 0) {
					zom->state = 1;
					zom->die_flag = 1;
				}
			    s.SetActive(false);
			}
		}
        s.Update();
    }
	for(int i = (int)pbs.size()-1; i >=0 ;i--)
	{
		if(!pbs[i].GetActive())
		{
			pbs.erase(pbs.begin()+i);
		}
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

void PbManager::SetZombies(vector<shared_ptr<Zombie>> z)
{
	zombies = z;
}
