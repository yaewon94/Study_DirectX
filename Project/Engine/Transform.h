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

public:
	Transform(const Ptr<GameObject>& owner);
	Transform(const Transform& origin, const Ptr<GameObject>& owner);
	~Transform();

public:
	Vec3 GetPos() { return pos; }
	void SetPosX(float x) { pos.x = x; }
	void SetPosY(float y) { pos.y = y; }
	void SetPosZ(float z) { pos.z = z; }

	Vec3 GetScale() { return scale; }

	Vec3 GetRotation() { return rotation; }

public:
	virtual void FinalTick() final {}

public:
	void BindOnGpu();
};