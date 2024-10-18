#pragma once

// cpp
#include <stdexcept>
#include <concepts>

// 자료구조
#include <array>
using std::array;
#include <vector>
using std::vector;
#include <list>
using std::list;
#include <map>
using std::map;
using std::make_pair;
#include <unordered_map>
using std::unordered_map;
#include <unordered_set>
using std::unordered_set;

// 문자열
#include <string>
using std::string;
using std::wstring;

// ComPtr
#include <wrl.h>
using namespace Microsoft::WRL;

// DirectX 11
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXTex/DirectXTex.h>

using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

#include "SimpleMath.h"
typedef DirectX::SimpleMath::Vector2 Vec2;
typedef DirectX::SimpleMath::Vector3 Vec3;
typedef DirectX::SimpleMath::Vector4 Vec4;
typedef DirectX::SimpleMath::Matrix Matrix;

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex\\DirectXTex_debug")
#else
#pragma comment(lib, "DirectXTex\\DirectXTex")
#endif

// 사용자 정의 헤더
#include "CommonTypes.h"
#include "DesignPatternDefine.h"
#include "Singleton.h"
#include "Message.h"
#include "Ptr.h"