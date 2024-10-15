#include "pch.h"
#include "TransformUI.h"
#include "Engine/TransformValues.h"

TransformUI::TransformUI()
{
}

TransformUI::~TransformUI()
{
}

void TransformUI::RenderUpdate()
{
	ImGui::Text("Local Position");	// 상수 문자열 출력
	ImGui::SameLine(130);			// 위에 출력된 문자열과 같은 라인에 출력 (@param - Text의 글자수가 공백으로 출력됨)
	float arrPos[3] = {};
	ImGui::InputFloat3("##pos", arrPos);	// 입력칸 (@param : 라벨명, 입력값을 저장할 변수)

	ImGui::Text("Local Scale");
	ImGui::SameLine(130);
	float arrScale[3] = { DEFAULT_SCALE_NO_PARENT.x, DEFAULT_SCALE_NO_PARENT.y, DEFAULT_SCALE_NO_PARENT.z };
	ImGui::InputFloat3("##scale", arrScale);

	ImGui::Text("Local Rotation");
	ImGui::SameLine(130);
	float arrRot[3] = {};
	ImGui::InputFloat3("##Rotation", arrRot);
}