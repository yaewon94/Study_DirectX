#pragma once
#include "Component.h"

enum class LIGHT_TYPE : int
{
	DIRECTIONAL = 0,	// 방향성 광원 (태양광, 달)
	POINT = 1,			// 점 광원 (전구, 형광등, 스킬 이펙트, 횃불)
	SPOT = 2,			// 스포트 라이트 (손전등)
};

static const char* LightTypeArr[] = { "Directional", "Point", "Spot" };
static int LightTypeArrSize = sizeof(LightTypeArr) / sizeof(const char*);

// Light2D, Light3D 의 부모 클래스 (abstract)
class Light : public Component
{
	NO_COPY_ASSIGN(Light);

protected:
	Light(const Ptr<GameObject>& owner);
	Light(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~Light();

public:
	virtual COMPONENT_TYPE GetBaseType() final { return COMPONENT_TYPE::LIGHT; }
};