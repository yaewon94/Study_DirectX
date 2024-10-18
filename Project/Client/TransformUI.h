#pragma once
#include "ComponentUI.h"

class Component;

// 게임오브젝트의 좌표, 크기, 각도를 설정하는 UI
// TODO : Transform UI 창 닫기를 눌러도 닫히지 않게 해야 함
class TransformUI final : public ComponentUI
{
	NO_COPY_ASSIGN(TransformUI);

private:
	static ImVec2 s_childSize;

public:
	TransformUI();
	~TransformUI();

public:
	virtual ImVec2 GetChildSize() final { return s_childSize; }

public:
	virtual void RenderUpdate() final;

private:
	virtual void AddComponent() final;
	virtual Ptr<Component> GetComponent() final;
};