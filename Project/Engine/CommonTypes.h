#pragma once

// =================================================
// Task
// =================================================
enum class TASK_TYPE
{
	CREATE_OBJECT,	// 0 : object address, layer index
	DELETE_OBJECT,	// 0 : object address
	CHANGE_LEVEL	// 0 : level address
};

struct TaskInfo
{
	TASK_TYPE Type;
	DWORD_PTR param0;
	DWORD_PTR param1;
};