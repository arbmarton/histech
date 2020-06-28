#pragma once

#include "List.h"

namespace histech {


class Cache
{
    friend class List;
public:
    Cache() = default;
    Cache(const Cache& rhs) = delete;
    Cache(Cache&& rhs) = delete;
    Cache& operator=(const Cache& rhs) = delete;
    Cache& operator=(Cache&& rhs) = delete;
    ~Cache();

    void Init(const long MaxCacheSizeInByte)
    {
        m_Initialized = true;
        m_MaxSize = MaxCacheSizeInByte;

        m_Data = new unsigned char[MaxCacheSizeInByte];
    }

    void Done()
    {
        delete[] m_Data;
        m_Finished = true;
    }

    void AddPicture(const long SlideID, const long XCoord, const long YCoord, const long DataSize, void* Picture);

    void GetPicture(const long SlideID, const long XCoord, const long YCoord, void** Picture);

    void DeletePicture(const long SlideID, const long XCoord, const long YCoord);
    void DeleteAllBySlideID(const long SlideID);
    void DeleteAll();


    
private:
    bool m_Initialized{ false };
    bool m_Finished{ false };
    long m_MaxSize;
    long m_CurrentOffset{ 0 };

    List* m_List = new List(this);

    unsigned char* m_Data{ nullptr };
};
}  // namespace histech
