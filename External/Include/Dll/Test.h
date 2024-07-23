#pragma once
#include <string>

#ifdef  DLL_EXPORTS
#define MYDLL  __declspec(dllexport)
#else
#define MYDLL __declspec(dllimport)
#endif //  DLL_EXPORT

extern"C" MYDLL std::string GetLibraryNameDll();