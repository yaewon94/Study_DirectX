#pragma once
#include "Entity.h"
#include "LayerEnums.h"

class GameObject;

// 오브젝트의 렌더링 순서 , 렌더링 여부 등을 결정하는 요소
class Layer final : public Entity
{
private:
	vector<Ptr<GameObject>> objs;

public:
	Layer();
	~Layer();

public:
	void AddObject(Ptr<GameObject>& _obj);
	Ptr<GameObject> GetGameObject() { return objs.at(0); }

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();
};