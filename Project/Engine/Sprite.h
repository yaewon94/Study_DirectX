#pragma once
#include "Asset.h"

class Texture;

// 2D 이미지
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
	void SetAtlasTexture(const Ptr<Texture>& atlas, UINT frameCount);
	UINT GetFrameCount() { return m_frameCount; }
	void SetFrameCount(UINT frameCount);

	bool IsRepeat() { return m_isRepeat; }
	void SetRepeatOnOff() { m_isRepeat = !m_isRepeat; }
	UINT GetFPS() { return m_fps; }
	void SetFPS(int fps)
	{
		if (fps <= 0 || fps > 60)
		{
			throw std::logic_error("fps값은 1 이상 60 이하만 가능합니다");
		}

		m_fps = fps;
	}

public:
	virtual int Load() final { return S_OK; }

public:
	void BindOnGpu(UINT curIndex);
	void Clear();
};