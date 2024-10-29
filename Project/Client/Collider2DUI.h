#pragma once
#include "ComponentUI.h"

class Component;
class Collider2D;

class Collider2DUI final : public ComponentUI
{
	NO_COPY_ASSIGN(Collider2DUI);

private:
	static ImVec2 s_childSize;
	Ptr<Collider2D> m_collider;

public:
	static const EDITOR_UI_TYPE Type = EDITOR_UI_TYPE::COLLIDER_2D;

public:
	Collider2DUI();
	~Collider2DUI();

public:
	virtual EDITOR_UI_TYPE GetType() final { return Type; }
	/*virtual Ptr<Component> AddComponent() final;
	virtual Ptr<Component> GetComponent(bool isBaseType = true) final;*/
	virtual ImVec2 GetChildSize() final { return s_childSize; }

public:
	virtual void RenderUpdate() final;
};