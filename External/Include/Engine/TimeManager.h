#pragma once

// 시간 관련 처리 클래스
class TimeManager final : public Singleton<TimeManager>
{
	SINGLETON(TimeManager)

private:
	LARGE_INTEGER frequency;	// 초당 카운팅 가능 값
	LARGE_INTEGER curCount;		// 현재 카운트 값
	LARGE_INTEGER prevCount;	// 이전 프레임 카운트 값

	double deltaTime;	// 프레임 당 시간
	double totalTime;	// 누적 시간

	UINT fps;	// 초당 프레임 횟수

public:
	double GetDeltaTime() { return deltaTime; }

public:
	void Init();
	void Tick();
};