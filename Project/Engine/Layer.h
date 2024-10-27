#pragma once
#include "Entity.h"
#include "LayerValues.h"

class GameObject;

// ������Ʈ�� ������ ���� , ������ ���� ���� �����ϴ� ���
class Layer final : public Entity
{
	NO_COPY_ASSIGN(Layer);

private:
	const LAYER_TYPE m_Type;

	// TODO : �ֻ��� �θ� ������Ʈ�� ����ϱ�
	vector<Ptr<GameObject>> m_objs;

public:
	Layer(const LAYER_TYPE Type);
	~Layer();

public:
	Ptr<GameObject> AddObject(const Ptr<GameObject>& _obj);
	void DeleteObject(const Ptr<GameObject>& obj);
	Ptr<GameObject> GetGameObject();
	bool IsEmpty() { return m_objs.empty(); }

public:
	void Init();
	void Tick();
	void FinalTick();
};