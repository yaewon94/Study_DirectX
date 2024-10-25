#pragma once
#include "Engine/Singleton.h"

class GameObject;

// 레벨 외(에디터 모드) 에서 동작하는 오브젝트 관리
class EditorManager final : public Singleton<EditorManager>
{
	SINGLETON(EditorManager);

private:
	vector<Ptr<GameObject>> m_objs;

public:
	int Init();
	void Progress();
};