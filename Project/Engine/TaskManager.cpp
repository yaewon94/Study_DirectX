#include "pch.h"
#include "TaskManager.h"
#include "LevelManager.h"
#include "GameObject.h"

TaskManager::TaskManager()
{
}

TaskManager::~TaskManager()
{
}

void TaskManager::Tick()
{
	for (auto& task : m_taskVec)
	{
		if (task.Type == TASK_TYPE::CREATE_OBJECT)
		{
			Ptr<GameObject> obj = Ptr<GameObject>(task.param0);
			obj->SetLayer((LAYER_TYPE)task.param1);
			obj->Init();
		}
		else if (task.Type == TASK_TYPE::DELETE_OBJECT)
		{
			Ptr<GameObject> obj = Ptr<GameObject>(task.param0);
			obj->SetDead();
		}
		else if (task.Type == TASK_TYPE::CHANGE_LEVEL_STATE)
		{
			LevelManager::GetInstance()->ChangeState((LEVEL_STATE)task.param0);
		}
		else if (task.Type == TASK_TYPE::CHANGE_LEVEL)
		{
		}
		else
		{
			throw std::logic_error("정의되지 않은 Task 타입입니다");
		}
	}

	m_taskVec.clear();
}

void TaskManager::CreateObject(Ptr<GameObject> obj, LAYER_TYPE layer)
{
	TaskInfo info = {};
	info.Type = TASK_TYPE::CREATE_OBJECT;
	info.param0 = (DWORD_PTR)(obj.Get());
	info.param1 = (DWORD_PTR)layer;
	AddTask(info);
}

void TaskManager::DeleteObject(Ptr<GameObject> obj)
{
	TaskInfo info = {};
	info.Type = TASK_TYPE::DELETE_OBJECT;
	info.param0 = (DWORD_PTR)(obj.Get());
	AddTask(info);
}

void TaskManager::ChangeLevelState(LEVEL_STATE state)
{
	TaskInfo info = {};
	info.Type = TASK_TYPE::CHANGE_LEVEL;
	info.param0 = (DWORD_PTR)state;
	AddTask(info);
}