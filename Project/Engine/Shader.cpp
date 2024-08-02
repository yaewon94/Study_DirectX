#include "pch.h"
#include "Shader.h"

Shader::Shader(const wstring& key, const wstring& relativePath) 
	: Asset(key, L"Shader\\" + relativePath)
{
}

Shader::~Shader()
{
}
