#pragma once

// cpp
#include <stdexcept>
#include <concepts>

// �ڷᱸ��
#include <vector>
using std::vector;
#include <list>
using std::list;
#include <map>
using std::map;
using std::make_pair;

// ���ڿ�
#include <string>
using std::string;
using std::wstring;

// DirectX 11
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

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

// ComPtr
#include <wrl.h>
using namespace Microsoft::WRL;

// ����� ���� ���
#include "Singleton.h"
#include "Message.h"
#include "Ptr.h"