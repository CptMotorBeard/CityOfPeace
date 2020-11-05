#pragma once
#ifndef SRC_SINGLETON_H
#define SRC_SINGLETON_H
template <class T>
class Singleton
{
public:
	static T& Instance()
	{
		static T instance;
		return instance;
	}

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(const Singleton&&) = delete;
	Singleton& operator=(const Singleton&&) = delete;

protected:
	Singleton() {};
};
#endif // !SRC_SINGLETON_H