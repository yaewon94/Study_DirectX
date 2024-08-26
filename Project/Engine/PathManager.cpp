#include "pch.h"
#include "PathManager.h"

PathManager::PathManager()
{
}

PathManager::~PathManager()
{
}

void PathManager::Init()
{
	// .exe 파일 경로 알아내기
	wchar_t curDir[256];
	GetCurrentDirectory(256, curDir);

	// 부모 디렉터리로 이동
	for (size_t i = wcslen(curDir) - 1; i > 0; --i)
	{
		if (curDir[i] == L'\\')
		{
			curDir[i] = L'\0';
			break;
		}
	}

	// $(SolutionDir)Output
	contentPath = curDir;
	contentPath += L"\\content\\";
}