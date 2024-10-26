#pragma once

// �ð� ���� ó�� Ŭ����
class TimeManager final : public Singleton<TimeManager>
{
	SINGLETON(TimeManager)

private:
	LARGE_INTEGER m_frequency;	// �ʴ� ī���� ���� ��
	LARGE_INTEGER m_curCount;	// ���� ī��Ʈ ��
	LARGE_INTEGER m_prevCount;	// ���� ������ ī��Ʈ ��

	float m_dt;		// ������ �� �ð�
	float m_time;	// ���� �ð�

	float m_engineDT;
	float m_engineTime;

	UINT m_fps;	// �ʴ� ������ Ƚ��
	bool m_isLevelStop;

public:
	float GetDeltaTime() { return m_dt; }
	float GetEngineDeltaTime() { return m_engineDT; }
	void SetLevelStop(bool flag);

public:
	void Init();
	void Tick();
};