#pragma once
#include "ComponentUI.h"

class Component;
class GameObject;

class CameraUI final : public ComponentUI
{
	NO_COPY_ASSIGN(CameraUI);

private:
	static ImVec2 s_childSize;

public:
	CameraUI(Ptr<GameObject> target);
	~CameraUI();

public:
	virtual Ptr<Component> AddComponent() final;
	virtual Ptr<Component> GetComponent(bool isBaseType = true) final;

	virtual ImVec2 GetChildSize() final { return s_childSize; }

public:
	virtual void RenderUpdate() final;
};