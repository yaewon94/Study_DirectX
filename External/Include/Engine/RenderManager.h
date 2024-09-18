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
private:
	vector<Ptr<GameObject>> m_debugObjs;
	vector<DebugShapeInfo> m_debugShapeInfos;

public:
	Ptr<GameObject> AddDebugShape(const DebugShapeInfo& info);
	void ChangeDebugShape(const Ptr<GameObject>& obj, DEBUG_SHAPE shape);
	void ChangeDebugColor(const Ptr<GameObject>& obj, Vec4 color);
#endif // _DEBUG
};