#pragma once

// 스마트 포인터를 사용할 클래스의 인터페이스
class IPtrReleasable
{
private:
	UINT refCount;	// 해당 개체를 참조 중인 스마트 포인터 수

protected:
	IPtrReleasable() : refCount(1) {}

	IPtrReleasable(const IPtrReleasable& origin)
	{
		*this = origin;
	}

	IPtrReleasable(IPtrReleasable&& origin) noexcept
	{
		*this = std::move(origin);
	}

	virtual ~IPtrReleasable()
	{
		if (refCount > 0) throw std::logic_error("해당 객체를 아직 참조중 입니다");
	}

	IPtrReleasable& operator=(const IPtrReleasable& other)
	{
		refCount = 1;
		return *this;
	}

	IPtrReleasable& operator=(IPtrReleasable&& other) noexcept
	{
		other.refCount = 0;
		refCount = 1;
		return *this;
	}

private:
	// 스마트 포인터로만 객체 생성하도록 강제
	template<typename T> friend class Ptr;

	void AddRefCount() { ++refCount; }
	void Release() { if (--refCount == 0) delete this; }

	void* operator new(size_t size) { return ::operator new(size); }
	void* operator new[](size_t) = delete;
	void operator delete(void* ptr) { ::operator delete(ptr); }
	void operator delete[](void*) = delete;
};


// 스마트 포인터 클래스
template<typename T>
class Ptr final
{
private:
	T* t;

public:
	T* Get() const { return t; }

public:
	// 복사생성자 호출
	Ptr DeepCopy() const
	{
		if constexpr (std::is_copy_constructible_v<T>)
		{
			Ptr<T> clone = Ptr<T>(nullptr);
			clone.t = new T(*t);
			return clone;
		}

		throw std::logic_error("해당 클래스의 복사생성자가 없거나 접근할 수 없습니다");
	}

public:
	// 초기화 용도 깡통만들기 or 디폴트 생성자 있는 객체 생성할 때 호출
	Ptr() : t(nullptr)
	{
		if constexpr (std::is_abstract_v<T>) throw std::logic_error("추상클래스의 객체를 생성할 수 없습니다");
		
		if constexpr (std::is_constructible_v<T>) t = new T;
	}

	// @ param : 생성할 객체의 생성자 파라미터
	template<typename... Args>
	Ptr(Args... args) : t(nullptr)
	{
		if constexpr (std::is_constructible_v<T, Args...>) t = new T(args...);
		else throw std::logic_error("해당 파라미터를 가진 생성자가 존재하지 않거나 접근할 수 없습니다");
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
		*this = std::move(origin);
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

	// 대입연산자 (nullptr_t)
	nullptr_t operator=(nullptr_t)
	{
		if (t != nullptr)
		{
			t->Release();
			t = nullptr;
		}

		return nullptr;
	}
		
	// 비교 연산자 (==)
	bool operator==(nullptr_t) const
	{
		if (this == nullptr || t == nullptr) return true;
		else return false;
	}

	// 비교 연산자 (!=)
	bool operator!=(nullptr_t) const
	{
		if (this == nullptr || t == nullptr) return false;
		else return true;
	}

	// 포인터 참조 연산자
	T* const operator->() const
	{
		if (t == nullptr) throw std::logic_error(MSG_NULLPTR_EXCEPTION);
		return t;
	}

	// 스마트포인터 형변환
	template<typename U>
	Ptr<U> ptr_dynamic_cast() const
	{
		if (t == nullptr) return nullptr;
		else if (dynamic_cast<U*>(t) != nullptr) return Ptr<U>((U*)t);
		else return nullptr;
	}

public:
	// 동적할당,해제 방지
	void* operator new(size_t) = delete;
	void* operator new[](size_t) = delete;
	void operator delete(void*) = delete;
	void operator delete[](void*) = delete;

	// 자동 형변환 방지
	template<typename U>
	operator Ptr<U>() const = delete;
};