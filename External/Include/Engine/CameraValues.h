#pragma once

// ī�޶� index
enum class CAMERA_TYPE : int
{
	EDITOR_CAMERA = -100,
	NONE = -1,
	MAIN_CAMERA = 0,
	CAMERA_MINIMAP = 1
};

static const char* CameraTypeArr[] = { "Main Camera", "MiniMap" };
static int CameraTypeArrSize = sizeof(CameraTypeArr) / sizeof(const char*);

// ī�޶� ���� Ÿ��
enum class PROJECTION_TYPE : int
{
	// ���� ����
	PERSPECTIVE = 0, 
	// ���� ���� (2D)
	ORTHOGRAPHIC = 1
};

static const char* ProjTypeArr[] = { "Perspective", "Orthographic" };
static int ProjTypeArrSize = sizeof(ProjTypeArr) / sizeof(const char*);