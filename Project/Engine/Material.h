#pragma once
#include "Asset.h"
#include "Render.h"

class GraphicShader;
class Texture;

// 재질
class Material final : public Asset
{
	NO_COPY_ASSIGN(Material);

private:
	Ptr<GraphicShader> m_shader;
	array<Ptr<Texture>, TEXTURE_PARAM::COUNT_END> m_textures;
	CB_Material m_cb;

public:
	Material(const wstring& Key, const wstring& relativePath);
	~Material();

public:
	void BindOnGpu();
	virtual int Load() final { return S_OK; }

public:
	Ptr<GraphicShader> GetShader();

	void SetShader(const Ptr<GraphicShader>& shader);
	void SetTextureParam(TEXTURE_PARAM type, const Ptr<Texture>& texture);
	void UnloadTexture(TEXTURE_PARAM type);

	template<typename T>
	void SetScalarParam(SCALAR_PARAM type, const T& data)
	{
		if constexpr (std::is_same_v<T, int>) m_cb.iArr[type] = data;
		else if constexpr (std::is_same_v<T, float>) m_cb.fArr[type - FLOAT_0] = data;
		else if constexpr (std::is_same_v<T, Vec2>) m_cb.v2Arr[type - VEC2_0] = data;
		else if constexpr (std::is_same_v<T, Vec4>) m_cb.v4Arr[type - VEC4_0] = data;
		else if constexpr (std::is_same_v<T, Matrix>) m_cb.matrixArr[type - MATRIX_0] = data;
		else throw std::logic_error("정의되지 않은 SCALAR_PARAM 타입 입니다");
	}
};