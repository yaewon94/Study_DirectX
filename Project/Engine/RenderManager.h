#pragma once
#include "Singleton.h"
#include "Render.h"
#include "CameraValues.h"

class StructuredBuffer;
class Camera;
class GameObject;
class Texture;
class Light2D;
struct Light2dInfo;


// 렌더링 담당 클래스
class RenderManager : public Singleton<RenderManager>
{
	SINGLETON(RenderManager);
	
private:
	Ptr<Camera> m_editorCam;
	map<CAMERA_TYPE, Ptr<Camera>> m_levelCameraMap;

	Ptr<Texture> m_rtTex;	// Render Target
	Ptr<Texture> m_dsTex;	// Depth Stencil
	Ptr<Texture> m_postProcessTex;	// 후처리용 텍스처 (렌더타겟 복사용도)

	Ptr<StructuredBuffer> m_light2dBuffer;
	vector<Ptr<Light2D>> m_light2Ds;
	vector<Light2dInfo> m_light2dInfos;

	bool m_isEditorMode;

public:
	bool IsEditorMode() { return m_isEditorMode; }
	void SetEditorMode(bool isEditorMode) { m_isEditorMode = isEditorMode; }
	int ChangeCameraType(Ptr<Camera> camera, CAMERA_TYPE type);
	void AddRenderObj(Ptr<GameObject> obj, CAMERA_TYPE type = CAMERA_TYPE::MAIN_CAMERA);
	void DeleteRenderObj(Ptr<GameObject> obj, CAMERA_TYPE type = CAMERA_TYPE::MAIN_CAMERA);

	void AddLight2D(Ptr<Light2D> light);

public:
	int Init();
	void Render();

public:
	void CopyRenderTarget();

private:
	void BindOnGpu();
	void Clear();

#ifdef _DEBUG
public:
	void InitDebugShape(Ptr<GameObject> obj, const DebugShapeInfo& info);
	void ChangeDebugShape(Ptr<GameObject> obj, DEBUG_SHAPE shape);
	void ChangeDebugPos(Ptr<GameObject> obj, Vec3 pos);
	void ChangeDebugScale(Ptr<GameObject> obj, Vec3 scale);
#endif // _DEBUG
};