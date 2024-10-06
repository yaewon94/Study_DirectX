#include "pch.h"
#include "TimeManager.h"
#include "Render.h"

TimeManager::TimeManager() 
	: m_frequency{}, m_curCount{}, m_prevCount{}
	, m_deltaTime(0.f), m_totalTime(0.f)
	, m_fps(0)
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Init()
{
	QueryPerformanceFrequency(&m_frequency);
	QueryPerformanceCounter(&m_prevCount);
}

void TimeManager::Tick()
{
	QueryPerformanceCounter(&m_curCount);

	// DT 계산
	m_deltaTime = (m_curCount.QuadPart - m_prevCount.QuadPart) / (float)m_frequency.QuadPart;
	if (m_deltaTime > 1.f / 60.f) m_deltaTime = 1.f / 60.f;

	// FPS 계산
	m_totalTime += m_deltaTime;
	++m_fps;

	if (m_totalTime > 1.f)
	{
		m_totalTime = 0.f;
		m_fps = 0;
	}

	m_prevCount = m_curCount;

	// 전역데이터 갱신
	g_global.dt = m_deltaTime;
	g_global.totalTime = m_totalTime;
}