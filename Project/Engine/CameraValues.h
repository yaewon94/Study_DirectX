#pragma once

// 카메라 index
enum class CAMERA_TYPE : int
{
	EDITOR_CAMERA = -100,
	NONE = -1,
	MAIN_CAMERA = 0,
	CAMERA_MINIMAP = 1
};

static const char* CameraTypeArr[] = { "Main Camera", "MiniMap" };
static int CameraTypeArrSize = sizeof(CameraTypeArr) / sizeof(const char*);

// 카메라 투영 타입
enum class PROJECTION_TYPE : int
{
	// 원근 투영
	PERSPECTIVE = 0, 
	// 직교 투영 (2D)
	ORTHOGRAPHIC = 1
};

static const char* ProjTypeArr[] = { "Perspective", "Orthographic" };
static int ProjTypeArrSize = sizeof(ProjTypeArr) / sizeof(const char*);