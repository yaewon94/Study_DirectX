#pragma once
#include "Entity.h"
#include "LayerValues.h"

class Layer;
class GameObject;

// ���� ����
enum class LEVEL_STATE
{
	NONE = -1, // ����Ŭ���� �ʱ�ȭ �뵵
	STOP, PAUSE, PLAY
};

// ������Ʈ�� �����ϴ� ������ scene ����
// TODO : �߻�Ŭ���� ��ȯ
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

	// @return : layer�� ���ӿ�����Ʈ �� ���� ���� ��ϵ� �� ����
	Ptr<GameObject> GetGameObject(LAYER_TYPE layer);

	void ChangeState(LEVEL_STATE state) { m_state = state; }
};