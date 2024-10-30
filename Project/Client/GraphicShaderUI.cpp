#include "pch.h"
#include "GraphicShaderUI.h"
#include "InspectorUI.h"
#include "Engine/GraphicShader.h"

GraphicShaderUI::GraphicShaderUI() : AssetUI("Graphic Shader")
{
	m_shader = ((InspectorUI*)ImguiManager::GetInstance()->FindUI(EDITOR_UI_TYPE::INSPECTOR))->GetTargetAsset().ptr_dynamic_cast<GraphicShader>();
}

GraphicShaderUI::~GraphicShaderUI()
{
}

void GraphicShaderUI::RenderUpdate()
{
	RenderTitle();

	// TODO : 에디터모드에서 에셋 새로 만들기 기능 추가 시, 주석해놓은 것들 사용

	// topology
	int topology = m_shader->GetTopology();
	ImGui::Text("Topology");
	ImGui::SameLine(SAMELINE_VALUE);
	ImGui::TextDisabled(TopologyNameArr[topology]);
	/*if (ImGui::Combo("##gs_topology", &topology, TopologyNameArr, TopologyArrSize))
	{
		m_shader->SetTopology((D3D11_PRIMITIVE_TOPOLOGY)topology);
	}*/

	// shader domain
	int domain = (int)m_shader->GetDomain();
	ImGui::Text("Shader domain");
	ImGui::SameLine(SAMELINE_VALUE);
	ImGui::TextDisabled(ShaderDomainArr[domain]);
	/*if (ImGui::Combo("##gs_domain", &domain, ShaderDomainArr, ShaderDomainArrSize))
	{
		m_shader->SetDomain((SHADER_DOMAIN)domain);
	}*/

	// rasterize type
	int rsType = (int)m_shader->GetRasterizeType();
	ImGui::Text("Rasterize");
	ImGui::SameLine(SAMELINE_VALUE);
	ImGui::TextDisabled(RsArr[rsType]);
	/*if (ImGui::Combo("##gs_rs", &rsType, RsArr, RsArrSize))
	{
		m_shader->SetRasterizerType((RASTERIZE_TYPE)rsType);
	}*/

	// blend type
	int bsType = (int)m_shader->GetBlendType();
	ImGui::Text("Blend");
	ImGui::SameLine(SAMELINE_VALUE);
	ImGui::TextDisabled(BsArr[bsType]);
	/*if (ImGui::Combo("##gs_bs", &bsType, BsArr, BsArrSize))
	{
		m_shader->SetBlendType((BLEND_TYPE)bsType);
	}*/

	// depth stencil type
	int dsType = (int)m_shader->GetDepthStencilType();
	ImGui::Text("Depth Stencil");
	ImGui::SameLine(SAMELINE_VALUE);
	ImGui::TextDisabled(DsArr[dsType]);
	/*if (ImGui::Combo("##gs_ds", &dsType, DsArr, DsArrSize))
	{
		m_shader->SetDepthStencilType((DEPTH_STENCIL_TYPE)dsType);
	}*/
}