#pragma once
#include "EditorUI.h"

enum class ASSET_TYPE;
enum class COMPONENT_TYPE;
class ComponentUI;
class GameObject;
class Asset;

// �ϳ��� ���ӿ�����Ʈ�� ������ �ִ� ��� ������Ʈ���� ���������� �����ִ� UI
class InspectorUI final : public EditorUI
{
	NO_COPY_ASSIGN(InspectorUI);

private:
	Ptr<GameObject> m_targetObj;
	Ptr<Asset> m_targetAsset;

public:
	static const EDITOR_UI_TYPE Type = EDITOR_UI_TYPE::INSPECTOR;

public:
	InspectorUI();
	~InspectorUI();

public:
	virtual EDITOR_UI_TYPE GetType() final { return Type; }

	void SetTargetObject(Ptr<GameObject> obj);
	Ptr<GameObject> GetTargetObject();

	void SetTargetAsset(Ptr<Asset> asset);
	Ptr<Asset> GetTargetAsset();

public:
	virtual void RenderUpdate() final {}

private:
	void AddChild(COMPONENT_TYPE type); // Component UI
	void AddChild(ASSET_TYPE type);		// Asset UI

//private:
//	template<typename T> requires std::derived_from<T, ComponentUI>
//	void AddChild(Ptr<GameObject> target)
//	{
//		// UI �� �����ϴ� ���
//		if (GetChild<T>() != nullptr)
//		{
//			throw std::logic_error("�̹� ������ �ִ� UI �Դϴ�");
//		}
//		// UI �� �������� �ʴ� ���
//		else
//		{
//			T* componentUI = new T(target);
//
//			// ������Ʈ�� �ִµ� UI�� ���� ���
//			if (componentUI->GetComponent() != nullptr)
//			{
//				// ������ ���� Ÿ���� ������Ʈ�� �̹� ������ �־ �߰��� �� ���� ���
//				if (componentUI->GetComponent(false) == nullptr)
//				{
//					delete componentUI;
//					MessageBox(nullptr, L"�̹� ������ Ÿ���� ���� ������Ʈ�� �����մϴ�", L"������Ʈ �߰� ����", MB_OK);
//				}
//				// �߰� ������ ���
//				else
//				{
//					RegisterChild<T>(componentUI);
//				}
//			}
//			// ������Ʈ�� ���� ��� : UI �߰�, ������Ʈ �߰�
//			else
//			{
//				((ComponentUI*)RegisterChild<T>(componentUI))->AddComponent();
//			}
//		}
//	}
};