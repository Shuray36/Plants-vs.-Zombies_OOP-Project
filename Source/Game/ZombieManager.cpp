#include "stdafx.h"
#include "ZombieManager.h"

std::vector<std::shared_ptr<Zombie>> ZombieManager::GetZombies()
{
    return zombies;
}

void ZombieManager::clear()
{
    zombies.clear();
	call_time = 0;
	tri_call_time = 0;
	bucketcall_time = 0;
}
