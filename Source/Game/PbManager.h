#pragma once
#include <vector>

#include "pb.h"
#include "Vector2.h"

class PbManager
{
    
    std::vector<Pb> suns;
public:
    void makePb(Vector2 pos)
    {
        makePb(pos,pos);
    }
    void makePb(Vector2 pos, Vector2 goal)
    {
        
    }
    void Update();
    void Show();
	void clear();
};
