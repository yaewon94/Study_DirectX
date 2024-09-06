#include "pch.h"
#include "Material.h"
#include "Device.h"
#include "ConstBuffer.h"
#include "GraphicShader.h"
#include "Texture.h"

Material::Material(const wstring& Key, const wstring& relativePath) 
	: Asset(Key, relativePath), m_cb{}
{
}

Material::~Material()
{
}

void Material::BindOnGpu()
{
	if (m_shader != nullptr)
	{
		// Texture
		for (int i=0; i<TEXTURE_PARAM::COUNT_END; ++i)
		{
			if(m_textures[i] != nullptr)
			{
				m_cb.bTex[i] = 1;
				m_textures[i]->BindOnGpu((TEXTURE_PARAM)i);
			}
		}

		// Const Buffer
		static Ptr<ConstBuffer> cb = Device::GetInstance()->GetConstBuffer(CB_TYPE::MATERIAL);
		cb->SetData(&m_cb);
		cb->BindOnGpu();

		// Shader
		m_shader->BindOnGpu();
	}
}

void Material::SetShader(const Ptr<GraphicShader>& shader)
{
	m_shader = shader;
}

void Material::SetTextureParam(TEXTURE_PARAM type, const Ptr<Texture>& texture)
{
	m_textures[type] = texture;
}

void Material::UnloadTexture(TEXTURE_PARAM param)
{
	if (m_textures[param] == nullptr)
	{
		throw std::logic_error("empty 레지스터 입니다");
	}

	TEXTURE_PARAM registerNum = m_textures[param]->GetRegisterNum();
	m_cb.bTex[registerNum] = 0;
	m_textures[param]->Clear();
	m_textures[param] = nullptr;
}