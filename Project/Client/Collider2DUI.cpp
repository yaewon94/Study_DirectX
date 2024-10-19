#include "pch.h"
#include "Collider2DUI.h"
#include "Engine/GameObject.h"
#include "Engine/Collider2D.h"

ImVec2 Collider2DUI::s_childSize = ImVec2(0, CHILDSIZE_ROW * 2);

Collider2DUI::Collider2DUI(Ptr<GameObject> target) 
	: ComponentUI("Collider2D", target)
{
}

Collider2DUI::~Collider2DUI()
{
}

void Collider2DUI::RenderUpdate()
{
	static Ptr<Collider2D> collider = GetTarget()->GetComponent<Collider2D>();
	Vec2 offset = collider->GetOffset();
	Vec2 scale = collider->GetScale();

	RenderTitle();

	ImGui::Text("Offset");
	ImGui::SameLine(SAMELINE_VALUE);
	ImGui::InputFloat2("##collider_offset", offset);
	collider->SetOffset(offset);

	ImGui::Text("Scale");
	ImGui::SameLine(SAMELINE_VALUE);
	ImGui::InputFloat2("##collider_scale", scale);
	collider->SetScale(scale);
}

Ptr<Component> Collider2DUI::AddComponent()
{
	return GetTarget()->AddComponent<Collider2D>().ptr_dynamic_cast<Component>();
}

Ptr<Component> Collider2DUI::GetComponent(bool isBaseType)
{
	if(isBaseType) return GetTarget()->GetCollider().ptr_dynamic_cast<Component>();
	else return GetTarget()->GetComponent<Collider2D>().ptr_dynamic_cast<Component>();
}