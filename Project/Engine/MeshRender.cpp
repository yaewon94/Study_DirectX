#include "pch.h"
#include "MeshRender.h"
#include "GameObject.h"
#include "Mesh.h"
#include "GraphicShader.h"

MeshRender::MeshRender(const Ptr<GameObject>& owner) : Component(owner)
{
}

MeshRender::MeshRender(const MeshRender& origin, const Ptr<GameObject>& owner)
	: Component(origin, owner)
	, mesh(origin.mesh)
	, shader(origin.shader)
{
}

MeshRender::~MeshRender()
{
}

void MeshRender::SetMesh(const Ptr<Mesh>& mesh)
{
	this->mesh = mesh;
}

void MeshRender::SetShader(const Ptr<GraphicShader>& shader)
{
	this->shader = shader;
}

void MeshRender::Render()
{
	if (mesh!=nullptr && shader!=nullptr)
	{
		shader->BindOnGpu();
		mesh->Render();
	}
}