#pragma once

// 오브젝트, 컴포넌트, 에셋 등의 최상위 클래스
class Entity
{
private:
	static UINT nextID;

private:
	const UINT ID;
	wstring name;
	UINT refCount;	// 해당 개체를 참조 중인 스마트 포인터 수

public:
	UINT GetID() { return ID; }

	const wstring& GetName() { return name; }
	void SetName(const wstring& name) { this->name = name; }

protected:
	Entity();
	Entity(const wstring& name);
	Entity(const Entity& origin);
	virtual ~Entity();

protected:
	virtual Entity* Clone() = 0;

private:
	template<typename T> requires std::derived_from<T,Entity> friend class Ptr;
	void AddRefCount() { ++refCount; }
	void Release()
	{
		assert(refCount > 0);
		if (--refCount == 0) delete this;
	}
};