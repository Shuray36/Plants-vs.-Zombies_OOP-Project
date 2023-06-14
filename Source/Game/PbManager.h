#pragma once
#include <memory>
#include <vector>

#include "pb.h"
#include "Vector2.h"
#include "zombie.h"

class PbManager
{
    std::vector<Pb> pbs;
    vector<shared_ptr<Zombie>> zombies;
public:
    void MakePb(Vector2 pos);
    void Update();
    void Show();
    void clear();
    void SetZombies(vector<shared_ptr<Zombie>> z);
};
