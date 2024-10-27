#pragma once
#include "Engine/Singleton.h"

class GameObjectEx;

// ���� ��(������ ���) ���� �����ϴ� ������Ʈ ����
class EditorManager final : public Singleton<EditorManager>
{
	SINGLETON(EditorManager);

private:
	vector<Ptr<GameObjectEx>> m_objs;

public:
	int Init();
	void Progress();
};