#pragma once
#include "ComponentUI.h"

class Component;
class GameObject;
class Transform;

// 게임오브젝트의 좌표, 크기, 각도를 설정하는 UI
// TODO : Transform UI 창 닫기를 눌러도 닫히지 않게 해야 함
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