#pragma once
#include "plant.h"
#include "../Library/gameutil.h"
#include "pb.h"
#include "PbManager.h"

class Bean:public Plant {
	shared_ptr<PbManager> pb_manager;
public:
	Bean();
	void Show() override;
	void Update() override;
	void Attack() override;
	void SetPbManager(shared_ptr<PbManager> p);
};
