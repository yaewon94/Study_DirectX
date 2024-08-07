#include "pch.h"
#include "Transform.h"
#include "GameObject.h"
#include "Device.h"
#include "ConstBuffer.h"

Transform::Transform(const GameObject& Owner) 
	: Component(Owner), scale(Vec3(100, 100, 1))
{
}

Transform::Transform(const Transform& origin, const GameObject& Owner) 
	: Component(origin, Owner)
	, pos(origin.pos), scale(origin.scale), rotation(origin.rotation)
{
}

Transform::~Transform()
{
}

void Transform::FinalTick()
{
}

void Transform::Bind()
{
	Ptr<ConstBuffer> cb = Device::GetInstance()->GetConstBuffer(CB_TYPE::TRANSFORM);

	CB_Transform tr = {};
	tr.pos = pos;
	cb->SetData(&tr);
	cb->Bind();
}