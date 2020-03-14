#pragma once

#include "stdafx.h"
template <typename T>
class CList
{
	class Node
	{
	public:
		T data;
		Node* _Prev;
		Node* _Next;
	public:
		Node(T data = 0)
		{
			this->data = data;
			_Prev = _Next = nullptr;
		}
	};

	int _size = 0;
	Node* head;
	Node* tail;

public:
	class iterator
	{
	private :
		Node* _node;
		friend class CList;
	public:
		iterator(Node* node = 0)
		{
			this->_node = node;
		}

		const T& operator *()
		{
			return _node->data;
		}

		operator Node* ()
		{
			return _node;
		}

		iterator& operator ++()
		{
			_node = _node->_Next;
			return (*this);
		}

		iterator& operator --()
		{
			_node = _node->_Prev;
			return (*this);
		}

		const iterator operator++(int)
		{
			iterator temp(*this);
			_node = _node->_Next;
			return temp;
		}

		const iterator operator--(int)
		{
			iterator temp(*this);
			_node = _node->_Prev;
			return temp;
		}

		bool operator !=(const iterator& iter) const
		{
			return _node != iter._node;
		}

		bool operator ==(const iterator& iter) const
		{
			return _node == iter._node;
		}
	};

	typedef iterator const_iterator;

public:
	CList()
	{
		head = new Node();
		tail = new Node();
		head->_Next = tail;
		tail->_Prev = head;
		_size = 0;
	}

	~CList()
	{
		clear();
		delete head;
		delete tail;
	}

	void push_back(T data)
	{
		insert(end(), data);
	}

	void insert(iterator itor, T data)
	{
		Node* newNode = new Node(data);
		Node* temp = itor;

		newNode->_Next = temp;
		newNode->_Prev = temp->_Prev;
		temp->_Prev->_Next = newNode;
		temp->_Prev = newNode;

		_size++;
	}

	void clear()
	{
		iterator iter(begin());
		for (iter; iter != end(); )
		{
			iter = erase(iter);
		}
	}

	iterator erase(iterator it)	
	{

		if (_size > 0)
		{
			Node* pPos = it._node;
			if (pPos->_Prev)
				pPos->_Prev->_Next = pPos->_Next;
			if (pPos->_Next)
				pPos->_Next->_Prev = pPos->_Prev;

			Node* pCurrnet = pPos->_Next;
			delete pPos;
			it = pCurrnet;
			_size--;
		}
		return it;
	}

	iterator begin()
	{
		iterator it(head->_Next);
		return it;
	}

	iterator end()
	{
		iterator it(tail);
		return it;
	}

	const_iterator begin()const
	{
		iterator iter(head->next);
		return iter;
	}
	
	const_iterator end()const
	{
		iterator iter(tail);
		return iter;
	}

	int GetSize()
	{
		return this->_size;
	}
};









