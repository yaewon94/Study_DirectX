#include "pch.h"
#include "Sprite.h"
#include "Device.h"
#include "ConstBuffer.h"
#include "Texture.h"

Sprite::Sprite(const wstring& Key, const wstring& RelativePath)
	: Asset(Key, RelativePath)
	, m_frameCount(0)
	, m_fps(1.f)
	, m_isRepeat(true)
{
}

Sprite::~Sprite()
{
}

Ptr<Texture> Sprite::GetAtlasTexture()
{
	return m_atlas;
}

void Sprite::SetAtlasTexture(const Ptr<Texture>& atlas, UINT frameCount)
{
	// 필드 초기화
	m_atlas = atlas;
	m_frameCount = frameCount;
	m_sliceUV = Vec2(1.f / m_frameCount, 1.f);
}

void Sprite::BindOnGpu(UINT curIndex)
{
	Ptr<ConstBuffer> cb = Device::GetInstance()->GetConstBuffer(CB_TYPE::SPRITE);
	CB_Sprite info = {};

	m_atlas->BindOnGpu(TEXTURE_PARAM::SPRITE_TEX);

	info.leftTopUV = Vec2(curIndex / (float)m_frameCount, 0.f);
	info.sliceUV = m_sliceUV;
	info.isUsed = true;

	cb->SetData(&info);
	cb->BindOnGpu();
}

void Sprite::Clear()
{
	Ptr<ConstBuffer> cb = Device::GetInstance()->GetConstBuffer(CB_TYPE::SPRITE);
	CB_Sprite info = {};

	cb->SetData(&info);
	cb->BindOnGpu();

	m_atlas->Clear();
}