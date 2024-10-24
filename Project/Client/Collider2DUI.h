#pragma once
#include "ComponentUI.h"

class Component;
class GameObject;
class Collider2D;

class Collider2DUI final : public ComponentUI
{
	NO_COPY_ASSIGN(Collider2DUI);

private:
	static ImVec2 s_childSize;
	Ptr<Collider2D> m_collider;

public:
	Collider2DUI(Ptr<GameObject> target);
	~Collider2DUI();

public:
	virtual EDITOR_UI_TYPE GetType() final { return EDITOR_UI_TYPE::COLLIDER_2D; }

	virtual Ptr<Component> AddComponent() final;
	virtual Ptr<Component> GetComponent(bool isBaseType = true) final;

	virtual ImVec2 GetChildSize() final { return s_childSize; }

public:
	virtual void RenderUpdate() final;
};