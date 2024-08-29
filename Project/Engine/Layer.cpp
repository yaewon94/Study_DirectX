#include "pch.h"
#include "Layer.h"
#include "GameObject.h"

Layer::Layer(const LAYER_TYPE Type) : Type(Type)
{
}

Layer::~Layer()
{
}

void Layer::AddObject(Ptr<GameObject>& _obj)
{
	// 같은 레이어인지 체크
	if (_obj->GetLayer() != LAYER_TYPE::NONE && _obj->GetLayer() != Type)
	{
		MessageBoxA(nullptr, "다른 타입의 레이어에 추가할 수 없습니다", "오브젝트 추가 실패", MB_OK);
		return;
	}

	// 중복 검사
	for (auto& obj : objs)
	{
		if (_obj.GetAddressOf() == obj.GetAddressOf())
		{
			MessageBoxA(nullptr, "이미 등록된 오브젝트 입니다", "오브젝트 추가 실패", MB_OK);
			return;
		}
	}

	_obj->SetLayer(Type);
	objs.push_back(_obj);
}

void Layer::Init()
{
	for (auto& obj : objs)
	{
		obj->Init();
	}
}

void Layer::Tick()
{
	for (auto& obj : objs)
	{
		obj->Tick();
	}
}

void Layer::FinalTick()
{
	for (auto& obj : objs)
	{
		obj->FinalTick();
	}
}

void Layer::Render()
{
	for (auto& obj : objs)
	{
		obj->Render();
	}
}