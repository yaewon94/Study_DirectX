#include "pch.h"
#include "OutlinerUI.h"
#include "TreeUI.h"
#include "Engine/TaskManager.h"
#include "Engine/LevelManager.h"
#include "Engine/GameObject.h"

OutlinerUI::OutlinerUI() 
	: EditorUI("OutlinerUI")
	, m_tree(AddChild<TreeUI>())
{
}

OutlinerUI::~OutlinerUI()
{
	m_tree = nullptr;
}

void OutlinerUI::RenderUpdate()
{
	// TODO : 매번 체크하지말고 레벨 바뀔때만 호출하도록 변경
	if (TaskManager::GetInstance()->IsLevelChanged())
	{
		RenewGameObjects();
	}
}

void OutlinerUI::AddGameObject(TreeNode* const parent, Ptr<GameObject> obj)
{
	TreeNode* node = m_tree->AddItem(obj->GetName(), (DWORD_PTR)obj.Get(), parent);
	vector<Ptr<GameObject>> children;

	for (auto& child : children)
	{
		AddGameObject(node, child);
	}
}

void OutlinerUI::RenewGameObjects()
{
	m_tree->ClearItems();

	TreeNode* root = m_tree->AddItem("GameObject", 0);
	vector<LAYER_TYPE> layers;

	LevelManager::GetInstance()->GetLayers(layers);
	for (auto layer : layers)
	{
		vector<Ptr<GameObject>> objs;

		LevelManager::GetInstance()->GetGameObjects(layer, objs);
		for (auto& obj : objs)
		{
			if (obj->GetParent() == nullptr) AddGameObject(root, obj);
		}
	}
}