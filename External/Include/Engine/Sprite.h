#pragma once
#include "Asset.h"

class Texture;

// 2D ¿ÃπÃ¡ˆ
class Sprite final : public Asset
{
	NO_COPY_ASSIGN(Sprite);

public:
	static const ASSET_TYPE Type = ASSET_TYPE::SPRITE;

private:
	Ptr<Texture> m_atlas;
	Vec2 m_sliceUV;
	Vec2 m_backgroundUV;
	UINT m_frameCount;
	UINT m_fps;
	bool m_isRepeat;

public:
	Sprite(const string& Key, const string& RelativePath);
	~Sprite();

public:
	virtual ASSET_TYPE GetType() final { return Type; }
	Ptr<Texture> GetAtlasTexture();
	UINT GetFPS() { return m_fps; }
	UINT GetFrameCount() { return m_frameCount; }
	bool IsRepeat() { return m_isRepeat; }

	void SetAtlasTexture(const Ptr<Texture>& atlas, UINT frameCount);

public:
	virtual int Load() final { return S_OK; }

public:
	void BindOnGpu(UINT curIndex);
	void Clear();
};