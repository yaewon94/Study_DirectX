#pragma once
#include "Asset.h"
#include "Render.h"

class GraphicShader;
class Texture;

// ����
class Material final : public Asset
{
public:
	static const ASSET_TYPE Type = ASSET_TYPE::MATERIAL;

private:
	Ptr<GraphicShader> m_shader;
	array<Ptr<Texture>, TEXTURE_PARAM::COUNT_END> m_textures;
	CB_Material m_cb;

public:
	Material(const string& Key, const string& relativePath);
	Material(const Material& origin);
	~Material();
	Material& operator=(const Material& other);

public:
	void BindOnGpu();
	virtual int Load() final { return S_OK; }

public:
	virtual ASSET_TYPE GetType() final { return Type; }

	// shader
	Ptr<GraphicShader> GetShader();
	void SetShader(const Ptr<GraphicShader>& shader);
	void SetAlpha(float alpha);
	void SetColor(Vec4 color) { m_cb.v4Arr[0] = color; }

	// texture
	void SetTextureParam(TEXTURE_PARAM type, const Ptr<Texture>& texture);
	void UnloadTexture(TEXTURE_PARAM type);

	template<typename T>
	void SetScalarParam(SCALAR_PARAM type, const T& data)
	{
		switch (type)
		{
		case INT_0:
		case INT_1:
		case INT_2:
		case INT_3:
			if constexpr (std::is_same_v<T, int>) m_cb.iArr[type] = data;
			else throw std::logic_error("�Ķ���� Ÿ���� int�� �ƴմϴ�");
			break;

		case FLOAT_0:
		case FLOAT_1:
		case FLOAT_2:
		case FLOAT_3:
			if constexpr (std::is_same_v<T, float>) m_cb.fArr[type - FLOAT_0] = data;
			else throw std::logic_error("�Ķ���� Ÿ���� float�� �ƴմϴ�");
			break;

		case VEC2_0:
		case VEC2_1:
		case VEC2_2:
		case VEC2_3:
			if constexpr (std::is_same_v<T, Vec2>) m_cb.v2Arr[type - VEC2_0] = data;
			else throw std::logic_error("�Ķ���� Ÿ���� Vec2�� �ƴմϴ�");
			break;

		case VEC4_0:
		case VEC4_1:
		case VEC4_2:
		case VEC4_3:
			if constexpr (std::is_same_v<T, Vec4>) m_cb.v4Arr[type - VEC4_0] = data;
			else throw std::logic_error("�Ķ���� Ÿ���� Vec4�� �ƴմϴ�");
			break;

		case MATRIX_0:
		case MATRIX_1:
			if constexpr (std::is_same_v<T, Matrix>) m_cb.matrixArr[type - MATRIX_0] = data;
			else throw std::logic_error("�Ķ���� Ÿ���� Matrix�� �ƴմϴ�");
			break;

		default:
			throw std::logic_error("���ǵ��� ���� SCALAR_PARAM Ÿ�� �Դϴ�");
		}
	}
};