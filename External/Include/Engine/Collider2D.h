#pragma once
#include "Component.h"

// 오브젝트간 충돌 감지를 위한 컴포넌트
class Collider2D final : public Component
{
	NO_COPY_ASSIGN(Collider2D);

private:
	Vec3 m_offset;
	Vec3 m_scale;

public:
	Collider2D(const Ptr<GameObject>& owner);
	Collider2D(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~Collider2D();

	virtual Ptr<Component> Clone(const Ptr<Component>& origin, const Ptr<GameObject>& owner) final
	{
		return Ptr<Collider2D>(origin, owner).ptr_dynamic_cast<Component>();
	}

public:
	virtual void Init() final;
	virtual void FinalTick() final {}

#ifdef _DEBUG
private:
	Ptr<GameObject> m_debugObj;
#endif // _DEBUG
};