#pragma once
#include "EditorUI.h"

class ComponentUI;
class GameObject;

// �ϳ��� ���ӿ�����Ʈ�� ������ �ִ� ��� ������Ʈ���� ���������� �����ִ� UI
class InspectorUI final : public EditorUI
{
	NO_COPY_ASSIGN(InspectorUI);

public:
	InspectorUI();
	~InspectorUI();

public:
	virtual EDITOR_UI_TYPE GetType() final { return EDITOR_UI_TYPE::INSPECTOR; }

	void SetTargetObject(Ptr<GameObject> obj);

	template<typename T> requires std::derived_from<T, ComponentUI>
	void AddChild(Ptr<GameObject> target)
	{
		// UI �� �����ϴ� ���
		if (GetChild<T>() != nullptr)
		{
			throw std::logic_error("�̹� ������ �ִ� UI �Դϴ�");
		}
		// UI �� �������� �ʴ� ���
		else
		{
			T* componentUI = new T(target);

			// ������Ʈ�� �ִµ� UI�� ���� ���
			if (componentUI->GetComponent() != nullptr)
			{
				// ������ ���� Ÿ���� ������Ʈ�� �̹� ������ �־ �߰��� �� ���� ���
				if (componentUI->GetComponent(false) == nullptr)
				{
					delete componentUI;
					MessageBox(nullptr, L"�̹� ������ Ÿ���� ���� ������Ʈ�� �����մϴ�", L"������Ʈ �߰� ����", MB_OK);
				}
				// �߰� ������ ���
				else
				{
					RegisterChild<T>(componentUI);
				}
			}
			// ������Ʈ�� ���� ��� : UI �߰�, ������Ʈ �߰�
			else
			{
				((ComponentUI*)RegisterChild<T>(componentUI))->AddComponent();
			}
		}
	}

public:
	virtual void RenderUpdate() final {}
};