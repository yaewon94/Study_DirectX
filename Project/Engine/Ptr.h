#pragma once
#include "Entity.h"

// 스마트 포인터 템플릿
template <typename T> requires std::derived_from<T, Entity>
class Ptr final
{
private:
	T* ptr;

public:
	Ptr();
	Ptr(nullptr_t) = delete;
	Ptr(T* ptr);
	Ptr(const Ptr& origin);
	~Ptr();

public:
	T* Get() const { if (ptr == nullptr) throw std::exception(MSG_NULLPTR_EXCEPTION); return ptr; }
	T** GetAddressOf() const { if (ptr == nullptr) throw std::exception(MSG_NULLPTR_EXCEPTION); return &ptr; }

public:
	Ptr& operator=(const Ptr& other);
	T* operator->() const { if (ptr == nullptr) throw std::exception(MSG_NULLPTR_EXCEPTION); return ptr; }
	bool operator==(const Ptr& other);
	bool operator!=(const Ptr& other);
};

template<typename T> requires std::derived_from<T, Entity>
inline Ptr<T>::Ptr() : ptr(nullptr)
{
}

template<typename T> requires std::derived_from<T, Entity>
inline Ptr<T>::Ptr(T* ptr) : ptr(nullptr)
{
	if (ptr == nullptr) throw std::exception(MSG_NULLPTR_EXCEPTION);

	this->ptr = ptr;
	this->ptr->AddRefCount();
}

template<typename T> requires std::derived_from<T, Entity>
inline Ptr<T>::Ptr(const Ptr& origin) : ptr(nullptr)
{
	*this = origin;
}

template<typename T> requires std::derived_from<T, Entity>
inline Ptr<T>::~Ptr()
{
	if (ptr != nullptr)
	{
		ptr->Release();
		ptr = nullptr;
	}
}

template<typename T> requires std::derived_from<T, Entity>
inline Ptr<T>& Ptr<T>::operator=(const Ptr& other)
{
	if (other.ptr == nullptr) throw std::exception(MSG_NULLPTR_EXCEPTION);

	if (*this != other)
	{
		if(ptr != nullptr) ptr->Release();
		ptr = other.ptr;
		ptr->AddRefCount();
	}

	return *this;
}

template<typename T> requires std::derived_from<T, Entity>
inline bool Ptr<T>::operator==(const Ptr& other)
{
	if (ptr != nullptr && other.ptr != nullptr)
	{
		if (&ptr == &other.ptr)
		{
			return true;
		}
	}

	return false;
}

template<typename T> requires std::derived_from<T, Entity>
inline bool Ptr<T>::operator!=(const Ptr& other)
{
	return !(*this == other);
}