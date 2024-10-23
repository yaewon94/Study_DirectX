#include "pch.h"
#include "Collider2DUI.h"
#include "Engine/GameObject.h"
#include "Engine/Collider2D.h"

ImVec2 Collider2DUI::s_childSize = ImVec2(0, CHILDSIZE_ROW * 2);

Collider2DUI::Collider2DUI(Ptr<GameObject> target) 
	: ComponentUI("Collider2D", target)
	, m_collider(target->GetComponent<Collider2D>())
{
}

Collider2DUI::~Collider2DUI()
{
}

void Collider2DUI::RenderUpdate()
{
	Vec2 offset = m_collider->GetOffset();
	Vec2 scale = m_collider->GetScale();

	RenderTitle();

	ImGui::Text("Offset");
	ImGui::SameLine(SAMELINE_VALUE);
	ImGui::InputFloat2("##collider_offset", offset);
	m_collider->SetOffset(offset);

	ImGui::Text("Scale");
	ImGui::SameLine(SAMELINE_VALUE);
	ImGui::InputFloat2("##collider_scale", scale);
	m_collider->SetScale(scale);
}

Ptr<Component> Collider2DUI::AddComponent()
{
	return GetTarget()->AddComponent<Collider2D>().ptr_dynamic_cast<Component>();
}

Ptr<Component> Collider2DUI::GetComponent(bool isBaseType)
{
	if(isBaseType) return GetTarget()->GetComponent<Collider>().ptr_dynamic_cast<Component>();
	else return GetTarget()->GetComponent<Collider2D>().ptr_dynamic_cast<Component>();
}