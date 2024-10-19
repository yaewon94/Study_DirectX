#pragma once
#include "ComponentUI.h"

class Component;
class GameObject;

class Collider2DUI final : public ComponentUI
{
	NO_COPY_ASSIGN(Collider2DUI);

private:
	static ImVec2 s_childSize;

public:
	Collider2DUI(Ptr<GameObject> target);
	~Collider2DUI();

public:
	virtual Ptr<Component> AddComponent() final;
	virtual Ptr<Component> GetComponent(bool isBaseType = true) final;

	virtual ImVec2 GetChildSize() final { return s_childSize; }

public:
	virtual void RenderUpdate() final;
};