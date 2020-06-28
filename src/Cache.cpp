#include "Cache.h"
#include "Utilities.h"

namespace histech {


Cache::~Cache()
{
	if (!m_Finished)
	{
		Done();
	}
	delete m_List;
}

void Cache::AddPicture(const long SlideID, const long XCoord, const long YCoord, const long DataSize, void* Picture)
{
	if (!m_Finished)
	{
		Node* found = m_List->FindNode(SlideID, XCoord, YCoord);
		if (found)
		{
			return;
		}

		if (m_CurrentOffset + DataSize > m_MaxSize)
		{
			// LOG here
			unsigned char* newData = new unsigned char[m_MaxSize * 2];
			memcpy(m_Data, newData, m_MaxSize);
			m_MaxSize *= 2;

			delete[] m_Data;
			m_Data = newData;
		}

		m_List->AddNode(SlideID, XCoord, YCoord, DataSize, m_CurrentOffset);

		memcpy(static_cast<unsigned char*>(Picture), m_Data + m_CurrentOffset, DataSize);

		m_CurrentOffset += DataSize;
	}
	else
	{
		// Print some proper error message and use return codes instead of throwing in production
		throw 0;
	}
}

void Cache::GetPicture(const long SlideID, const long XCoord, const long YCoord, void** Picture)
{
	if (!m_Finished)
	{
		Node* found = m_List->FindNode(SlideID, XCoord, YCoord);
		
		memcpy(m_Data + found->m_ByteOffset, static_cast<unsigned char*>(*Picture), found->m_SizeInBytes);
	}
	else
	{
		// Print some proper error message and use return codes instead of throwing in production
		throw 0;
	}
}

void Cache::DeletePicture(const long SlideID, const long XCoord, const long YCoord)
{
	if (!m_Finished)
	{
		m_List->RemoveNode(SlideID, XCoord, YCoord);
	}
	else
	{
		// Print some proper error message and use return codes instead of throwing in production
		throw 0;
	}
}

void Cache::DeleteAllBySlideID(const long SlideID)
{
	if (!m_Finished)
	{
		while (auto found = m_List->FindNodeWithSlideID(SlideID))
		{
			m_List->RemoveNode(found->m_SlideID, found->m_XCoord, found->m_YCoord);
		}
	}
	else
	{
		// Print some proper error message and use return codes instead of throwing in production
		throw 0;
	}
}

void Cache::DeleteAll()
{
	if (!m_Finished)
	{
		delete[] m_Data;
		m_Data = new unsigned char[m_MaxSize];
	}
	else
	{
		// Print some proper error message and use return codes instead of throwing in production
		throw 0;
	}
}
}  // namespace histech
