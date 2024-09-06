#pragma once
#include "Singleton.h"

// 작업을 모아서 다음 프레임에 처리할 수 있게 함
class TaskManager : public Singleton<TaskManager>
{
	SINGLETON(TaskManager);

private:
	vector<TaskInfo> taskVec;

public:
	void AddTesk(const TaskInfo& task) { taskVec.push_back(task); }

public:
	void Tick();
};