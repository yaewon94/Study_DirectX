#include "pch.h"
#include "MeshRender.h"
#include "GameObject.h"
#include "Mesh.h"
#include "GraphicShader.h"
#include "Texture.h"

MeshRender::MeshRender(const Ptr<GameObject>& owner) : Component(owner)
{
}

MeshRender::MeshRender(const Ptr<Component>& origin, const Ptr<GameObject>& owner)
	: Component(origin, owner)
{
	auto ptr = origin.ptr_dynamic_cast<MeshRender>();
	mesh = ptr->mesh;
	shader = ptr->shader;
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

void MeshRender::SetTexture(const Ptr<Texture>& texture)
{
	this->texture = texture;
	this->texture->BindOnGpu(0);	// TODO : 레지스터 넘버 상수변수로 받기
}

void MeshRender::Render()
{
	if (mesh!=nullptr)
	{
		mesh->BindOnGpu();
		mesh->Render();
	}
}