#include "stdafx.h"
#include "ZombieManager.h"

std::vector<std::shared_ptr<Zombie>> ZombieManager::GetZombies()
{
    return zombies;
}

void ZombieManager::clear()
{
    zombies.clear();
}
