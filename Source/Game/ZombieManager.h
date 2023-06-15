#pragma once
#include <memory>
#include <vector>

#include "basic_zombie.h"
#include "bucket_zombie.h"
#include "triangle_zombie.h"
#include "plant.h"
#include "zombie.h"
#include "map.h"

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
		z->SetPosition({ 950.0f,(float)zb_y_random(level) });
		//z->SetTopLeft(950, zb_y_random(level));
		zombies.push_back(z);
	}
	template<typename Z = Zombie>
	void MakeZombie(int x, int y){
		auto z = std::make_shared<Z>();
		z->init();
		z->SetPosition({ (float)x,(float)y });
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
				//z->speed = -1;
				z->SetSpeed({ -0.5f,0.0f });
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
			zom->Update();
			//Map::level = zom->state;
			//zom->SetTopLeft(zom->GetLeft() + zom->speed, zom->GetTop());
			for (auto &s : plants)
			{
				if (s->GetIsPlace()&&(zom->GetLeft() + 50 <= s->GetLeft() + s->GetWidth() && zom->GetLeft() + 50 >= s->GetLeft() && zom->GetTop() <= s->GetTop() + 0 && zom->GetTop() >= s->GetTop() - 60 && zom->die_flag == 0) ){
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
		if (call_time == 400) {
			MakeZombie<Basic_zombie>(950, zb_y_random(level));
			basic_counter += 1;
			call_time = 0;
		}else if(basic_counter < 6)
		{
			call_time+=1;
		}
		if(level !=1)
		{
			if (tri_counter < 3) tri_call_time += 1;
			if (tri_call_time == 450) {
				MakeZombie<Triangle_zombie>(950, zb_y_random(level));
				tri_counter += 1;
				tri_call_time = 0;
			}
			/*
			else if(basic_counter < 3)
			{
				call_time+=1;
			}
			*/
			
		}
		if(level >= 3){
			if (bucket_counter < 3) bucketcall_time += 1;
			if (bucketcall_time == 550) {
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
	void reset_call_time() {
		call_time = 0;
		tri_call_time = 0;
		bucketcall_time = 0;

		basic_counter = 0;
		tri_counter = 0;
		bucket_counter = 0;
	}
	void SetCallTime(int time) {
		call_time = time;
	}
	void SetTriTime(int time) {
		tri_call_time = time;
	}
	void SetBucketTime(int time) {
		bucketcall_time = time;
	}
};

