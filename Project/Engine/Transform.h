#pragma once
#include "Component.h"

// 게임오브젝트의 좌표, 크기, 회전 정보
class Transform final : public Component
{
	NO_COPY_ASSIGN(Transform);

private:
	Vec3 localPos, localScale, localRotation;

	Matrix worldMatrix;
	Matrix matTrans, matRotation, matScale;

public:
	Transform(const Ptr<GameObject>& owner);
	Transform(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~Transform();

	virtual Ptr<Component> Clone(const Ptr<Component>& origin, const Ptr<GameObject>& owner) final
	{
		return Ptr<Transform>(origin, owner).ptr_dynamic_cast<Component>();
	}

public:
	Vec3 GetLocalPos() { return localPos; }
	void SetPosX(float x);
	void SetPosY(float y);
	void SetPosZ(float z);

	Vec3 GetLocalScale() { return localScale; }
	void SetScaleX(float x);
	void SetScaleY(float y);
	void SetScaleZ(float z);

	Vec3 GetLocalRotation() { return localRotation; }
	void SetRotationX(float x);
	void SetRotationY(float y);
	void SetRotationZ(float z);
		
public:
	virtual void Init() final;
	virtual void FinalTick() final;

private:
	void BindOnGpu();

private:
	void OnChangePos();
	void OnChangeScale();
	void OnChangeRotation();
	void OnChangeMatrix();
};