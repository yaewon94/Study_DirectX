#pragma once
#include "Singleton.h"
#include "Level.h"

class GameObject;

// ���� ���� Ŭ����
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

	// @return : layer�� ���ӿ�����Ʈ �� ���� ���� ��ϵ� �� ����
	Ptr<GameObject> GetGameObject(LAYER_TYPE layer);

	void ChangeState(LEVEL_STATE state);
};