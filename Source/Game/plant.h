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
	vector<string> filePath;
	int fileColor;
	int _cycleTime;
	Vector2 coordinate;
	Counter attack;
	bool _isPlace;
	virtual bool CanAttack(); //override it to let different plant attack 
	virtual void Attack(); // override it to make different attack
public:
	Plant() = default;
	~Plant() = default;
	void Init() override;
	void Update() override;
	void SetCoordinate(int x,int y);
	void SetCoordinate(float x,float y);
	void SetCoordinate(Vector2 v);
	void SetImange(vector<string> path,int color, int cycleTime);
	void Show() override;
	int GetCoordinateX();
	int GetCoordinateY();
	bool GetIsPlace();
	void SetIsPlace(bool status);
	void SetAttackCounter(float cycle);
	float GetAttackCycle();
	float GetAttackCounter();;

	// will remove
	int cd;
	int hp;
	
};
#endif 