#pragma once
#include "Entity.h"
#include "LayerEnums.h"

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
	virtual void Render(LAYER_TYPES layers) final;

private:
	void AddObject(LAYER_TYPE layer, Ptr<GameObject>& obj);

	// @return : layer의 게임오브젝트 중 가장 먼저 등록된 것 리턴
	Ptr<GameObject> GetGameObject(LAYER_TYPE layer);

private:
	// 오브젝트 추가 시, 해당 레이어가 없으면 자동 추가
	void AddLayer(LAYER_TYPE layer);
};