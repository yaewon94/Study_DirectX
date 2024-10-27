#pragma once
#include "Singleton.h"
#include "Level.h"

class GameObject;

// 작업을 모아서 다음 프레임에 처리할 수 있게 함
class TaskManager : public Singleton<TaskManager>
{
	SINGLETON(TaskManager);

private:
	// 작업 타입
	enum class TASK_TYPE
	{
		CREATE_OBJECT,	// param0 : object address, param1 : LAYER_TYPE
		DELETE_OBJECT,	// param0 : object address
		CHANGE_LEVEL,	// param0 : level address
		CHANGE_LEVEL_STATE,	// param0 : level state
	};

	// 작업 정보
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