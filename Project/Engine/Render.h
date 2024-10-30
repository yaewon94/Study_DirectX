#pragma once

// �̸�
#define RENDER_TARGET_TEX_NAME "RenderTargetTex"
#define DEPTH_STENCIL_TEX_NAME "DepthStencilTex"

// ����
#define COLOR_WHITE Vec4(1.f, 1.f, 1.f, 1.f)
#define COLOR_RED Vec4(1.f, 0.f, 0.f, 1.f)
#define COLOR_GREEN Vec4(0.f, 1.f, 0.f, 1.f)

// �������
#define BUFFER_SIZE_UNIT 16 // �������,����ȭ���� �ּ� ���� (����Ʈ)

// ======================
// Texture
// ======================
// �ؽ�ó Ÿ�� (value : �������� ��ȣ)
enum TEXTURE_PARAM
{
	NULL_PARAM = -1,	// �������� �Ҵ� ���� ��
	TEX_0, TEX_1, TEX_2, TEX_3, TEX_4, TEX_5,
	TEXARR_0, TEXARR_1, TEXARR_2, TEXARR_3,
	CUBE_0, CUBE_1,
	//SPRITE_TEX,
	COUNT_END,
	SPRITE_TEX = 12,	// ���� : �� COUNT_END == 13�̸� ���ܶ�?
	LIGHT_2D = 13,
	TILEMAP = 16,
};


// =======================
// Const Buffer
// =======================
// ��� ���� Ÿ�� (value : �������� ��ȣ)
enum class CB_TYPE : UINT
{
	TRANSFORM, MATERIAL, SPRITE, GLOBAL, COUNT_END
};

// ���� �������
struct CB_Global
{
	Vec2 renderResolution;

	float dt;
	float totalTime;

	float dt_engine;
	float totalTime_engine;

	int Light2dCount;
	int Light3dCount;
};

// ���� ������� (�� �ʵ带 ������ �������Ϳ� ���ε�)
struct CB_Material
{
	int iArr[4];
	float fArr[4];
	Vec2 v2Arr[4];
	Vec4 v4Arr[4];
	Matrix matrixArr[2];
	int bTex[TEXTURE_PARAM::COUNT_END];
};

// ��������Ʈ �̹��� �������
struct CB_Sprite
{
	Vec2 leftTopUV;
	Vec2 sliceUV;
	Vec2 backgroundUV;
	Vec2 offsetUV;
	int isUsed;
	int padding[3];
};

// �Ķ���� Ÿ�� (Material ���� ���)
enum SCALAR_PARAM
{
	INT_0, INT_1, INT_2, INT_3,
	FLOAT_0, FLOAT_1, FLOAT_2, FLOAT_3,
	VEC2_0, VEC2_1, VEC2_2, VEC2_3,
	VEC4_0, VEC4_1, VEC4_2, VEC4_3,
	MATRIX_0, MATRIX_1
};

// ������Ʈ�� ��ġ,ũ��,ȸ���� �������
struct CB_Transform
{
	//Vec4 pos;
	//Vec4 scale;
	Matrix worldMatrix;
	Matrix viewMatrix;
	Matrix projMatrix;

	Matrix wv;	// world * view
	Matrix wvp;	// world * view * projection
};

// ======================
// Shader
// ======================
// ���̴� ���� �з� (value : ������ ����)
enum class SHADER_DOMAIN
{
	DOMAIN_OPAQUE = 0,	// ������
	DOMAIN_MASK,		// ������ or ����
	DOMAIN_TRANSPARENT,	// ������ + ����
	DOMAIN_POSTPROCESS,	// ��ó��
	COUNT_END
};

static const char* ShaderDomainArr[] = {"Opaque", "Mask", "Transparent", "Postprocess"};
static constexpr byte ShaderDomainArrSize = sizeof(ShaderDomainArr) / sizeof(const char*);

// �����Ͷ����� Ÿ��
enum class RASTERIZE_TYPE
{
	// culling : ������Ʈ���� �ʿ���� �κ��� ������ ���� �ʰ� �ϴ� ��� 
	CULL_NONE = 0,
	CULL_BACK,	// �޸� �ø� (DEFAULT)
	CULL_FRONT,	// �ո� �ø�
	WIRE_FRAME,	// ���̾� ������
	COUNT_END
};

static const char* RsArr[] = { "None", "Cull back", "Cull front", "Wireframe" };
static constexpr byte RsArrSize = sizeof(RsArr) / sizeof(const char*);

// Blend State
enum class BLEND_TYPE
{
	DEFAULT = 0,		// �������
	ALPHABLEND,			// ���İ� ����
	ALPHABLEND_COVERAGE,// ���ĺ��� + AlphaToCoverage
	ONE_ONE,			// 1:1 ����
	COUNT_END
};

static const char* BsArr[] = { "Default", "Alphablend", "Alphablend coverage", "1 : 1" };
static constexpr byte BsArrSize = sizeof(BsArr) / sizeof(const char*);

// �������� Ÿ��
enum class DEPTH_STENCIL_TYPE
{
	LESS = 0,
	LESS_EQUAL,
	GREATER,		// �����ִ� ����
	NO_TEST,		// �������� X
	NO_WRITE,		// �������� LESS, ��� X
	NO_TEST_WRITE,	// �������� X, ��� X
	COUNT_END
};

static const char* DsArr[] = { "Less", "Less equal", "Greater", "No test", "No write", "No test No write" };
static constexpr byte DsArrSize = sizeof(DsArr) / sizeof(const char*);

// ���ø� Ÿ��
enum class SAMPLER_TYPE : UINT
{
	AF,							// �̹漺 ���͸�
	MIN_MAG_POINT_MIP_LINEAR,	// Minification, Magnification Mipmap ���� ���͸�
	COUNT_END
};

#ifdef _DEBUG
// ======================
// Debug
// ======================
// ����� ��� shape
enum class DEBUG_SHAPE
{
	RECT, CIRCLE, CROSS, LINE
};

// ����� ��� ����
struct DebugShapeInfo
{
	DEBUG_SHAPE shape;
	Vec3 pos, scale, rotation;
	Vec4 color;

	//const float Duration;
	//float curTime = 0.f;

	bool hasDepthTest = false;	// �������� ���� ����
};
#endif	// _DEBUG

// ==============================
// �ܺκ���
// ==============================
extern CB_Global g_global;
extern CB_Transform g_transform;