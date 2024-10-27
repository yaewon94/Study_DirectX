#include "pch.h"
#include "Layer.h"
#include "GameObject.h"

Layer::Layer(const LAYER_TYPE Type) : m_Type(Type)
{
}

Layer::~Layer()
{
}

Ptr<GameObject> Layer::AddObject(const Ptr<GameObject>& _obj)
{
	// 중복 검사
	for (auto& obj : m_objs)
	{
		if (obj.Get() == _obj.Get())
		{
			throw std::logic_error("오브젝트 추가 실패 : 이미 등록된 오브젝트 입니다");
		}
	}

	// 오브젝트 등록
	m_objs.push_back(_obj);

	return _obj;
}

void Layer::DeleteObject(const Ptr<GameObject>& obj)
{
	for (auto iter = m_objs.begin(); iter != m_objs.end(); ++iter)
	{
		if (iter->Get() == obj.Get())
		{
			m_objs.erase(iter);
			return;
		}
	}

	throw std::logic_error("오브젝트 삭제 실패 : 해당 레이어에 등록된 오브젝트가 아닙니다");
}

Ptr<GameObject> Layer::GetGameObject()
{
	// 가장 첫번째 객체 반환
	if (m_objs.size() > 0)  return m_objs[0];

	throw std::logic_error("오브젝트 찾기 실패 : 해당 레이어에 등록된 오브젝트가 없습니다");
}

void Layer::GetGameObjects(vector<Ptr<GameObject>>& objs)
{
	for (auto& obj : m_objs)
	{
		objs.push_back(obj);
	}
}

void Layer::Init()
{
	for (auto& obj : m_objs)
	{
		obj->Init();
	}
}

void Layer::Tick()
{
	for (auto& obj : m_objs)
	{
		obj->Tick();
	}
}

void Layer::FinalTick()
{
	for (auto& obj : m_objs)
	{
		obj->FinalTick();
	}
}