#pragma once
#include "AssetUI.h"

class GraphicShader;

class GraphicShaderUI final : public AssetUI
{
	NO_COPY_ASSIGN(GraphicShaderUI);

public:
	static constexpr auto Type = EDITOR_UI_TYPE::GRAPHIC_SHADER;

private:
	static constexpr auto ChildSize = ImVec2(0, CHILDSIZE_ROW * 5);
	Ptr<GraphicShader> m_shader;

public:
	GraphicShaderUI();
	~GraphicShaderUI();

	virtual EDITOR_UI_TYPE GetType() final { return Type; }
	virtual ImVec2 GetChildSize() final { return ChildSize; }

	virtual void RenderUpdate() final;
};