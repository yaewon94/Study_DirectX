#include "pch.h"
#include "TimeManager.h"

TimeManager::TimeManager() 
	: frequency{}, curCount{}, prevCount{}
	, deltaTime(0.), totalTime(0.)
	, fps(0)
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Init()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&prevCount);
}

void TimeManager::Tick()
{
	QueryPerformanceCounter(&curCount);

	// DT 계산
	deltaTime = (curCount.QuadPart - prevCount.QuadPart) / (double)frequency.QuadPart;
	if (deltaTime > 1.f / 60.f) deltaTime = 1.f / 60.f;

	// FPS 계산
	totalTime += deltaTime;
	++fps;

	if (totalTime > 1.)
	{
		totalTime = 0.;
		fps = 0;
	}

	prevCount = curCount;
}