#include "pch.h"
#include "Material.h"
#include "Device.h"
#include "ConstBuffer.h"
#include "GraphicShader.h"
#include "Texture.h"

Material::Material(const string& Key, const string& relativePath) 
	: Asset(Key, relativePath), m_cb{}, m_copy(1)
{
}

Material::Material(const Material& origin) 
	: Asset(origin.GetKey() + "##" + std::to_string(++m_copy), "")
	, m_copy(1)
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
		// 주소 공유 (에셋이므로 깊은복사 X)
		m_shader = other.m_shader;
		m_texMap = other.m_texMap;

		// 개별 주소
		m_cb = other.m_cb;
	}

	return *this;
}

void Material::BindOnGpu()
{
	if (m_shader != nullptr)
	{
		// Texture
		for (auto& pair : m_texMap)
		{
			m_cb.bTex[pair.first] = 1;
			pair.second->BindOnGpu(pair.first);
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
	if (m_shader.Get() == shader.Get()) return;

	m_shader = shader;

	// 알파블렌드 타입일 경우, 불투명도 100%로 초기화
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
			throw std::logic_error("0.f 이상 1.f 이하의 값만 가능합니다");
		}

		m_cb.fArr[0] = alpha;
	}
	else
	{
		throw std::logic_error("알파블렌딩 타입만 알파값을 설정할 수 있습니다");
	}
}

Ptr<Texture> Material::GetTexture(TEXTURE_PARAM type)
{
	const auto iter = m_texMap.find(type);

	if (iter != m_texMap.end()) return iter->second;
	else return nullptr;
}

void Material::SetTextureParam(TEXTURE_PARAM type, const Ptr<Texture>& texture)
{
	if (type < 0) throw std::logic_error("type은 양수만 가능합니다");
	if (type >= TEXTURE_PARAM::COUNT_END) throw std::logic_error("전용 파라미터는 사용할 수 없습니다");

	const auto iter = m_texMap.find(type);

	if (iter != m_texMap.end())
	{
		if (texture == nullptr)
		{
			m_cb.bTex[type] = 0;
			iter->second->Clear(type);
			m_texMap.erase(iter);
		}
		else
		{
			iter->second = texture;
		}
	}
	else
	{
		if(texture != nullptr) m_texMap.insert(make_pair(type, texture));
	}
}