#pragma once
#include "Singleton.h"

class Camera;

// 렌더링 담당 클래스
class RenderManager : public Singleton<RenderManager>
{
	SINGLETON(RenderManager);

private:
	vector<Ptr<Camera>> cameras;

public:
	void AddCamera(const Ptr<Camera>& camera);

public:
	void Render();
};