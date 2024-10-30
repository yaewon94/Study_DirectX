#pragma once

// Editor UI Type (�� = ���� ������ �� ������ ����)
enum class EDITOR_UI_TYPE
{
	MENU, OUTLINER, INSPECTOR, CONTENT, TREE, LIST,

	// COMPONENT UI (�� = Inspector���� ������ ����)
	TRANSFORM, CAMERA, MESH_RENDER, LIGHT_2D, COLLIDER_2D,

	// ASSET UI
	MESH, GRAPHIC_SHADER
};