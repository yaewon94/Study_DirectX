#pragma once
#include "ComponentUI.h"

class Component;
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
	static const EDITOR_UI_TYPE Type = EDITOR_UI_TYPE::TRANSFORM;

public:
	TransformUI();
	~TransformUI();

public:
	virtual EDITOR_UI_TYPE GetType() final { return Type; }
	/*virtual Ptr<Component> AddComponent() final;
	virtual Ptr<Component> GetComponent(bool isBaseType = true) final;*/
	virtual ImVec2 GetChildSize() final { return s_childSize; }

public:
	virtual void RenderUpdate() final;
};