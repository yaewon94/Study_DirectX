#pragma once
#include "Entity.h"
#include "LayerValues.h"

class Layer;
class GameObject;

// 레벨 상태
enum class LEVEL_STATE
{
	NONE = -1, // 레벨클래스 초기화 용도
	STOP, PAUSE, PLAY
};

// 오브젝트가 존재하는 각각의 scene 개념
// TODO : 추상클래스 전환
class Level : public Entity
{
	friend class LevelManager;

private:
	map<LAYER_TYPE, Ptr<Layer>> m_layerMap;
	LEVEL_STATE m_state;

public:
	Level();
	~Level();

public:
	LEVEL_STATE GetState() { return m_state; }

private:
	virtual void Init();
	virtual void Tick();
	virtual void FinalTick();

private:
	Ptr<GameObject> AddObject(const Ptr<GameObject>& obj);
	void DeleteObject(const Ptr<GameObject>& obj);

	// @return : layer의 게임오브젝트 중 가장 먼저 등록된 것 리턴
	Ptr<GameObject> GetGameObject(LAYER_TYPE layer);

	void ChangeState(LEVEL_STATE state) { m_state = state; }
};