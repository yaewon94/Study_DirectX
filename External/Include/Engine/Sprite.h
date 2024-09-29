#pragma once
#include "Asset.h"

class Texture;

// 2D ¿ÃπÃ¡ˆ
class Sprite final : public Asset
{
	NO_COPY_ASSIGN(Sprite);

private:
	Ptr<Texture> m_atlas;
	Vec2 m_sliceUV;
	UINT m_frameCount;
	UINT m_fps;
	bool m_isRepeat;

public:
	Sprite(const wstring& Key, const wstring& RelativePath);
	~Sprite();

public:
	Ptr<Texture> GetAtlasTexture();
	void SetAtlasTexture(const Ptr<Texture>& atlas, UINT frameCount);
	UINT GetFPS() { return m_fps; }
	UINT GetFrameCount() { return m_frameCount; }
	bool IsRepeat() { return m_isRepeat; }

public:
	virtual int Load() final { return S_OK; }

public:
	void BindOnGpu(UINT curIndex);
	void Clear();
};