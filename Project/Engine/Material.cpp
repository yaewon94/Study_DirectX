#include "pch.h"
#include "Material.h"
#include "Device.h"
#include "ConstBuffer.h"
#include "GraphicShader.h"
#include "Texture.h"

Material::Material(const string& Key, const string& relativePath) 
	: Asset(Key, relativePath), m_cb{}
{
}

Material::Material(const Material& origin) : Asset("", "")
{
	*this = origin;
}

Material::~Material()
{
}

Material& Material::operator=(const Material& other)
{
	if (this != &other)
	{
		// �ּ� ���� (�����̹Ƿ� �������� X)
		m_shader = other.m_shader;
		m_textures = other.m_textures;

		// ���� �ּ�
		m_cb = other.m_cb;
	}

	return *this;
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

Ptr<GraphicShader> Material::GetShader()
{
	return m_shader;
}

void Material::SetShader(const Ptr<GraphicShader>& shader)
{
	m_shader = shader;

	// ���ĺ��� Ÿ���� ���, ������ 100%�� �ʱ�ȭ
	if (m_shader->GetBlendType() == BLEND_TYPE::ALPHABLEND
		|| m_shader->GetBlendType() == BLEND_TYPE::ALPHABLEND_COVERAGE)
	{
		SetAlpha(1.f);
	}
}

void Material::SetAlpha(float alpha)
{
	if (m_shader->GetBlendType() == BLEND_TYPE::ALPHABLEND 
		|| m_shader->GetBlendType() == BLEND_TYPE::ALPHABLEND_COVERAGE)
	{
		if (alpha < 0.f || alpha > 1.f)
		{
			throw std::logic_error("0.f �̻� 1.f ������ ���� �����մϴ�");
		}

		m_cb.fArr[0] = alpha;
	}
	else
	{
		throw std::logic_error("���ĺ��� Ÿ�Ը� ���İ��� ������ �� �ֽ��ϴ�");
	}
}

void Material::SetTextureParam(TEXTURE_PARAM type, const Ptr<Texture>& texture)
{
	m_textures[type] = texture;
}

void Material::UnloadTexture(TEXTURE_PARAM param)
{
	if (m_textures[param] == nullptr)
	{
		throw std::logic_error("empty �������� �Դϴ�");
	}

	m_cb.bTex[param] = 0;
	m_textures[param]->Clear(param);
	m_textures[param] = nullptr;
}