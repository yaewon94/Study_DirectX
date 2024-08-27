#include "pch.h"
#include "Transform.h"
#include "GameObject.h"
#include "Device.h"
#include "ConstBuffer.h"

Transform::Transform(const Ptr<GameObject>& owner)
	: Component(owner), localScale(Vec3(1.f, 1.f, 1.f))
{

}

Transform::Transform(const Transform& origin, const Ptr<GameObject>& owner)
	: Component(origin, owner)
	, localPos(origin.localPos), localScale(origin.localScale), rotation(origin.rotation)
{
}

Transform::~Transform()
{
}

void Transform::Init()
{
	BindOnGpu();
}


void Transform::BindOnGpu()
{
	Ptr<ConstBuffer> cb = Device::GetInstance()->GetConstBuffer(CB_TYPE::TRANSFORM);

	CB_Transform tr = {};
	tr.pos = localPos;
	tr.scale = localScale;

	cb->SetData(&tr);
	cb->BindOnGpu();
}