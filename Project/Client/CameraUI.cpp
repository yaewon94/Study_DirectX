#include "pch.h"
#include "CameraUI.h"
#include "InspectorUI.h"
#include "Engine/GameObject.h"
#include "Engine/Camera.h"

ImVec2 CameraUI::s_childSize = ImVec2(0, CHILDSIZE_ROW * 8);


CameraUI::CameraUI() 
	: ComponentUI("Camera")
{
	m_camera = ((InspectorUI*)ImguiManager::GetInstance()->FindUI(EDITOR_UI_TYPE::INSPECTOR))->GetTargetObject()->GetComponent<Camera>();
}

CameraUI::~CameraUI()
{
}

//Ptr<Component> CameraUI::AddComponent()
//{
//	return GetTarget()->AddComponent<Camera>().ptr_dynamic_cast<Component>();
//}
//
//Ptr<Component> CameraUI::GetComponent(bool isBaseType)
//{
//	return GetTarget()->GetComponent<Camera>().ptr_dynamic_cast<Component>();
//}

void CameraUI::RenderUpdate()
{
	RenderTitle();

	// ī�޶� Ÿ�� (������ �켱����)
	int camType = (int)(m_camera->GetCameraType());
	ImGui::Text("Camera Type\n(Render priority)");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::Combo("##cam_type", &camType, CameraTypeArr, CameraTypeArrSize))
	{
		m_camera->SetCameraType((CAMERA_TYPE)camType);
	}

	// ���� Ÿ��
	int projType = (int)(m_camera->GetProjectionType());
	ImGui::Text("Projection");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::Combo("##cam_proj", &projType, ProjTypeArr, ProjTypeArrSize))
	{
		m_camera->SetProjectionType((PROJECTION_TYPE)projType);
	}

	// ī�޶� ���� Z�� ������ ���� (near ~ far)
	float Near = m_camera->GetNear();
	float Far = m_camera->GetFar();
	ImGui::Text("Near");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::InputFloat("##cam_near", &Near, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue))
	{
		if (Near >= Far)
		{
			Near = m_camera->GetNear();
			MessageBoxA(nullptr, "near���� far������ �۾ƾ� �մϴ�", "������Ʈ �� ���� ����", MB_OK);
		}
		else
		{
			m_camera->SetNear(Near);
		}
	}

	ImGui::Text("Far");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::InputFloat("##cam_far", &Far, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue))
	{
		if (Far <= Near)
		{
			Far = m_camera->GetFar();
			MessageBoxA(nullptr, "far���� near������ Ŀ�� �մϴ�", "������Ʈ �� ���� ����", MB_OK);
		}
		else
		{
			m_camera->SetFar(Far);
		}
	}

	// ī�޶� ���� X,Y�� ������ ����
	float width = m_camera->GetViewWidth();
	ImGui::Text("View Width");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::InputFloat("##cam_width", &width, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue))
	{
		if (width <= 0.f)
		{
			width = m_camera->GetViewWidth();
			MessageBoxA(nullptr, "view width ���� ������� �մϴ�", "������Ʈ �� ���� ����", MB_OK);
		}
		else
		{
			m_camera->SetViewWidth(width);
		}
	}

	float height = m_camera->GetViewHeight();
	ImGui::Text("View Height");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::InputFloat("##cam_height", &height, 0.0f, 0.0f, "%.f", ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue))
	{
		if (height <= 0.f)
		{
			height = m_camera->GetViewHeight();
			MessageBoxA(nullptr, "view height ���� ������� �մϴ�", "������Ʈ �� ���� ����", MB_OK);
		}
		else
		{
			m_camera->SetViewHeight(height);
		}
	}

	// �������� (3D ������) ���
	if (projType == (int)PROJECTION_TYPE::PERSPECTIVE)
	{
		// �þ߰�
		ImGui::Text("Field of view");
		ImGui::SameLine(SAMELINE_VALUE);
		int fov = m_camera->GetFieldOfView() * 180.f / XM_PI;
		if (ImGui::InputInt("##cam_fov", &fov, 0))
		{
			m_camera->SetFieldOfView(fov);
		}
	}
	// �������� (2D ������) ���
	else
	{
		// ���� ����
		ImGui::Text("View Scale");
		ImGui::SameLine(SAMELINE_VALUE);
		float scale = m_camera->GetScale();
		if (ImGui::InputFloat("##cam_scale", &scale, 0.0f, 0.0f, "%.3f", ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue))
		{
			if (scale <= 0.f)
			{
				scale = m_camera->GetScale();
				MessageBoxA(nullptr, "view scale ���� ������� �մϴ�", "������Ʈ �� ���� ����", MB_OK);
			}
			else
			{
				m_camera->SetScale(scale);
			}
		}
	}

	// �������� ���̾� ����
	LAYER_TYPES layers = m_camera->GetRenderLayers();
	ImGui::Text("Layers");
	ImGui::BeginTable("##cam_layers_table", 4);
	for (const auto& tuple : LayerTypeArr)
	{
		LAYER_TYPE layer = std::get<0>(tuple);
		const char* layerName = std::get<1>(tuple);
		bool flag = layer & layers;

		ImGui::TableNextColumn();
		if (ImGui::Checkbox(layerName, &flag))
		{
			m_camera->SetLayerOnOff(layer);
		}
	}
	ImGui::EndTable();
}