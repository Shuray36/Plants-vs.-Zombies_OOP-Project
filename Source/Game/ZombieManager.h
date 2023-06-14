#pragma once
#include <memory>
#include <vector>

#include "plant.h"
#include "zombie.h"

class Plant;

class ZombieManager
{
	std::vector<std::shared_ptr<Zombie>> zombies;
public:
	std::vector<std::shared_ptr<Zombie>> GetZombies();
	template<typename Z>
	void MakeZombie(int x, int y){
		auto z = std::make_shared<Z>();
		z->init();
		z->SetTopLeft(x, y);
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
	void Update(vector<shared_ptr<Plant>> plants)
	{
		for (auto&zom : zombies)
		{
			zom->SetTopLeft(zom->GetLeft() + zom->speed, zom->GetTop());
			for (auto &s : plants)
			{
				if (s->GetIsPlace()&&(zom->GetLeft() <= s->GetLeft() + 30 && zom->GetLeft() >= s->GetLeft() + 20 && zom->GetTop() <= s->GetTop() + 0 && zom->GetTop() >= s->GetTop() - 60 && zom->die_flag == 0) ){
					zom->state = 4;
					zom->cd += 1;
					if (zom->cd >= 100 && s->hp > 0) {
						zom->cd = 0;
						s->hp -= zom->attack;
					}
					if (s->hp <= 0) {
						SetAllZombieMove();
					}
				}
			}
		}
	}
	
};
