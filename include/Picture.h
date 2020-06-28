#pragma once

namespace histech
{

class Picture
{
public:
	Picture() = delete;
	Picture(long size)
		: m_Size(size)
	{
		static int counter = 1;

		m_Data = new unsigned char[size];
		for (int i = 0; i < size; ++i)
		{
			m_Data[i] = counter;
		}

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
	
	long m_Size;
	unsigned char* m_Data;
};

}