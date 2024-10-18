#include "pch.h"
#include "Collider2DUI.h"
#include "InspectorUI.h"
#include "Engine/GameObject.h"
#include "Engine/Collider2D.h"

ImVec2 Collider2DUI::s_childSize = ImVec2(0, CHILDSIZE_ROW * 2);

Collider2DUI::Collider2DUI() 
	: ComponentUI("Collider2D")
{
}

Collider2DUI::~Collider2DUI()
{
}

void Collider2DUI::RenderUpdate()
{
	static Ptr<Collider2D> collider = ((InspectorUI*)GetParent())->GetTarget()->GetComponent<Collider2D>();
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

void Collider2DUI::AddComponent()
{
	((InspectorUI*)GetParent())->GetTarget()->AddComponent<Collider2D>();
}

Ptr<Component> Collider2DUI::GetComponent()
{
	return ((InspectorUI*)GetParent())->GetTarget()->GetCollider().ptr_dynamic_cast<Component>();
}