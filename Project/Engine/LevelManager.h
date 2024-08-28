#pragma once
#include "Singleton.h"
#include "LayerEnums.h"

class Level;
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
	void Render();

public:
	// @return : 현재 레벨 layer의 게임오브젝트 중 가장 먼저 등록된 것
	Ptr<GameObject> GetGameObject(LAYER_TYPE layer);
};