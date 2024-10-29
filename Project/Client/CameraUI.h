#pragma once
#include "ComponentUI.h"

class Component;
class Camera;

class CameraUI final : public ComponentUI
{
	NO_COPY_ASSIGN(CameraUI);

private:
	static ImVec2 s_childSize;
	Ptr<Camera> m_camera;

public:
	static const EDITOR_UI_TYPE Type = EDITOR_UI_TYPE::CAMERA;
	
public:
	CameraUI();
	~CameraUI();

public:
	virtual EDITOR_UI_TYPE GetType() final { return Type; }
	/*virtual Ptr<Component> AddComponent() final;
	virtual Ptr<Component> GetComponent(bool isBaseType = true) final;*/
	virtual ImVec2 GetChildSize() final { return s_childSize; }

public:
	virtual void RenderUpdate() final;
};