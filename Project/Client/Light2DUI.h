#pragma once
#include "ComponentUI.h"

class Component;
class Light2D;

class Light2DUI final : public ComponentUI
{
	NO_COPY_ASSIGN(Light2DUI);

private:
	static ImVec2 s_childSize;
	Ptr<Light2D> m_light;

public:
	static const EDITOR_UI_TYPE Type = EDITOR_UI_TYPE::LIGHT_2D;

public:
	Light2DUI();
	~Light2DUI();

public:
	virtual EDITOR_UI_TYPE GetType() final { return Type; }
	/*virtual Ptr<Component> AddComponent() final;
	virtual Ptr<Component> GetComponent(bool isBaseType = true) final;*/
	virtual ImVec2 GetChildSize() final { return s_childSize; }

public:
	virtual void RenderUpdate() final;

};