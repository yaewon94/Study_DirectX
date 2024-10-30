#pragma once

// Editor UI Type (값 = 같은 계층일 때 렌더링 순서)
enum class EDITOR_UI_TYPE
{
	MENU, OUTLINER, INSPECTOR, CONTENT, TREE, LIST,

	// COMPONENT UI (값 = Inspector에서 렌더링 순서)
	TRANSFORM, CAMERA, MESH_RENDER, LIGHT_2D, COLLIDER_2D,

	// ASSET UI
	MESH, GRAPHIC_SHADER
};