#include "Cache.h"
#include "Picture.h"

using namespace histech;

int main()
{
    // Add and delete picture test
    {
        Cache cache;
        cache.Init(1024);

        Picture pic(2);
        Picture pic2(3);
        Picture pic3(2);
        Picture pic4(4);

        cache.AddPicture(0, 0, 0, pic.m_Size, pic.m_Data);
        cache.AddPicture(0, 0, 1, pic2.m_Size, pic2.m_Data);
        cache.AddPicture(0, 0, 2, pic3.m_Size, pic3.m_Data);
        cache.AddPicture(0, 0, 3, pic4.m_Size, pic4.m_Data);

        cache.DeletePicture(0, 0, 1);

        if (!cache.AssertContents(2, 2, 3))
        {
            throw 0;
        }
    }

    // Delete all from a given slide, and adding a new image test
    {
        Cache cache;
        cache.Init(1024);

        Picture pic(2);
        Picture pic2(3);
        Picture pic3(2);
        Picture pic4(4);
        Picture pic5(5);

        cache.AddPicture(1, 0, 0, pic.m_Size, pic.m_Data);
        cache.AddPicture(1, 0, 1, pic2.m_Size, pic2.m_Data);
        cache.AddPicture(1, 0, 2, pic3.m_Size, pic3.m_Data);
        cache.AddPicture(0, 0, 3, pic4.m_Size, pic4.m_Data);

        cache.DeleteAllBySlideID(1);

        cache.AddPicture(0, 0, 4, pic5.m_Size, pic5.m_Data);

        if (!cache.AssertContents(0, 4, 8) || !cache.AssertContents(4, 5, 9))
        {
            throw 0;
        }
    }

    // Get picture test
    {
        Cache cache;
        cache.Init(1024);

        Picture pic(2);
        Picture pic2(3);
        Picture pic3(2);
        Picture pic4(4);

        cache.AddPicture(0, 0, 0, pic.m_Size, pic.m_Data);
        cache.AddPicture(0, 0, 1, pic2.m_Size, pic2.m_Data);
        cache.AddPicture(0, 0, 2, pic3.m_Size, pic3.m_Data);
        cache.AddPicture(0, 0, 3, pic4.m_Size, pic4.m_Data);

        cache.DeletePicture(0, 0, 0);

        cache.GetPicture(0, 0, 1, reinterpret_cast<void**>(&pic2.m_Data));
        if (!pic2.AssertContent(11))
        {
            throw 0;
        }
    }

    //if (false)
    //{
    //    Picture pic(2);
    //    Picture pic2(3);
    //    Picture pic3(2);
    //    Picture pic4(4);
    //    Picture pic5(5);

    //    Cache cache;

    //    cache.Init(8192);


    //    cache.AddPicture(0, 0, 0, pic.m_Size, pic.m_Data);
    //    cache.AddPicture(0, 0, 1, pic2.m_Size, pic2.m_Data);
    //    cache.AddPicture(0, 0, 2, pic3.m_Size, pic3.m_Data);
    //    cache.AddPicture(0, 0, 4, pic4.m_Size, pic4.m_Data);
    //    cache.AddPicture(0, 0, 5, pic5.m_Size, pic5.m_Data);

    //    cache.DeletePicture(0, 0, 1);
    //    cache.DeletePicture(0, 0, 2);

    //    cache.AddPicture(0, 0, 5, pic5.m_Size, pic5.m_Data);
    //    cache.AddPicture(0, 0, 6, pic5.m_Size, pic5.m_Data);
    //    cache.AddPicture(0, 0, 7, pic5.m_Size, pic5.m_Data);

    //    //cache.DeleteAllBySlideID(0);

    //    cache.GetPicture(0, 0, 2, reinterpret_cast<void**>(&pic.m_Data));
    //}


    return 0;
}