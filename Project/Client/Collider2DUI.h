#pragma once
#include "ComponentUI.h"

class Component;

class Collider2DUI final : public ComponentUI
{
	NO_COPY_ASSIGN(Collider2DUI);

private:
	static ImVec2 s_childSize;

public:
	Collider2DUI();
	~Collider2DUI();

public:
	virtual ImVec2 GetChildSize() final { return s_childSize; }

public:
	virtual void RenderUpdate() final;

private:
	virtual void AddComponent() final;
	virtual Ptr<Component> GetComponent() final;
};