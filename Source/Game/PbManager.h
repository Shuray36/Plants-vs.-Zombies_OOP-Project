#pragma once
#include <vector>

#include "pb.h"
#include "Vector2.h"

class PbManager
{
    std::vector<Pb> pbs;
public:
    void MakePb(Vector2 pos);
    void Update();
    void Show();
    void clear();
};
