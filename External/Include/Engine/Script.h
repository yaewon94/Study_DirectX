#pragma once
#include "Component.h"

class GameObject;

// 사용자 정의 스크립트 컴포넌트
class Script : public Component
{
	NO_COPY_ASSIGN(Script);

protected:
	Script(const GameObject& Owner);
	Script(const Script& origin, const GameObject& Owner);
	~Script();
};