#pragma once
#include <array>
#include <memory>

#include "Nut.h"
#include "PbManager.h"
#include "plant.h"
#include "SunFlower.h"
#include "chili.h"
#include "zombie.h"

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
	vector<shared_ptr<Zombie>> zombies;

	int seat[9][5] ;
public:
	vector<shared_ptr<Plant>>& GetPlants();
	void SetZombies(vector<shared_ptr<Zombie>> z)
	{
		zombies = z;

	}

	void setSunmanager(shared_ptr<SunManager> sm);
	void setPbmanager(shared_ptr<PbManager> sm);
	void ClearSeat(int get_coordinate_x, int get_coordinate_y);
	void Update();
	void Show();
	void OnMouseMove(Vector2 point);
	int GetSeat(int x,int y){return seat[x][y];}
	void SetSeat(int x,int y, int item){seat[x][y] = item;}
	void OnLButtonDown(Vector2 coordinate);
	void MakePlant(PlantType type, Vector2 position);
	void clear_plant();
	void PlantByShovel(Vector2 coordinate);
	int plant_size();
};
