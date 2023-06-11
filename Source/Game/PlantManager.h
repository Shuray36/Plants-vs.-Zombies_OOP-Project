#pragma once
#include <memory>

#include "Nut.h"
#include "PbManager.h"
#include "plant.h"
#include "SunFlower.h"
#include "chili.h"

enum class PlantType {
	SUN_FLOWER=0,
	BEAN_PLANT=1,
	NUT_PLANT=2,
	DOUBLE_BEAN=3,
	CHILI_PLANT=4
};
class PlantManager
{
	vector<shared_ptr<Plant>> plants;
	shared_ptr<SunManager> sun_manager;
	shared_ptr<PbManager> pb_manager;
public:
	vector<shared_ptr<Plant>>& GetPlants()
	{
		return plants;
	}
	void setSunmanager(shared_ptr<SunManager> sm);
	void setPbmanager(shared_ptr<PbManager> sm);

	void Update();

	void Show();

	void OnMouseMove(Vector2 point);

	void OnLButtonDown(Vector2 coordinate);

	void MakePlant(PlantType type, Vector2 position);

	void clear_plant();
	int plant_size();
};
