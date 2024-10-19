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
	char curDir[256];
	//GetCurrentDirectory(256, curDir); // 아무것도 안건드렸는데 갑자기 Client 프로젝트 위치한 경로로 바뀜
	GetModuleFileNameA(nullptr, curDir, 256);
	GetParentPath(curDir);
	GetParentPath(curDir);

	// $(SolutionDir)Output
	contentPath = curDir;
	contentPath += "\\content\\";
}

void PathManager::GetParentPath(char* path)
{
	// 부모 디렉터리로 이동
	for (size_t i = strlen(path) - 1; i > 0; --i)
	{
		if (path[i] == '\\')
		{
			path[i] = '\0';
			break;
		}
	}
}