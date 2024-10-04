#pragma once
#include "Entity.h"
#include "LayerEnums.h"

class GameObject;

// 오브젝트의 렌더링 순서 , 렌더링 여부 등을 결정하는 요소
class Layer final : public Entity
{
	NO_COPY_ASSIGN(Layer);

private:
	const LAYER_TYPE m_Type;
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