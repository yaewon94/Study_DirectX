#pragma once
#include "Component.h"
#include "TransformValues.h"

// 게임오브젝트의 좌표, 크기, 회전 정보
class Transform final : public Component
{
	NO_COPY_ASSIGN(Transform);

private:
	Vec3 m_localPos, m_localScale, m_localRotation;	// 상대좌표, 크기, 회전각

	Matrix m_worldMatrix;	// 월드행렬(크기 * 회전 * 좌표)
	Matrix m_matTrans, m_matScale, m_matRot;

	array<Vec3, 3> m_localDirVec;	// 방향벡터 (회전에 필요)
	array<Vec3, 3> m_worldDirVec;

public:
	Transform(const Ptr<GameObject>& owner);
	Transform(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~Transform();

	virtual Ptr<Component> Clone(const Ptr<Component>& origin, const Ptr<GameObject>& owner) final
	{
		return Ptr<Transform>(origin, owner).ptr_dynamic_cast<Component>();
	}

public:
	virtual COMPONENT_TYPE GetBaseType() final { return COMPONENT_TYPE::TRANSFORM; }

	Vec3 GetWorldPos() { return m_worldMatrix.Translation(); }
	Vec3 GetLocalPos() { return m_localPos; }
	void SetLocalPos(const Vec3& pos) { m_localPos = pos; OnChangePos(); }
	void SetLocalPosX(float x) { m_localPos.x = x; OnChangePos(); }
	void SetLocalPosY(float y) { m_localPos.y = y; OnChangePos(); }
	void SetLocalPosZ(float z) { m_localPos.z = z; OnChangePos(); }

	Vec3 GetWorldScale();
	Vec3 GetLocalScale() { return m_localScale; }
	void SetLocalScale(const Vec3& scale) { m_localScale = scale; OnChangeScale(); }
	void SetLocalScaleX(float x) { m_localScale.x = x; OnChangeScale(); }
	void SetLocalScaleY(float y) { m_localScale.y = y; OnChangeScale(); }
	void SetLocalScaleZ(float z) { m_localScale.z = z; OnChangeScale(); }

	Vec3 GetLocalRotation() { return m_localRotation; }
	void SetLocalRotation(const Vec3& rotation) { m_localRotation = rotation; OnChangeRotation(); }
	void SetLocalRotationX(float x) { m_localRotation.x = x; OnChangeRotation(); }
	void SetLocalRotationY(float y) { m_localRotation.y = y; OnChangeRotation(); }
	void SetLocalRotationZ(float z) { m_localRotation.z = z; OnChangeRotation(); }

	Vec3 GetWorldDirection(DIRECTION_VEC dir) { return m_worldDirVec[(UINT)dir]; }

	const Matrix& GetWorldMatrix() { return m_worldMatrix; }
		
public:
	virtual void Init() final;
	virtual void FinalTick() final;

public:
	void BindOnGpu();

private:
	void OnChangePos();
	void OnChangeScale();
	void OnChangeRotation();
	void OnChangeMatrix();
};