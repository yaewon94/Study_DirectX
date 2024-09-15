#pragma once
#include "Singleton.h"
#include "Render.h"

class Camera;

// 디버깅 모드 정보
struct DebugShapeInfo
{
	DEBUG_SHAPE shape = DEBUG_SHAPE::RECT;
	Vec3 pos;
	Vec4 color = COLOR_GREEN;

	const float Duration;
	float curTime = 0.f;

	bool hasDepthTest = false;	// 깊이판정 수행 여부
};

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