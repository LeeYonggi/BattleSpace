#pragma once

template<class T>
class Singleton
{
public:
	Singleton() {}
	virtual ~Singleton() {}

private:
	static T *p;

public:
	static T *GetInstance()
	{
		if (!p)
			p = new T;
		return p;
	}
	static void ReleaseInstance()
	{
		if (p)
			delete p;
	}
};

template<class T>
T *Singleton<T>::p = nullptr;
