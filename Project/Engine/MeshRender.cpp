#include "pch.h"
#include "MeshRender.h"

MeshRender::MeshRender(const GameObject& Owner) : Component(Owner)
{
}

MeshRender::MeshRender(const MeshRender& origin, const GameObject& Owner) : Component(origin, Owner)
{
}

MeshRender::~MeshRender()
{
}
