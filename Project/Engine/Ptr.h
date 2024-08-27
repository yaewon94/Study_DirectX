#pragma once
//#include "Entity.h"

// 스마트 포인터 템플릿
/*
// 헤더파일 순환참조 문제 발생
//template<typename T> requires std::derived_from<T, Entity>
*/
template<typename T>
class Ptr final
{
private:
	T* t;

public:
	T* const Get() { return t; }
	T** const GetAddressOf() { return &t; }

public:
	// 깡통만들기 or 디폴트 생성자 있는 객체 생성할 때 호출
	Ptr() : t(nullptr)
	{
		if constexpr (std::is_constructible_v<T>) t = new T;
	}

	// @ param : 생성할 객체의 생성자 파라미터
	template<typename... Args>
	Ptr(Args... args) : t(nullptr)
	{
		if constexpr (std::is_constructible_v<T, Args...>)
		{
			t = new T(args...);
		}
	}

	// args==nullptr인 Ptr(args...) 호출 방지
	Ptr(nullptr_t) : t(nullptr)
	{
	}

	// @ param : 참조할 객체
	Ptr(T* const t) : t(t)
	{
		if (t != nullptr) t->AddRefCount();
	}

	// 복사생성자 (lValue)
	Ptr(const Ptr& origin) : t(nullptr)
	{
		*this = origin;
	}

	// 복사생성자 (rValue)
	Ptr(Ptr&& origin) noexcept : t(nullptr)
	{
		*this = origin;
	}

	// 소멸자
	~Ptr()
	{
		if (t != nullptr)
		{
			t->Release();
			t = nullptr;
		}
	}

public:
	// 대입연산자 (lValue)
	Ptr& operator=(const Ptr& other)
	{
		if (t != nullptr)
		{
			t->Release();
			t = nullptr;
		}

		if (other.t != nullptr)
		{
			t = other.t;
			t->AddRefCount();
		}

		return *this;
	}

	// 대입연산자 (rValue)
	Ptr& operator=(Ptr&& other) noexcept
	{
		if (t != nullptr)
		{
			t->Release();
			t = nullptr;
		}

		if (other.t != nullptr)
		{
			t = other.t;
			t->AddRefCount();

			other.t->Release();
			other.t = nullptr;
		}

		return *this;
	}

	// 비교 연산자 (==)
	bool operator==(nullptr_t)
	{
		if (this == nullptr || t == nullptr) return true;
		else return false;
	}

	// 비교 연산자 (!=)
	bool operator!=(nullptr_t)
	{
		if (this == nullptr || t == nullptr) return false;
		else return true;
	}

	// 포인터 참조 연산자
	T* const operator->()
	{
		if (t == nullptr) throw std::logic_error(MSG_NULLPTR_EXCEPTION);
		return t;
	}

	// 스마트포인터 형변환
	template<typename U>
	Ptr<U> ptr_dynamic_cast()
	{
		if (t == nullptr) return nullptr;
		else if (dynamic_cast<U*>(t) != nullptr) return Ptr<U>((U*)t);
		else return nullptr;
	}

public:
	// nullptr 대입 방지 (초기화만 가능)
	Ptr& operator=(nullptr_t) = delete;

	// 동적할당,해제 방지
	void* operator new(size_t) = delete;
	void* operator new[](size_t) = delete;
	void operator delete(void*) = delete;
	void operator delete[](void*) = delete;
};