#pragma once
#include "Singleton.h"

class Level;

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
};