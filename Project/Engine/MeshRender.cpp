#include "pch.h"
#include "MeshRender.h"
#include "GameObject.h"

MeshRender::MeshRender(const GameObject& Owner) : Component(Owner)
{
}

MeshRender::MeshRender(const MeshRender& origin, const GameObject& Owner) 
	: Component(origin, Owner)
	, mesh(origin.mesh), shader(origin.shader)
{
}

MeshRender::~MeshRender()
{
}

void MeshRender::FinalTick()
{
}

void MeshRender::Render()
{
	if (mesh.Get() && shader.Get())
	{
		shader->Bind();
		mesh->Render();
	}
}