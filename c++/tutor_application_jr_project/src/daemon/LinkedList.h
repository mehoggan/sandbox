#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;

#ifndef LINKED
#define LINKED
template <typename T> class Node 
{
	public:
		Node();
		Node(T);
		~Node();
		Node<T>*& getNext();
		void setNext(Node<T>*);
		T getData();
	private:
		T data;
		Node<T>* next;
};

template <typename T> Node<T>::Node() 
{
}

template <typename T> Node<T>::Node(T info) 
{
	data = info;
	next = NULL;
}

template <typename T> Node<T>::~Node() 
{
}

template <typename T> Node<T>*& Node<T>::getNext() 
{
	return next;
}

template <typename T> void Node<T>::setNext(Node<T>* nextNode) 
{
	next = nextNode;
}

template <typename T> T Node<T>::getData() 
{
	return data;
}

/*-------------------------------------------------------------------------------*/

template <typename T> class LinkedList 
{
	public:
		LinkedList();
		~LinkedList();
		void InsertTail(T);
		void InsertHead(T);
		void Delete(T);
		void DeleteHead();
		Node<T>* getHead();
		void Display();
		bool Search(T);
		int getSize();
	private:
		Node<T>* head;
		int size;
};

template <typename T> LinkedList<T>::LinkedList() 
{
	head = NULL;
	size = 0;
}

template <typename T> LinkedList<T>::~LinkedList() 
{
	if(head == NULL) 
	{
	}
	else 
	{
		Node<T>* slider = head;
		Node<T>* trail = slider;
		while(slider != NULL)
		{
			trail = slider;
			slider = slider->getNext();
			delete trail;
		}
	}
}

template <typename T> void LinkedList<T>::InsertTail(T info) {
	if(head == NULL) 
	{
		Node<T>* data = new Node<T>(info);
		head = data;
		size++;
	}
	else 
	{
		Node<T>* data = new Node<T>(info);
		Node<T>* slider = head;
		while(slider->getNext() != NULL) 
		{
			slider = slider->getNext();
		}
		slider->setNext(data);
		size++;
	}
}

template <typename T> void LinkedList<T>::InsertHead(T info) 
{
	if(head == NULL) 
	{
		Node<T>* data = new Node<T>(info);
		head = data;
		size++;
	}
	else 
	{
		Node<T>* data = new Node<T>(info);
		data->setNext(head);
		head = data;
		size++;
	}
}

template <typename T> void LinkedList<T>::Delete(T info) 
{
	if(head == NULL) 
	{
	}
	else 
	{
		Node<T>* slider = head;
		while(slider != NULL && slider->getNext()->getData() != info) 
		{
			slider = slider->getNext();
		}
		if(slider != NULL) slider->setNext(slider->getNext()->getNext());
		size--;
	}
}

template <typename T> void LinkedList<T>::DeleteHead() 
{
	if(head == NULL) 
	{
	}
	else 
	{
		head = head->getNext();
		size--;
	}
}

template <typename T> Node<T>* LinkedList<T>::getHead() 
{
	return head;
}

template <typename T> void LinkedList<T>::Display() 
{
	if(head == NULL) 
	{
	}
	else 
	{
		fstream file_Out("X:\\Matthew\\CSUN\\Final Project\\EditMemberList\\Output\\Output1.txt", ios::out);
		Node<T>* slider = head;
		while(slider != NULL) 
		{
			file_Out << slider->getData() << endl;
			slider = slider->getNext();
		}
		file_Out.close();
	cout << endl << endl;
	}
}

template <typename T> bool LinkedList<T>::Search(T item) 
{
	bool ret = false;
	if(head == NULL) 
	{
	}
	else 
	{
		Node<T>* slider = head;
		while(slider != NULL && slider->getData() != item) 
		{
			slider = slider->getNext();
		}
		if(slider != NULL) ret = true;
	}
	return ret;
}

template <typename T> int LinkedList<T>::getSize() 
{
	return size;
}
#endif
