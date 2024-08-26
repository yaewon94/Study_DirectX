#include "pch.h"
#include "Transform.h"
#include "GameObject.h"
#include "Device.h"
#include "ConstBuffer.h"

Transform::Transform(const Ptr<GameObject>& owner)
	: Component(owner), scale(Vec3(100, 100, 1))
{

}

Transform::Transform(const Transform& origin, const Ptr<GameObject>& owner)
	: Component(origin, owner)
	, pos(origin.pos), scale(origin.scale), rotation(origin.rotation)
{
}

Transform::~Transform()
{
}

void Transform::BindOnGpu()
{
	Ptr<ConstBuffer> cb = Device::GetInstance()->GetConstBuffer(CB_TYPE::TRANSFORM);

	CB_Transform tr = {};
	tr.pos = pos;
	cb->SetData(&tr);
	cb->BindOnGpu();
}