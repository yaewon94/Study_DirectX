#pragma once

// 오브젝트, 컴포넌트, 에셋 등의 최상위 클래스
class Entity
{
private:
	static UINT nextID;

private:
	const UINT ID;
	wstring name;

public:
	UINT GetID() { return ID; }
	const wstring& GetName() { return name; }
	void SetName(const wstring& name) { this->name = name; }

protected:
	Entity();
	Entity(const wstring& name);
	Entity(const Entity& origin);
	~Entity();

protected:
	virtual Entity* Clone() = 0;
};