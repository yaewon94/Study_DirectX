#pragma once
#include "Component.h"

// 사용자 정의 스크립트 컴포넌트
class Script : public Component
{
	NO_COPY_ASSIGN(Script);

protected:
	Script(const Ptr<GameObject>& owner);
	Script(const Script& origin, const Ptr<GameObject>& owner);
	~Script();

public:
	virtual void Tick() = 0;
	virtual void FinalTick() override {}
};