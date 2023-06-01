#pragma once
#include <memory>

#include "plant.h"
#include "SunFlower.h"

enum class PlantType {
	SUN_FLOWER=0,
	BEAN_PLANT=1,
	NUT_PLANT=2,
	DOUBLE_BEAN=3
};
class PlantManager
{
	vector<shared_ptr<Plant>> plants;
	shared_ptr<SunManager> sun_manager;
public:
	void setSunmanager(shared_ptr<SunManager> sm)
	{
		sun_manager = sm;
	}
	void Update()
	{
		for(auto& p:plants)
		{
			p->Update();
		}
	}
	void Show()
	{
		for(auto& p:plants)
		{
			p->Show();
		}
	}
    void MakePlant(PlantType type)
    {
    	//todo
    	std::shared_ptr<Plant> p;
		switch (type)
		{
		case PlantType::SUN_FLOWER:
			{
				auto s=make_shared<Sunflower>();
				s->Init();
				s->setSunmanager(sun_manager);
				s->SetAttackCounter(1000);
				p=s;
			}
			break;
		case PlantType::BEAN_PLANT: break;
		case PlantType::NUT_PLANT: break;
		case PlantType::DOUBLE_BEAN: break;
		default: ;
		}
		plants.push_back(p);
    }
};
