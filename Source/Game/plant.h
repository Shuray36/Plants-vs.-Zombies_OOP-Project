#ifndef PLANT_H
#define PLANT_H

#include "PZGameObject.h"

enum class PlantStatus
{
	Normal,
	Attack,
};

class Plant :public PZGameObject{
protected:
	int state;
	Vector2 coordinate;
	vector<shared_ptr<PZGameObject>> creations;
	Counter attack;
	bool CanAttack(); //override it to let different plant attack 
	void Attack(); // override it to make different attack
	
public:
	Plant() = default;
	~Plant() = default;
	void Init() override;
	void Update() override;
	void SetCoordinate(int x,int y);
	void SetCoordinate(float x,float y);
	int GetCoordinateX();
	int GetCoordinateY();
	
	// will remove
	int cd;
	int hp;
	
};
#endif 