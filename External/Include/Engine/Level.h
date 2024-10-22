#pragma once
#include "Entity.h"
#include "LayerValues.h"

class Layer;
class GameObject;

// 오브젝트가 존재하는 각각의 scene 개념
// TODO : 추상클래스 전환
class Level : public Entity
{
	friend class LevelManager;

private:
	map<LAYER_TYPE, Ptr<Layer>> m_layerMap;

public:
	Level();
	~Level();

private:
	virtual void Init();
	virtual void Tick();
	virtual void FinalTick();

private:
	Ptr<GameObject> AddObject(const Ptr<GameObject>& obj);
	void DeleteObject(const Ptr<GameObject>& obj);

	// @return : layer의 게임오브젝트 중 가장 먼저 등록된 것 리턴
	Ptr<GameObject> GetGameObject(LAYER_TYPE layer);
};