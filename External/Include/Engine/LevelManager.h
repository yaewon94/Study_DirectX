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
	void Render(LAYER_TYPES layers);

public:
	// @return : layer의 게임오브젝트 중 가장 먼저 등록된 것 리턴
	Ptr<GameObject> GetGameObject(LAYER_TYPE layer);
};