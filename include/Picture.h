#pragma once

#include "Utilities.h"

namespace histech {

class Picture
{
public:
    Picture() = delete;
    Picture(long size)
        : m_Size(size)
    {
        // Use this static member for testing the contents
        static int counter = 1;

        m_Data = new unsigned char[size];
        memset(m_Data, size, counter);

        counter++;
    }
    Picture(const Picture& rhs) = delete;
    Picture(Picture&& rhs) = delete;
    Picture& operator=(const Picture& rhs) = delete;
    Picture& operator=(Picture&& rhs) = delete;
    ~Picture()
    {
        delete[] m_Data;
    }

    bool AssertContent(const long Val) const
    {
        for (long i = 0; i < m_Size; ++i)
        {
            if (m_Data[i] != Val)
            {
                return false;
            }
        }

        return true;
    }

    long m_Size;
    unsigned char* m_Data;
};

}  // namespace histech