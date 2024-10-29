#include "pch.h"
#include "TransformUI.h"
#include "InspectorUI.h"
#include "Engine/LayerValues.h"
#include "Engine/GameObject.h"
#include "Engine/Transform.h"

ImVec2 TransformUI::s_childSize = ImVec2(0, CHILDSIZE_ROW * 3);

TransformUI::TransformUI()
	: ComponentUI("Transform")
{
	m_tr = ((InspectorUI*)ImguiManager::GetInstance()->FindUI(EDITOR_UI_TYPE::INSPECTOR))->GetTargetObject()->GetTransform();
}

TransformUI::~TransformUI()
{
}

void TransformUI::RenderUpdate()
{
	Vec3 localPos = m_tr->GetLocalPos();
	Vec3 localScale = m_tr->GetLocalScale();
	Vec3 localRot = m_tr->GetLocalRotation();

	RenderTitle();

	ImGui::Text("Local Position");	// 상수 문자열 출력
	ImGui::SameLine(SAMELINE_VALUE);			// 위에 출력된 문자열과 같은 라인에 출력 (@param - Text의 글자수가 공백으로 출력됨)
	ImGui::InputFloat3("##tr_pos", localPos);	// 입력칸 (@param : 라벨명, 입력값을 저장할 변수)
	//if (ImGui::DragFloat3("##pos", localPos))
	//{
		m_tr->SetLocalPos(localPos);
	//}

	ImGui::Text("Local Scale");
	ImGui::SameLine(SAMELINE_VALUE);
	ImGui::InputFloat3("##tr_scale", localScale);
	//if (ImGui::DragFloat3("##scale", localScale))
	//{
		m_tr->SetLocalScale(localScale);
	//}

	ImGui::Text("Local Rotation");
	ImGui::SameLine(SAMELINE_VALUE);
	localRot = (localRot / XM_PI) * 180.f;
	ImGui::InputFloat3("##tr_rotation", localRot);
	//if (ImGui::DragFloat3("##Rotation", localRot, 0.1f))
	//{
		localRot = (localRot / 180) * XM_PI;
		m_tr->SetLocalRotation(localRot);
	//}
}

//Ptr<Component> TransformUI::AddComponent()
//{
//	return GetTarget()->AddComponent<Transform>().ptr_dynamic_cast<Component>();
//}
//
//Ptr<Component> TransformUI::GetComponent(bool isBaseType)
//{
//	return GetTarget()->GetTransform().ptr_dynamic_cast<Component>();
//}