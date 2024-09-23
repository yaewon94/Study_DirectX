#pragma once
#include "Singleton.h"
#include "Render.h"

class Camera;
class GameObject;

// 렌더링 담당 클래스
class RenderManager : public Singleton<RenderManager>
{
	SINGLETON(RenderManager);
	
private:
	vector<Ptr<Camera>> m_cameras;

public:
	void AddCamera(const Ptr<Camera>& camera);

public:
	void Render();

#ifdef _DEBUG
public:
	Ptr<GameObject> CreateDebugShape(const DebugShapeInfo& info);
	void ChangeDebugShape(const Ptr<GameObject>& obj, DEBUG_SHAPE shape);
#endif // _DEBUG
};