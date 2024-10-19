#include "pch.h"
#include "Shader.h"

Shader::Shader(const string& key, const string& relativePath) 
	: Asset(key, relativePath)
{
}

Shader::~Shader()
{
}