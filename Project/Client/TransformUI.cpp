#include "pch.h"
#include "TransformUI.h"
#include "Engine/LayerValues.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"

ImVec2 TransformUI::s_childSize = ImVec2(0, CHILDSIZE_ROW * 3);

TransformUI::TransformUI(Ptr<GameObject> target)
	: ComponentUI("Transform", target)
{
}

TransformUI::~TransformUI()
{
}

void TransformUI::RenderUpdate()
{
	static Ptr<Transform> tr = GetTarget()->GetTransform();
	Vec3 localPos = tr->GetLocalPos();
	Vec3 localScale = tr->GetLocalScale();
	Vec3 localRot = tr->GetLocalRotation();

	RenderTitle();

	ImGui::Text("Local Position");	// 상수 문자열 출력
	ImGui::SameLine(SAMELINE_VALUE);			// 위에 출력된 문자열과 같은 라인에 출력 (@param - Text의 글자수가 공백으로 출력됨)
	ImGui::InputFloat3("##tr_pos", localPos);	// 입력칸 (@param : 라벨명, 입력값을 저장할 변수)
	//if (ImGui::DragFloat3("##pos", localPos))
	//{
		tr->SetLocalPos(localPos);
	//}

	ImGui::Text("Local Scale");
	ImGui::SameLine(SAMELINE_VALUE);
	ImGui::InputFloat3("##tr_scale", localScale);
	//if (ImGui::DragFloat3("##scale", localScale))
	//{
		tr->SetLocalScale(localScale);
	//}

	ImGui::Text("Local Rotation");
	ImGui::SameLine(SAMELINE_VALUE);
	localRot = (localRot / XM_PI) * 180.f;
	ImGui::InputFloat3("##tr_rotation", localRot);
	//if (ImGui::DragFloat3("##Rotation", localRot, 0.1f))
	//{
		localRot = (localRot / 180) * XM_PI;
		tr->SetLocalRotation(localRot);
	//}
}

Ptr<Component> TransformUI::AddComponent()
{
	return GetTarget()->AddComponent<Transform>().ptr_dynamic_cast<Component>();
}

Ptr<Component> TransformUI::GetComponent(bool isBaseType)
{
	return GetTarget()->GetTransform().ptr_dynamic_cast<Component>();
}