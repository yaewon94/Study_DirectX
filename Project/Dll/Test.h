#pragma once
#include <string>

#ifdef  DLL_EXPORTS	// 프로젝트에 해당 이름의 전처리기가 정의되어 있다는 뜻
#define MYDLL  __declspec(dllexport)
#else
#define MYDLL __declspec(dllimport)
#endif

extern"C" MYDLL std::string GetLibraryNameDll();