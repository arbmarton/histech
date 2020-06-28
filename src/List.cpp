#include "List.h"
#include "Utilities.h"
#include "Cache.h"

namespace histech
{

List::~List()
{
	Node* next = m_Head;

	while (next)
	{
		Node* temp = next;
		next = next->m_Next;
		delete temp;
	}
}

void List::AddNode(const long SlideID, const long XCoord, const long YCoord, const long Size, const long ByteOffset)
{
	Node* newNode = new Node{SlideID, XCoord, YCoord, Size, ByteOffset, nullptr};
	if (!m_Head)
	{
		m_Head = newNode;
		m_Tail = newNode;
	}
	else
	{
		m_Tail->m_Next = newNode;
		m_Tail = newNode;
	}
}

void List::RemoveNode(const long SlideID, const long XCoord, const long YCoord)
{
	Node* found = FindNode(SlideID, XCoord, YCoord);
	if (!found)
	{
		return;
	}

	const long foundOffset = found->m_ByteOffset;
	const long foundSize = found->m_SizeInBytes;

	if (found != m_Head)
	{
		// Find the previous node
		Node* prev = m_Head;
		while (prev->m_Next != found)
		{
			prev = prev->m_Next;
		}

		prev->m_Next = found->m_Next;

		if (found == m_Tail)
		{
			delete found;
			return;
		}
	}
	else
	{
		m_Head = found->m_Next;
	}


	long accum = -found->m_SizeInBytes;
	Node* iter = found;
	while (iter != nullptr)
	{
		accum += iter->m_SizeInBytes;
		iter->m_ByteOffset -= foundSize;
		iter = iter->m_Next;
	}

	memcpy(m_ParentCache->m_Data + foundOffset + foundSize, m_ParentCache->m_Data + foundOffset, accum);
	m_ParentCache->m_CurrentOffset -= foundSize;
	delete found;
}

Node* List::FindNode(const long SlideID, const long XCoord, const long YCoord)
{
	auto* curr = m_Head;

	while (curr)
	{
		if (curr->m_SlideID == SlideID && curr->m_XCoord == XCoord && curr->m_YCoord == YCoord)
		{
			return curr;
		}

		curr = curr->m_Next;
	}

	return nullptr;
}

Node* List::FindNodeWithSlideID(const long SlideID)
{
	Node* iter = m_Head;
	while (iter)
	{
		if (iter->m_SlideID == SlideID)
		{
			return iter;
		}
		iter = iter->m_Next;
	}

	return nullptr;
}

}