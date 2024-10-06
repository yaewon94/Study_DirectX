#pragma once

// 시간 관련 처리 클래스
class TimeManager final : public Singleton<TimeManager>
{
	SINGLETON(TimeManager)

private:
	LARGE_INTEGER m_frequency;	// 초당 카운팅 가능 값
	LARGE_INTEGER m_curCount;	// 현재 카운트 값
	LARGE_INTEGER m_prevCount;	// 이전 프레임 카운트 값

	float m_deltaTime;	// 프레임 당 시간
	float m_totalTime;	// 누적 시간

	UINT m_fps;	// 초당 프레임 횟수

public:
	float GetDeltaTime() { return m_deltaTime; }

public:
	void Init();
	void Tick();
};