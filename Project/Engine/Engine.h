#pragma once

// 해상도
#define FullHD Vec2(1920, 1080)

// 게임 엔진 관리 클래스
class Engine final : public Singleton<Engine>
{
	SINGLETON(Engine);

private:
	HWND hwnd;
	Vec2 resolution = FullHD;

public:
	Vec2 GetResolution() { return resolution; }
	HWND GetHwnd() const { return hwnd; }

public:
	int Init(HWND hwnd);
	void Progress();
};