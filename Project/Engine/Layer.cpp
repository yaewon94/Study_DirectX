#include "pch.h"
#include "Layer.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "Material.h"
#include "GraphicShader.h"
#include "MeshRender.h"

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
	for (auto& objVec : renderObjs)
	{
		for (auto& obj : objVec.second)
		{
			if (_obj.GetAddressOf() == obj.GetAddressOf())
			{
				MessageBoxA(nullptr, "이미 등록된 오브젝트 입니다", "오브젝트 추가 실패", MB_OK);
				return;
			}
		}
	}

	// 렌더링 컴포넌트 확인
	Ptr<RenderComponent> renderComponent = _obj->GetComponent<RenderComponent>();

	if (renderComponent != nullptr)
	{
		// 셰이더 도메인 확인
		SHADER_DOMAIN domain = renderComponent->GetMaterial()->GetShader()->GetDomain();
		const auto iter = renderObjs.find(domain);
		if (iter == renderObjs.end())
		{
			vector<Ptr<GameObject>> vec;
			vec.push_back(_obj);
			renderObjs.insert(make_pair(domain, vec));
		}
		else
		{
			iter->second.push_back(_obj);
		}
	}
	else
	{
		notRenderObjs.push_back(_obj);
	}

	_obj->SetLayer(Type);
}

Ptr<GameObject> Layer::GetGameObject()
{
	for (auto& objVec : renderObjs)
	{
		for (auto& obj : objVec.second)
		{
			return obj;
		}
	}

	for (auto& obj : notRenderObjs)
	{
		return obj;
	}

	return nullptr;
}

void Layer::Init()
{
	for (auto& objVec : renderObjs)
	{
		for (auto& obj : objVec.second)
		{
			obj->Init();
		}
	}

	for (auto& obj : notRenderObjs)
	{
		obj->Init();
	}
}

void Layer::Tick()
{
	for (auto& objVec : renderObjs)
	{
		for (auto& obj : objVec.second)
		{
			obj->Tick();
		}
	}

	for (auto& obj : notRenderObjs)
	{
		obj->Tick();
	}

}

void Layer::FinalTick()
{
	for (auto& objVec : renderObjs)
	{
		for (auto& obj : objVec.second)
		{
			obj->FinalTick();
		}
	}

	for (auto& obj : notRenderObjs)
	{
		obj->FinalTick();
	}
}

void Layer::Render()
{
	for (auto& objVec : renderObjs)
	{
		for (auto& obj : objVec.second)
		{
			obj->Render();
		}
	}
}