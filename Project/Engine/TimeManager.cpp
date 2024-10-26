#include "pch.h"
#include "TimeManager.h"
#include "Render.h"

#define MAX_DT 1.f/ 60.f

TimeManager::TimeManager() 
	: m_frequency{}, m_curCount{}, m_prevCount{}
	, m_dt(0.f), m_time(0.f)
	, m_engineDT(0.f), m_engineTime(0.f)
	, m_fps(0)
	, m_isLevelStop(true)
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::SetLevelStop(bool flag)
{
	m_isLevelStop = flag;
	if (m_isLevelStop) m_dt = 0.f;
}

void TimeManager::Init()
{
	QueryPerformanceFrequency(&m_frequency);
	QueryPerformanceCounter(&m_prevCount);
}

void TimeManager::Tick()
{
	static float second = 0.f;

	QueryPerformanceCounter(&m_curCount);

	// ���� DT ���
	m_engineDT = (float)(m_curCount.QuadPart - m_prevCount.QuadPart) / (float)m_frequency.QuadPart;
	if (m_engineDT > MAX_DT) m_engineDT = MAX_DT;

	// ���� �����ð� ���
	m_engineTime += m_engineDT;

	// �� ���� �ð� ���
	second += m_engineDT;
	++m_fps;

	if (second > 1.f)
	{
		second = 0.f;
		m_fps = 0;
	}

	m_prevCount = m_curCount;

	// ������ ���� ���϶�
	if (!m_isLevelStop)
	{
		m_dt = m_engineDT;
		m_time += m_dt;
	}

	// ���������� ����
	g_global.dt = m_dt;
	g_global.totalTime = m_time;

	g_global.dt_engine = m_engineDT;
	g_global.totalTime_engine = m_engineTime;
}