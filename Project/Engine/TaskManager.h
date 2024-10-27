#pragma once
#include "Singleton.h"
#include "Level.h"

class GameObject;

// �۾��� ��Ƽ� ���� �����ӿ� ó���� �� �ְ� ��
class TaskManager : public Singleton<TaskManager>
{
	SINGLETON(TaskManager);

private:
	// �۾� Ÿ��
	enum class TASK_TYPE
	{
		CREATE_OBJECT,	// param0 : object address, param1 : LAYER_TYPE
		DELETE_OBJECT,	// param0 : object address
		CHANGE_LEVEL,	// param0 : level address
		CHANGE_LEVEL_STATE,	// param0 : level state
	};

	// �۾� ����
	struct TaskInfo
	{
		TASK_TYPE Type;
		DWORD_PTR param0;
		DWORD_PTR param1;
	};

private:
	vector<TaskInfo> m_taskVec;
	void AddTask(const TaskInfo& task) { m_taskVec.push_back(task); }

public:
	void Tick();

public:
	void CreateObject(Ptr<GameObject> obj, LAYER_TYPE layer);
	void DeleteObject(Ptr<GameObject> obj);
	void ChangeLevelState(LEVEL_STATE state);
};