#pragma once
#include "EditorUI.h"

class GameObject;

// 하나의 게임오브젝트가 가지고 있는 모든 컴포넌트들을 종합적으로 보여주는 UI
class InspectorUI final : public EditorUI
{
	NO_COPY_ASSIGN(InspectorUI);

private:
	Ptr<GameObject> m_target;

public:
	InspectorUI(const Ptr<GameObject>& target);
	~InspectorUI();

public:
	Ptr<GameObject> GetTarget() const { return m_target; }

public:
	virtual void RenderUpdate() final;
};