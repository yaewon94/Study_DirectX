#include "pch.h"
#include "MeshRender.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Material.h"

MeshRender::MeshRender(const Ptr<GameObject>& owner) : RenderComponent(owner)
{
}

MeshRender::MeshRender(const Ptr<Component>& origin, const Ptr<GameObject>& owner)
	: RenderComponent(origin, owner)
{
	auto ptr = origin.ptr_dynamic_cast<MeshRender>();
	mesh = ptr->mesh;
}

MeshRender::~MeshRender()
{
}

void MeshRender::SetMesh(const Ptr<Mesh>& mesh)
{
	this->mesh = mesh;
}

void MeshRender::Render()
{
	if (mesh != nullptr && m_material != nullptr)
	{
		m_material->BindOnGpu();
		mesh->Render();
	}
}