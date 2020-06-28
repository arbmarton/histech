#include "List.h"
#include "Utilities.h"
#include "Cache.h"

namespace histech {

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
    Node* newNode = new Node{ SlideID, XCoord, YCoord, Size, ByteOffset, nullptr };
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

RemoveData List::RemoveNode(const long SlideID, const long XCoord, const long YCoord)
{
    Node* found = FindNode(SlideID, XCoord, YCoord);
    if (!found)
    {
        return {};
    }

    const long foundOffset = found->m_ByteOffset;
    const long foundSize = found->m_SizeInBytes;

    if (found != m_Head)
    {
        // Find the previous node and modify its next
        Node* prev = m_Head;
        while (prev->m_Next != found)
        {
            prev = prev->m_Next;
        }

        prev->m_Next = found->m_Next;

        if (found == m_Tail)
        {
            delete found;
            return {};
        }
    }
    else
    {
        // If its the first one just set the head to the second element
        m_Head = found->m_Next;
    }

    // Calculate how many bytes we need to move, also modify the nodes' byte offset as we go
    long accum = -found->m_SizeInBytes;
    Node* iter = found;
    while (iter != nullptr)
    {
        accum += iter->m_SizeInBytes;
        iter->m_ByteOffset -= foundSize;
        iter = iter->m_Next;
    }

    delete found;

    // Return the offset data, so that the Cache can move the elements properly
    return { foundOffset, foundSize, accum };
}

Node* List::FindNode(const long SlideID, const long XCoord, const long YCoord) const
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

Node* List::FindFirstNodeWithSlideID(const long SlideID) const
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

}  // namespace histech