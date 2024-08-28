#pragma once
#include "Entity.h"
#include "LayerEnums.h"

class Layer;
class GameObject;

// 오브젝트가 존재하는 각각의 scene 개념
// TODO : 추상클래스 전환
class Level : public Entity
{
private:
	array<Ptr<Layer>, (UINT)LAYER_TYPE::COUNT_END> layers;

public:
	Level();
	~Level();

public:
	virtual void Init();
	virtual void Tick();
	virtual void FinalTick();
	virtual void Render() final;

public:
	void AddObject(LAYER_TYPE layer, Ptr<GameObject>& obj);

	// @return : layer의 게임오브젝트 중 가장 먼저 등록된 것
	Ptr<GameObject> GetGameObject(LAYER_TYPE layer);
};