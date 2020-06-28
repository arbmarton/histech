#pragma once

namespace histech {

template <typename T>
void memcpy(T* from, T* to, const long size)
{
    for (long i = 0; i < size; ++i)
    {
        to[i] = from[i];
    }
}

template <typename T, typename R>
void memset(T* from, const long size, const R val)
{
    for (long i = 0; i < size; ++i)
    {
        from[i] = val;
    }
}

}  // namespace histech