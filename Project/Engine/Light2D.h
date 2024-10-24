#pragma once
#include "Light.h"
#include "TransformValues.h"

struct Light2dInfo
{
	Vec3 color = Vec3(1.f, 1.f, 1.f);
	Vec2 worldPos = Vec2(0.f, 0.f);
	Vec2 dir = Vec2(0.f, 0.f);
	LIGHT_TYPE type = LIGHT_TYPE::DIRECTIONAL;
	float radius = 0.f;
	float angle = 0.f;
	double padding = 0.; // 16바이트의 배수로 맞추기 위한 공간
};

// 2D 조명
class Light2D final : public Light
{
private:
	Light2dInfo m_info;
	DIRECTION_2D m_dirType;

public:
	Light2D(const Ptr<GameObject>& owner);
	Light2D(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~Light2D();
	
	virtual Ptr<Component> Clone(const Ptr<Component>& origin, const Ptr<GameObject>& owner) final
	{
		return Ptr<Light2D>(origin, owner).ptr_dynamic_cast<Component>();
	}

public:
	const Light2dInfo& GetInfo() { return m_info; }
	
	int GetAngle() { return (int)(m_info.angle * 180.f / XM_PI); }
	void SetAngle(int angle); // @angle : 0 ~ 90

	Vec3 GetColor() { return m_info.color; }
	void SetColor(Vec3 color) { m_info.color = color; }

	DIRECTION_2D GetDirection() { return m_dirType; }
	void SetDirection(DIRECTION_2D dir) { m_dirType = dir; m_info.dir = Direction2dValueArr[(UINT)dir]; }

	float GetRadius() { return m_info.radius; }
	void SetRadius(float radius);

	LIGHT_TYPE GetLightType() { return m_info.type; }
	void SetLightType(LIGHT_TYPE type) { m_info.type = type; }

public:
	virtual void Init() final;
	virtual void FinalTick() final;
};