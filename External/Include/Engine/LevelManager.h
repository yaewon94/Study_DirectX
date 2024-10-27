#pragma once
#include "Singleton.h"
#include "Level.h"

class GameObject;

// 레벨 관리 클래스
class LevelManager final : public Singleton<LevelManager>
{
	SINGLETON(LevelManager);

private:
	Ptr<Level> curLevel = nullptr;

public:
	void Init();
	void Tick();

public:
	Ptr<GameObject> AddObject(const Ptr<GameObject>& obj);
	void DeleteObject(const Ptr<GameObject>& obj);
	// @return : layer의 게임오브젝트 중 가장 먼저 등록된 것 리턴
	Ptr<GameObject> GetGameObject(LAYER_TYPE layer);
	void GetGameObjects(LAYER_TYPE layer, vector<Ptr<GameObject>>& objs);
	void GetLayers(vector<LAYER_TYPE>& layers) { curLevel->GetLayers(layers); }

	LEVEL_STATE GetState() { return curLevel->GetState(); }
	void ChangeState(LEVEL_STATE state);
};