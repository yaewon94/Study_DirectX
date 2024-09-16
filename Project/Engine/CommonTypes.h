#pragma once

// =================================================
// Task
// =================================================
enum class TASK_TYPE
{
	CREATE_OBJECT,	// param0 : object address, param1 : LAYER_TYPE
	DELETE_OBJECT,	// param0 : object address
	CHANGE_LEVEL	// param0 : level address
};

struct TaskInfo
{
	TASK_TYPE Type;
	DWORD_PTR param0;
	DWORD_PTR param1;
};