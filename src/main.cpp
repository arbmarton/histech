#include "Cache.h"
#include "Picture.h"

using namespace histech;

int main()
{
    Picture pic(2);
    Picture pic2(3);
    Picture pic3(2);
    Picture pic4(4);
    Picture pic5(5);

    Cache cache;

    cache.Init(2048);


    cache.AddPicture(0, 0, 0, pic.m_Size, pic.m_Data);
    cache.AddPicture(0, 0, 1, pic2.m_Size, pic2.m_Data);
    cache.AddPicture(0, 0, 2, pic3.m_Size, pic3.m_Data);
    cache.AddPicture(0, 0, 4, pic4.m_Size, pic4.m_Data);

    cache.DeletePicture(0, 0, 0);
    cache.DeletePicture(0, 0, 1);

    cache.AddPicture(0, 0, 5, pic5.m_Size, pic5.m_Data);

    //cache.DeleteAllBySlideID(0);

    cache.GetPicture(0, 0, 2, reinterpret_cast<void**>(&pic.m_Data));

    return 0;
}