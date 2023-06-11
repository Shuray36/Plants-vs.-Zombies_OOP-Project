#pragma once
#include "plant.h"
#include "../Library/gameutil.h"
#include "pb.h"

class Double_bean :public Bean{
public:
	Double_bean() ;
	void Attack() override;
};
