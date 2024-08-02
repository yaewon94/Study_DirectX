#pragma once
#include "Entity.h"

// 에셋 최상위 클래스
class Asset : public Entity
{
private:
	wstring key;
	wstring relativePath;

public:
	const wstring& GetKey() { return key; }
	
protected:
	Asset(const wstring& key, const wstring& relativePath);
	~Asset();

protected:	// 삭제
	Asset(const Asset&) = delete;
	virtual Asset* Clone() final { return nullptr; }
};