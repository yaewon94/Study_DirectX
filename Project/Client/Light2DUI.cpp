#include "pch.h"
#include "Light2DUI.h"
#include "InspectorUI.h"
#include "Engine/GameObject.h"
#include "Engine/Light2D.h"
#include "Engine/TransformValues.h"

ImVec2 Light2DUI::s_childSize = ImVec2(0, CHILDSIZE_ROW * 4);


Light2DUI::Light2DUI() 
	: ComponentUI("Light2D")
{
	m_light = ((InspectorUI*)ImguiManager::GetInstance()->FindUI(EDITOR_UI_TYPE::INSPECTOR))->GetTargetObject()->GetComponent<Light2D>();
}

Light2DUI::~Light2DUI()
{
}

//Ptr<Component> Light2DUI::AddComponent()
//{
//	return GetTarget()->AddComponent<Light2D>().ptr_dynamic_cast<Component>();
//}
//
//Ptr<Component> Light2DUI::GetComponent(bool isBaseType)
//{
//	if (isBaseType) return GetTarget()->GetComponent<Light>().ptr_dynamic_cast<Component>();
//	else return GetTarget()->GetComponent<Light2D>().ptr_dynamic_cast<Component>();
//}

void Light2DUI::RenderUpdate()
{
	RenderTitle();

	// ���� Ÿ��
	LIGHT_TYPE type = m_light->GetLightType();
	int iType = (int)(type);
	ImGui::Text("Light Type");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::Combo("##light_type", &iType, LightTypeArr, LightTypeArrSize))
	{
		m_light->SetLightType((LIGHT_TYPE)iType);
	}

	if (type == LIGHT_TYPE::POINT)
	{
		// ����
		float radius = m_light->GetRadius();
		ImGui::Text("Radius");
		ImGui::SameLine(SAMELINE_VALUE);
		if (ImGui::InputFloat("##light_radius", &radius, 0.0f, 0.0f, "%.3f", ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue))
		{
			if (radius < 0.f)
			{
				MessageBoxA(nullptr, "radius���� ������� �մϴ�", "������Ʈ �� ���� ����", MB_OK);
			}
			else
			{
				m_light->SetRadius(radius);
			}
		}

	}
	else if (type == LIGHT_TYPE::SPOT)
	{
		// ����
		int dir = (int)(m_light->GetDirection());
		ImGui::Text("Direction");
		ImGui::SameLine(SAMELINE_VALUE);
		if (ImGui::Combo("##light_dir", &dir, Direction2dNameArr, Direction2dNameArrSize))
		{
			m_light->SetDirection((DIRECTION_2D)dir);
		}

		// ����
		int angle = m_light->GetAngle();
		ImGui::Text("Angle");
		ImGui::SameLine(SAMELINE_VALUE);
		if (ImGui::InputInt("##light_angle", &angle, 0, 0, ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue))
		{
			if (angle < 0 || angle > 90)
			{
				MessageBoxA(nullptr, "angle���� 0~90 ���̿��� �մϴ�", "������Ʈ �� ���� ����", MB_OK);
			}
			else
			{
				m_light->SetAngle(angle);
			}
		}
	}

	// ����
	Vec3 color = m_light->GetColor();
	ImGui::Text("Color");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::ColorEdit3("##light_color", color))
	{
		m_light->SetColor(color);
	}
}