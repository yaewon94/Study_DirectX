#pragma once
#include "Component.h"
#include "LayerValues.h"

// 사용자 정의 스크립트 컴포넌트
class Script : public Component
{
	NO_COPY_ASSIGN(Script);

protected:
	Script(const Ptr<GameObject>& owner);
	Script(const Ptr<Script>& origin, const Ptr<GameObject>& owner);
	~Script();

public:
	virtual Ptr<Script> Clone(const Ptr<Script>& origin, const Ptr<GameObject>& owner) = 0;

public:
	virtual void Tick() = 0;
	virtual void FinalTick() override {}

public:
	virtual void OnCollisionEnter(LAYER_TYPE other) = 0;
	virtual void OnCollisionStay(LAYER_TYPE other) = 0;
	virtual void OnCollisionExit(LAYER_TYPE other) = 0;

private:
	// delete
	virtual Ptr<Component> Clone(const Ptr<Component>&, const Ptr<GameObject>&) final
	{
		return nullptr;
	}
};