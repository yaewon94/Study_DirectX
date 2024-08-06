#include "pch.h"
#include "Shader.h"

Shader::Shader(ASSET_TYPE Type, const wstring& key, const wstring& relativePath) 
	: Asset(Type, key, relativePath)
{
}

Shader::~Shader()
{
}
