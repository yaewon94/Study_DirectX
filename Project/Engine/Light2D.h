#pragma once
#include "Light.h"
#include "TransformValues.h"

struct Light2dInfo
{
	Vec3 color;
	Vec2 worldPos;
	Vec2 dir;
	LIGHT_TYPE type;
	float radius;
	float angle;
	double padding; // 16바이트의 배수로 맞추기 위한 공간
};

// 2D 조명
class Light2D final : public Light
{
private:
	Light2dInfo m_info;

public:
	Light2D(const Ptr<GameObject>& owner);
	Light2D(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~Light2D();
	
	virtual Ptr<Component> Clone(const Ptr<Component>& origin, const Ptr<GameObject>& owner) final
	{
		return Ptr<Light2D>(origin, owner).ptr_dynamic_cast<Component>();
	}

public:
	const Light2dInfo& GetInfo();
	
	void SetAngle(int angle); // @angle : 0 ~ 360
	void SetColor(Vec3 color) { m_info.color = color; }
	void SetDirection(DIRECTION_VEC type) { m_info.dir = Directions[(UINT)type].XY(); }
	void SetRadius(float radius) { m_info.radius = radius; }
	void SetType(LIGHT_TYPE type) { m_info.type = type; }

public:
	virtual void Init() final;
	virtual void FinalTick() final;
};