#pragma once

typedef void(*EXIT)(void);

// ΩÃ±€≈Ê ≈¨∑°Ω∫ ≈€«√∏¥
template<typename T>
class Singleton
{
private:
	static T* instance;

public:
	static T* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new T;
			atexit((EXIT)&Singleton<T>::Destroy);
		}
		return instance;
	}

private:
	static void Destroy()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}
};

template<typename T> T* Singleton<T>::instance = nullptr;

// ΩÃ±€≈Ê ≈¨∑°Ω∫ ¡§¿« ∏≈≈©∑Œ
#define SINGLETON(TYPE) private:\
							TYPE();\
							TYPE(const TYPE&) = delete;\
							~TYPE();\
							TYPE& operator=(const TYPE&) = delete;\
							friend class Singleton;