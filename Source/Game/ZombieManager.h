#pragma once
#include <memory>
#include <vector>

#include "zombie.h"

class ZombieManager
{
	std::vector<std::shared_ptr<Zombie>> zombies;
public:
	std::vector<std::shared_ptr<Zombie>> GetZombies();
	template<typename Z>
	void MakeZombie(int x, int y){
		auto z = std::make_shared<Z>();
		z->init();
		z->SetPosition({(float)x,(float)y});
		//z->SetTopLeft(x, y);
		zombies.push_back(z);
	}
	void clear();
	int GetDienum()
	{
		int die_num = 0;
		for (auto&z : zombies) {
			die_num += z->die_flag;
		}
		return die_num;
	}
	bool GetZombieWin()
	{
		bool over = false;
		for (auto &z : zombies) {
			if (z->GetLeft() <= 100) {
				over = true;
			}
		}
		return over;
	}
	void SetAllZombieMove(){
		for (auto &z : zombies) {
			if (z->state == 4) {
				z->state = 0;
				z->speed = -1;
			}
		}
	}
	void Show()
	{
		for (auto &zom : zombies) zom->show();
	}
	bool CarTouch(int x,int y){
		bool result = false;
		for (auto &zom : zombies)
		{
			if (x >= zom->GetLeft() + 0 &&
			 x <= zom->GetLeft() + 100 &&
			 y >= zom->GetTop() + 0 &&
			 y <= zom->GetTop() + 100)
			{
				result =true;
				zom->state = 3;
			}
		}
		return result;
	}
	void Update()
	{
		for (auto&zom : zombies) {
			zom->Update();
			//zom->SetTopLeft(zom->GetLeft() + zom->speed, zom->GetTop());
		}
	}
	
};
