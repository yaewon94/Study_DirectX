#pragma once
#include "Singleton.h"
#include "Render.h"

class Camera;
class GameObject;
class Texture;

// 카메라 index
enum class CAMERA_TYPE : UINT
{
	MAIN_CAMERA
};


// 렌더링 담당 클래스
class RenderManager : public Singleton<RenderManager>
{
	SINGLETON(RenderManager);
	
private:
	vector<Ptr<Camera>> m_cameras;
	Ptr<Texture> m_postProcessTex;	// 후처리용 텍스처 (렌더타겟 복사용도)

public:
	void AddCamera(const Ptr<Camera>& camera);
	void AddRenderObj(CAMERA_TYPE type, const Ptr<GameObject>& obj);
	void DeleteRenderObj(CAMERA_TYPE type, const Ptr<GameObject>& obj);
	void CopyRenderTarget();

public:
	int Init();
	void Render();

private:
	void BindOnGpu();

#ifdef _DEBUG
public:
	Ptr<GameObject> CreateDebugShape(const DebugShapeInfo& info);
	void ChangeDebugShape(const Ptr<GameObject>& obj, DEBUG_SHAPE shape);
#endif // _DEBUG
};