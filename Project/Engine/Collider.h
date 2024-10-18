#pragma once
#include "Component.h"
#include "LayerEnums.h"
#include "Render.h"

#ifdef _DEBUG
#define COLOR_DEFAULT COLOR_GREEN
#define COLOR_COLLISION COLOR_RED
#endif // _DEBUG

class GameObject;

// 오브젝트간 충돌 감지를 위한 컴포넌트 [abstract]
class Collider : public Component
{
	NO_COPY_ASSIGN(Collider);

protected:
	Matrix m_worldMat;
	Matrix m_matTrans, m_matScale;

protected:
	Collider(const Ptr<GameObject>& owner);
	Collider(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~Collider();

public:
	const Matrix& GetWorldMatrix() { return m_worldMat; }

public:
	virtual void FinalTick() final;

public:
	void OnCollisionEnter(LAYER_TYPE other);
	void OnCollisionStay(LAYER_TYPE other);
	void OnCollisionExit(LAYER_TYPE other);

protected:
	virtual void OnChangeOffset() = 0;
	virtual void OnChangeScale() = 0;

#ifdef _DEBUG
protected:
	Ptr<GameObject> m_debugObj;
#endif // _DEBUG
};