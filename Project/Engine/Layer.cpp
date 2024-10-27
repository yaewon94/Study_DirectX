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
	// �ߺ� �˻�
	for (auto& obj : m_objs)
	{
		if (obj.Get() == _obj.Get())
		{
			throw std::logic_error("������Ʈ �߰� ���� : �̹� ��ϵ� ������Ʈ �Դϴ�");
		}
	}

	// ������Ʈ ���
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

	throw std::logic_error("������Ʈ ���� ���� : �ش� ���̾ ��ϵ� ������Ʈ�� �ƴմϴ�");
}

Ptr<GameObject> Layer::GetGameObject()
{
	// ���� ù��° ��ü ��ȯ
	if (m_objs.size() > 0)  return m_objs[0];

	throw std::logic_error("������Ʈ ã�� ���� : �ش� ���̾ ��ϵ� ������Ʈ�� �����ϴ�");
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