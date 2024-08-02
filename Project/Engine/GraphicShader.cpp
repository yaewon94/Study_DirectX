#include "pch.h"
#include "GraphicShader.h"
#include "Device.h"

GraphicShader::GraphicShader(const wstring& key, const wstring& relativePath) 
	: Shader(key, relativePath)
	, topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
}

GraphicShader::~GraphicShader()
{
}

int GraphicShader::Create(const string& vertexFuncName, const string& pixelFuncName)
{
	// ===============
	// Vertex Shader
	// ===============
	// 셰이더 파일 컴파일
	UINT flag = D3DCOMPILE_DEBUG;
	HRESULT result = S_OK;

	result = D3DCompileFromFile(GetPath().c_str()
		, nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, vertexFuncName.c_str()
		, VERTEX_SHADER_VER
		, flag
		, 0
		, vertexShaderBlob.GetAddressOf()
		, errorBlob.GetAddressOf());

	if (FAILED(result))
	{
		errno_t errNum = GetLastError();
		
		if (errNum == 2 || errNum == 3)
		{
			MessageBoxA(nullptr, "셰이더 파일 존재하지 않음", "버텍스 셰이더 컴파일 실패", MB_OK);
		}
		else
		{
			MessageBoxA(nullptr, (char*)errorBlob->GetBufferPointer(), "버텍스 셰이더 컴파일 실패", MB_OK);
		}

		return E_FAIL;
	}

	// 셰이더 객체 생성
	DEVICE->CreateVertexShader(vertexShaderBlob->GetBufferPointer()
		, vertexShaderBlob->GetBufferSize()
		, nullptr
		, vertexShader.GetAddressOf());

	// ==============
	// Vertex Shader Input Layout
	// ==============
	D3D11_INPUT_ELEMENT_DESC layoutDesc[3] = {};

	layoutDesc[0].AlignedByteOffset = 0;
	layoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	layoutDesc[0].InputSlot = 0;
	layoutDesc[0].InputSlotClass - D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[0].InstanceDataStepRate = 0;
	layoutDesc[0].SemanticName = "POSITION";
	layoutDesc[0].SemanticIndex = 0;

	layoutDesc[1].AlignedByteOffset = 12;
	layoutDesc[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	layoutDesc[1].InputSlot = 0;
	layoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[1].InstanceDataStepRate = 0;
	layoutDesc[1].SemanticName = "TEXCOORD";
	layoutDesc[1].SemanticIndex = 0;

	layoutDesc[2].AlignedByteOffset = 20;
	layoutDesc[2].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	layoutDesc[2].InputSlot = 0;
	layoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	layoutDesc[2].InstanceDataStepRate = 0;
	layoutDesc[2].SemanticName = "COLOR";
	layoutDesc[2].SemanticIndex = 0;

	if (FAILED(DEVICE->CreateInputLayout(layoutDesc
		, 3
		, vertexShaderBlob->GetBufferPointer()
		, vertexShaderBlob->GetBufferSize()
		, layout.GetAddressOf())))
	{
		return E_FAIL;
	}

	// ===============
	// Pixel Shader
	// ===============
	// 셰이더 파일 컴파일
	result = D3DCompileFromFile(GetPath().c_str()
		, nullptr
		, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, pixelFuncName.c_str()
		, PIXEL_SHADER_VER
		, flag
		, 0
		, pixelShaderBlob.GetAddressOf()
		, errorBlob.GetAddressOf());

	if (FAILED(result))
	{
		errno_t errNum = GetLastError();

		if (errNum == 2 || errNum == 3)
		{
			MessageBoxA(nullptr, "셰이더 파일 존재하지 않음", "픽셀 셰이더 컴파일 실패", MB_OK);
		}
		else
		{
			MessageBoxA(nullptr, (char*)errorBlob->GetBufferPointer(), "픽셀 셰이더 컴파일 실패", MB_OK);
		}

		return E_FAIL;
	}

	// 셰이더 객체 생성
	DEVICE->CreatePixelShader(pixelShaderBlob->GetBufferPointer()
		, pixelShaderBlob->GetBufferSize()
		, nullptr
		, pixelShader.GetAddressOf());

	return S_OK;
}

void GraphicShader::Bind()
{
	// Input Assembler
	CONTEXT->IASetPrimitiveTopology(topology);
	CONTEXT->IASetInputLayout(layout.Get());

	// Vertex Shader Stage
	CONTEXT->VSSetShader(vertexShader.Get(), nullptr, 0);

	// Pixel Shader Stage
	CONTEXT->PSSetShader(pixelShader.Get(), nullptr, 0);
}