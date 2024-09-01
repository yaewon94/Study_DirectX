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
	void SetPos(const Vec3& pos) { localPos = pos; OnChangePos(); }
	void SetPosX(float x) { localPos.x = x; OnChangePos(); }
	void SetPosY(float y) { localPos.y = y; OnChangePos(); }
	void SetPosZ(float z) { localPos.z = z; OnChangePos(); }

	Vec3 GetLocalScale() { return localScale; }
	void SetScaleX(float x) { localScale.x = x; OnChangeScale(); }
	void SetScaleY(float y) { localScale.y = y; OnChangeScale(); }
	void SetScaleZ(float z) { localScale.z = z; OnChangeScale(); }

	Vec3 GetLocalRotation() { return localRotation; }
	void SetRotationX(float x) { localRotation.x = x; OnChangeRotation(); }
	void SetRotationY(float y) { localRotation.y = y; OnChangeRotation(); }
	void SetRotationZ(float z) { localRotation.z = z; OnChangeRotation(); }
		
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