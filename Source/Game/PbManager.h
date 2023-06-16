#pragma once
#include <memory>
#include <vector>

#include "pb.h"
#include "Vector2.h"
#include "zombie.h"
#include "../Library/audio.h"

class PbManager
{
    std::vector<Pb> pbs;
    vector<shared_ptr<Zombie>> zombies;
	int a[5] = { 40,140,240,340,440 };
public:
    void MakePb(Vector2 pos,int y);
    void Update();
    void Show();
    void clear();
    void SetZombies(vector<shared_ptr<Zombie>> z);
};
