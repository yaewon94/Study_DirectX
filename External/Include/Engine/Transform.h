#pragma once
#include "Component.h"

// 게임오브젝트의 좌표, 크기, 회전 정보
class Transform final : public Component
{
	NO_COPY_ASSIGN(Transform);
	friend class GameObject;

private:
	const static COMPONENT_TYPE Type = COMPONENT_TYPE::TRANSFORM;

private:
	Vec3 pos;
	Vec3 scale;
	Vec3 rotation;

public:
	Vec3 GetPos() { return pos; }
	void SetPos(Vec3 pos) { this->pos = pos; }

	Vec3 GetScale() { return scale; }
	void SetScale(Vec3 scale) { this->scale = scale; }

	Vec3 GetRotation() { return rotation; }
	void SetRotation() { this->rotation = rotation; }

private:
	Transform(const GameObject& Owner);
	Transform(const Transform& origin, const GameObject& Owner);
	~Transform();

private:
	virtual Transform* Clone(const GameObject& Owner) final { return new Transform(*this, Owner); }
};