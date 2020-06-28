#pragma once

namespace histech
{

template<typename T>
void memcpy(T* from, T* to, long size)
{
	for (int i = 0; i < size; ++i)
	{
		to[i] = from[i];
	}
}

template<typename T>
void memset(T* from, long size, const T val)
{
	for (int i = 0; i < size; ++i)
	{
		from[i] = val;
	}
}

}