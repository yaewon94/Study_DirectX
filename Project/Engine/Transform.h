#pragma once
#include "Component.h"

// 게임오브젝트의 좌표, 크기, 회전 정보
class Transform final : public Component
{
	NO_COPY_ASSIGN(Transform);

private:
	Vec3 pos;
	Vec3 scale;
	Vec3 rotation;

private:
	template<typename T> requires std::derived_from<T, Component>
	friend static T* Component::Create(const GameObject& Owner);

	Transform(const GameObject& Owner);
	Transform(const Transform& origin, const GameObject& Owner);
	~Transform();

public:
	virtual Transform* Clone(const GameObject& Owner) final { return new Transform(*this, Owner); }

public:
	Vec3 GetPos() { return pos; }
	void SetPos(const Vec3& pos) { this->pos = pos; }
	void SetPosX(float x) { pos.x = x; }
	void SetPosY(float y) { pos.y = y; }
	void SetPosZ(float z) { pos.z = z; }

	Vec3 GetScale() { return scale; }
	void SetScale(const Vec3& scale) { this->scale = scale; }

	Vec3 GetRotation() { return rotation; }
	void SetRotation(const Vec3& rotation) { this->rotation = rotation; }

public:
	virtual void FinalTick() final;

public:
	void Bind();
};