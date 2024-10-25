#pragma once
#include "Engine/Singleton.h"

class GameObject;

// ���� ��(������ ���) ���� �����ϴ� ������Ʈ ����
class EditorManager final : public Singleton<EditorManager>
{
	SINGLETON(EditorManager);

private:
	vector<Ptr<GameObject>> m_objs;

public:
	int Init();
	void Progress();
};