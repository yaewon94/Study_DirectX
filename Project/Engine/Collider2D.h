#pragma once
#include "Collider.h"

// 오브젝트간 충돌 감지를 위한 컴포넌트
class Collider2D final : public Collider
{
	NO_COPY_ASSIGN(Collider2D);

private:
	Vec2 m_offset;
	Vec2 m_scale;

public:
	Collider2D(const Ptr<GameObject>& owner);
	Collider2D(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~Collider2D();

	virtual Ptr<Component> Clone(const Ptr<Component>& origin, const Ptr<GameObject>& owner) final
	{
		return Ptr<Collider2D>(origin, owner).ptr_dynamic_cast<Component>();
	}

public:
	Vec2 GetOffset() { return m_offset; }
	Vec2 GetScale() { return m_scale; }

	void SetOffset(Vec2 offset) { m_offset = offset; OnChangeOffset(); }
	void SetScale(Vec2 scale) { m_scale = scale; OnChangeScale(); }

public:
	virtual void Init() final;

private:
	virtual void OnChangeOffset();
	virtual void OnChangeScale();
};