#pragma once
#include "ComponentUI.h"

class Component;
class GameObject;
class Transform;

// ���ӿ�����Ʈ�� ��ǥ, ũ��, ������ �����ϴ� UI
// TODO : Transform UI â �ݱ⸦ ������ ������ �ʰ� �ؾ� ��
class TransformUI final : public ComponentUI
{
	NO_COPY_ASSIGN(TransformUI);

private:
	static ImVec2 s_childSize;
	Ptr<Transform> m_tr;

public:
	TransformUI(Ptr<GameObject> target);
	~TransformUI();

public:
	virtual EDITOR_UI_TYPE GetType() final { return EDITOR_UI_TYPE::TRANSFORM; }

	virtual Ptr<Component> AddComponent() final;
	virtual Ptr<Component> GetComponent(bool isBaseType = true) final;

	virtual ImVec2 GetChildSize() final { return s_childSize; }

public:
	virtual void RenderUpdate() final;
};