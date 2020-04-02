#pragma once

template <typename T>
class singletonBase
{
protected:
	static T* singleton;

	singletonBase() {}
	~singletonBase() {}

public:
	static T* getSingleton();
	void ReleaseSingleton();

};

//ΩÃ±€≈Ê √ ±‚»≠
template<typename T>
T* singletonBase<T>::singleton = 0;


template<typename T>
T * singletonBase<T>::getSingleton()
{
	if (!singleton) singleton = new T;

	return singleton;
}

template<typename T>
void singletonBase<T>::ReleaseSingleton()
{
	if (singleton)
	{
		delete singleton;
		singleton = 0;
	}
}
