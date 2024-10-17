#pragma once
#include "EditorUI.h"

class Transform;

// 게임오브젝트의 좌표, 크기, 각도를 설정하는 UI
// TODO : Transform UI 창 닫기를 눌러도 닫히지 않게 해야 함
class TransformUI final : public EditorUI
{
	NO_COPY_ASSIGN(TransformUI);
	
public:
	TransformUI(const Ptr<GameObject>& target);
	~TransformUI();

public:
	virtual void RenderUpdate() final;
};