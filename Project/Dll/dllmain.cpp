// [동적 라이브러리]
// .exe파일과 같이 컴파일 되는게 아니라
// 프로그램 실행 도중에 라이브러리를 요청한 경우, 메모리에 로딩됨
// 또는 동일한 DLL이 이미 메모리에 존재하는 경우, 운영체제에 의해서 링킹됨

// [출력 디렉터리 설정]
// 프로젝트 우클릭 > 속성 > 일반 > 출력 디렉터리

// [동적 라이브러리의 출력 파일 종류]
// .dll : 실제 내용 포함, .exe 파일과 같은 경로에 있어야 함
// .lib : dll 링크를 위한 명시 용도, 실시간 링크만 할거라면 필요가 없음

// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

