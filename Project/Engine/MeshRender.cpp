#include "pch.h"
#include "MeshRender.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Material.h"

MeshRender::MeshRender(const Ptr<GameObject>& owner) : Component(owner)
{
}

MeshRender::MeshRender(const Ptr<Component>& origin, const Ptr<GameObject>& owner)
	: Component(origin, owner)
{
	auto ptr = origin.ptr_dynamic_cast<MeshRender>();
	mesh = ptr->mesh;
	material = ptr->material;
}

MeshRender::~MeshRender()
{
}

void MeshRender::SetMesh(const Ptr<Mesh>& mesh)
{
	this->mesh = mesh;
}

void MeshRender::SetMaterial(const Ptr<Material>& material)
{
	this->material = material;
}

Ptr<Material> MeshRender::GetMaterial()
{
	return material;
}

void MeshRender::Render()
{
	if (mesh != nullptr && material != nullptr)
	{
		material->BindOnGpu();
		mesh->Render();
	}
}