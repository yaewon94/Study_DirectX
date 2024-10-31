#include "pch.h"
#include "ContentUI.h"
#include "TreeUI.h"
#include "InspectorUI.h"
#include "Engine/AssetManager.h"

ContentUI::ContentUI() 
	: EditorUI("ContentUI")
	, m_tree(AddChild<TreeUI>())
{
	m_tree->SetOnSelectCallback(this, (EUI_CALLBACK)&ContentUI::SelectAsset);

	// 모든 에셋 가져오기
	TreeNode* root = m_tree->AddItem("Asset", 0);

	for (UINT i=0; i<(UINT)ASSET_TYPE::COUNT_END; ++i)
	{
		TreeNode* node = m_tree->AddItem(AssetNameArr[i], 0, root);

		const map<string, Ptr<Asset>> map = AssetManager::GetInstance()->GetAssets((ASSET_TYPE)i);
		for (auto& pair : map)
		{
			m_tree->AddItem(pair.first, (DWORD_PTR)pair.second.Get(), node);
		}
	}
}

ContentUI::~ContentUI()
{
}

void ContentUI::RenderUpdate()
{
}

void ContentUI::SelectAsset(TreeNode* const node)
{
	if (node->GetData() == 0) return;
	Asset* asset = (Asset*)node->GetData();
	InspectorUI* inspector = (InspectorUI*)ImguiManager::GetInstance()->FindUI(EDITOR_UI_TYPE::INSPECTOR);
	inspector->SetTargetAsset(Ptr<Asset>(asset));
}