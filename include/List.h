#pragma once

namespace histech {

class Cache;

struct Node
{
    long m_SlideID{ -1 };
    long m_XCoord{ -1 };
    long m_YCoord{ -1 };

    long m_SizeInBytes{ -1 };
    long m_ByteOffset{ -1 };

    Node* m_Next;
};

struct RemoveData
{
    long m_Offset{ -1 };
    long m_Size{ -1 };
    long m_BytesToMove{ -1 };
};

class List
{
public:
    List() = default;
    List(const List& rhs) = delete;
    List(List&& rhs) = delete;
    List& operator=(const List& rhs) = delete;
    List& operator=(List&& rhs) = delete;
    ~List();

    void AddNode(const long SlideID, const long XCoord, const long YCoord, const long Size, const long ByteOffset);
    [[nodiscard]] RemoveData RemoveNode(const long SlideID, const long XCoord, const long YCoord);

    Node* FindNode(const long SlideID, const long XCoord, const long YCoord) const;
    Node* FindFirstNodeWithSlideID(const long SlideID) const;

private:
    Node* m_Head{ nullptr };
    Node* m_Tail{ nullptr };
};
}  // namespace histech