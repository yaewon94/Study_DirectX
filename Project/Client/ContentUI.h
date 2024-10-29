#pragma once
#include "EditorUI.h"

struct TreeNode;

// 에셋 등 게임 관련 리소스 목록을 보여주는 UI
class ContentUI final : public EditorUI
{
private:
	class TreeUI* m_tree;

public:
	static const EDITOR_UI_TYPE Type = EDITOR_UI_TYPE::CONTENT;

public:
	ContentUI();
	~ContentUI();

public:
	virtual void RenderUpdate() final;

public:
	virtual EDITOR_UI_TYPE GetType() final { return Type; }

private:
	void SelectAsset(TreeNode* const node);
};