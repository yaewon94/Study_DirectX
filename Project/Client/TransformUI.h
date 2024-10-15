#pragma once
#include "EditorUI.h"

// 게임오브젝트의 좌표, 크기, 각도를 설정하는 UI
class TransformUI final : public EditorUI
{
	NO_COPY_ASSIGN(TransformUI);

public:
	TransformUI();
	~TransformUI();

public:
	virtual void RenderUpdate() final;
};