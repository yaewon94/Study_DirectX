#pragma once
#include "Component.h"

// 게임오브젝트의 좌표, 크기, 회전 정보
class Transform final : public Component
{
	NO_COPY_ASSIGN(Transform);

private:
	Vec3 localPos;
	Vec3 localScale;
	Vec3 rotation;

public:
	Transform(const Ptr<GameObject>& owner);
	Transform(const Transform& origin, const Ptr<GameObject>& owner);
	~Transform();

public:
	Vec3 GetLocalPos() { return localPos; }
	void SetPosX(float x) { localPos.x = x; BindOnGpu(); }
	void SetPosY(float y) { localPos.y = y; BindOnGpu(); }
	void SetPosZ(float z) { localPos.z = z; BindOnGpu(); }

	Vec3 GetLocalScale() { return localScale; }
	void SetScaleX(float x) { localScale.x = x; BindOnGpu(); }
	void SetScaleY(float y) { localScale.y = y; BindOnGpu(); }
	void SetScaleZ(float z) { localScale.z = z; BindOnGpu(); }

public:
	virtual void Init() final;
	virtual void FinalTick() final;

private:
	void BindOnGpu();
};