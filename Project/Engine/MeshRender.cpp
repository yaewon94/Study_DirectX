#include "pch.h"
#include "MeshRender.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

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

Ptr<Mesh> MeshRender::GetMesh()
{
	return mesh;
}

void MeshRender::SetMesh(const Ptr<Mesh>& mesh)
{
	this->mesh = mesh;
}

void MeshRender::Render()
{
	if (mesh != nullptr && m_material != nullptr)
	{
		GetOwner()->GetTransform()->BindOnGpu();
		m_material->BindOnGpu();
		mesh->Render();
	}
}