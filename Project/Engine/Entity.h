#pragma once

// 오브젝트, 컴포넌트, 에셋 등의 최상위 클래스
// TODO : 추상클래스로 만들기
class Entity
{
private:
	static UINT nextID;

private:
	const UINT ID;
	UINT refCount;	// 해당 개체를 참조 중인 스마트 포인터 수

public:
	UINT GetID() { return ID; }

protected:
	Entity();
	Entity(const Entity& origin);
	virtual ~Entity();

private:
	// 스마트 포인터로만 객체 생성하도록 강제
	//template<typename T> requires std::derived_from<T,Entity> friend class Ptr;
	template<typename T> friend class Ptr;

	void AddRefCount() { ++refCount; }
	void Release() { if (--refCount == 0) delete this; }

	void* operator new(size_t size) { return ::operator new(size); }
	void* operator new[](size_t) = delete;
	void operator delete(void* ptr) { ::operator delete(ptr); }
	void operator delete[](void*) = delete;
};