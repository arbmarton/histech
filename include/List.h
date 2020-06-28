#pragma once

namespace histech
{

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

class List
{
public:
	List(Cache* ParentCache)
		: m_ParentCache(ParentCache)
	{
	}
	~List();

	void AddNode(const long SlideID, const long XCoord, const long YCoord, const long Size, const long ByteOffset);
	void RemoveNode(const long SlideID, const long XCoord, const long YCoord);

	Node* FindNode(const long SlideID, const long XCoord, const long YCoord);
	Node* FindNodeWithSlideID(const long SlideID);

private:
	Cache* m_ParentCache;
	Node* m_Head{ nullptr };
	Node* m_Tail{ nullptr };
};
}