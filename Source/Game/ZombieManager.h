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
		z->SetTopLeft(x, y);
		zombies.push_back(z);
	}
	void clear();
};
