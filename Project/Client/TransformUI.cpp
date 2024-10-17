#include "pch.h"
#include "TransformUI.h"
#include "Engine/LayerEnums.h"
#include "Engine/Transform.h"

TransformUI::TransformUI(const Ptr<GameObject>& target) 
	: EditorUI(target)
{
}

TransformUI::~TransformUI()
{
}

void TransformUI::RenderUpdate()
{
	Ptr<Transform> tr = GetTarget()->GetTransform();
	Vec3 localPos = tr->GetLocalPos();
	Vec3 localScale = tr->GetLocalScale();
	Vec3 localRot = tr->GetLocalRotation();

	ImGui::Text("Local Position");	// 상수 문자열 출력
	ImGui::SameLine(130);			// 위에 출력된 문자열과 같은 라인에 출력 (@param - Text의 글자수가 공백으로 출력됨)
	ImGui::InputFloat3("##pos", localPos);	// 입력칸 (@param : 라벨명, 입력값을 저장할 변수)
	//if (ImGui::DragFloat3("##pos", localPos))
	//{
		tr->SetLocalPos(localPos);
	//}

	ImGui::Text("Local Scale");
	ImGui::SameLine(130);
	ImGui::InputFloat3("##scale", localScale);
	//if (ImGui::DragFloat3("##scale", localScale))
	//{
		tr->SetLocalScale(localScale);
	//}

	ImGui::Text("Local Rotation");
	ImGui::SameLine(130);
	localRot = (localRot / XM_PI) * 180.f;
	ImGui::InputFloat3("##Rotation", localRot);
	//if (ImGui::DragFloat3("##Rotation", localRot, 0.1f))
	//{
		localRot = (localRot / 180) * XM_PI;
		tr->SetLocalRotation(localRot);
	//}
}