#pragma once
#include <memory>
#include <vector>

#include "basic_zombie.h"
#include "bucket_zombie.h"
#include "plant.h"
#include "zombie.h"

class ZombieManager
{
	int call_time = 0;
	int tri_call_time = 0;
	int bucketcall_time = 0;
	
	int basic_counter = 0;
	int tri_counter = 0;
	int bucket_counter = 0;

	std::vector<std::shared_ptr<Zombie>> zombies;
public:
	std::vector<std::shared_ptr<Zombie>> GetZombies();
	template<typename Z = Zombie>
	void MakeZombie(int level){
		auto z = std::make_shared<Z>();
		z->init();
		z->SetTopLeft(950, zb_y_random(level));
		zombies.push_back(z);
	}
	template<typename Z = Zombie>
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
	void UpdateCallZombie(int level)
	{
		if (call_time == 200) {
			MakeZombie<Basic_zombie>(950, zb_y_random(level));
			basic_counter += 1;
			call_time = 0;
		}else if(basic_counter < 3)
		{
			call_time+=1;
		}
		if(level !=1)
		{
			if (tri_counter < 3) tri_call_time += 1;
			if (tri_call_time == 210) {
				MakeZombie<Basic_zombie>(950, zb_y_random(level));
				tri_counter += 1;
				tri_call_time = 0;
			}else if(basic_counter < 3)
			{
				call_time+=1;
			}
		}
		if(level >= 3){
			if (bucketcall_time == 220) {
				MakeZombie<Bucket_zombie>(950,zb_y_random(level));
				bucket_counter += 1;
				bucketcall_time = 0;
			}
		}
	}
	int zb_y_random(int level) {
		//[40, 140, 240, 340, 440] 殭屍的道路
		int zb_y[5];
		for (int i = 0; i < 5; i++) zb_y[i] = 40 + 100 * i;
		int ry = 0;
		if (level == 1) {
			return 240;
		}
		else if (level == 2) {
			ry = rand() % 3 + 1;
			return zb_y[ry];
		}
		else {
			ry = rand() % 5;
			return zb_y[ry];
		}
	}
};
