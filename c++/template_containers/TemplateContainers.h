#include <cstdio>
#include <iostream>

using namespace std;
#ifndef CONTAIN
#define CONTAIN
/********************************************************	Node Class	************************************************************************/
namespace containers 
{
	template <typename T> class Node 
	{
		public:
			Node();
			Node(T);
			~Node();
			Node<T>* getNext();
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

	template <typename T> Node<T>* Node<T>::getNext() 
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

/********************************************************	Linked List Class	******************************************************************/

	template <typename T> class LinkedList 
	{
		public:
			LinkedList();
			~LinkedList();
			void Insert(T);
			void Delete(T);
			void Display();			

		private:
			Node<T>* head;
	};

	template <typename T> LinkedList<T>::LinkedList() 
	{
		head = NULL;
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

	template <typename T> void LinkedList<T>::Insert(T info) 
	{
		if(head == NULL) 
		{
			Node<T>* data = new Node<T>(info);
			head = data;
		}
		else 
		{
			cout << "INSERTING " << info << "... " << endl; 
			Node<T>* data = new Node<T>(info);
			Node<T>* slider = head;
			while(slider->getNext() != NULL) 
			{
				slider = slider->getNext();
			}
			slider->setNext(data);
		}
	}	

	template <typename T> void LinkedList<T>::Delete(T info) 
	{
		if(head == NULL) 
		{
		}
		else 
		{
			cout << "DELETING " << info << "... " << endl;
			Node<T>* slider = head;
			while(slider != NULL && slider->getNext()->getData() != info) 
			{
				slider = slider->getNext();
			}
			if(slider != NULL) cout << "Found your value " << info << " and DELETING IT" << "\n";
			if(slider != NULL) slider->setNext(slider->getNext()->getNext());
		}
	}		

	template <typename T> void LinkedList<T>::Display() 
	{
		if(head == NULL) 
		{
		}
		else 
		{
			Node<T>* slider = head;
			while(slider != NULL) 
			{
				cout << slider->getData() << " ";
				slider = slider->getNext();
			}
			cout << endl << endl;
		}
	}

/********************************************************	TreeNode Implements Node	******************************************************/

	template <typename T> class TreeNode:Node<T> 
	{
		public:
			TreeNode();
			TreeNode(T);
			~TreeNode();
			TreeNode<T>* getRightBr();
			TreeNode<T>* getLeftBr();
			void setLeftBr(TreeNode<T>*);
			void setRightBr(TreeNode<T>*);
			T getData();	

		private:
			T data;
			TreeNode<T>* leftBr;
			TreeNode<T>* rightBr;
	};

	template <typename T> TreeNode<T>::TreeNode() 
	{
	}

	template <typename T> TreeNode<T>::TreeNode(T info) 
	{
		data = info;
		leftBr = NULL;
		rightBr = NULL;
	}

	template <typename T> TreeNode<T>::~TreeNode() 
	{
	}

	template <typename T> TreeNode<T>* TreeNode<T>::getRightBr() 
	{
		return rightBr;	
	}

	template <typename T> TreeNode<T>* TreeNode<T>::getLeftBr() 
	{
		return leftBr;
	}

	template <typename T> void TreeNode<T>::setLeftBr(TreeNode<T>* left) 
	{
		leftBr = left;
	}

	template <typename T> void TreeNode<T>::setRightBr(TreeNode<T>* right) 
	{
		rightBr = right;
	}

	template <typename T> T TreeNode<T>::getData() 
	{
		return data;
	}

/********************************************************	BST Class	************************************************************************/

	template <typename T> class BST 
	{
		private:
			TreeNode<T>* root;
			T data;
			void rec_Delete(TreeNode<T>*);
			void rec_Display(TreeNode<T>*);
			TreeNode<T>* rec_Remove(TreeNode<T>*, T);	

		public:
			BST();
			~BST();
			void InsertLeaf(T data);
			void Remove(T data);
			void Display();
	};

	template <typename T> BST<T>::BST() 
	{
		root = NULL;
	}


	template <typename T> BST<T>::~BST() 
	{
		if(root == NULL) 
		{
		}
		else 
		{	
			cout << "Deleting Tree " << endl;
			TreeNode<T>* trim = root;
			rec_Delete(trim);
			delete root;	
			}
	}

	template <typename T> void BST<T>::Remove(T data)
	{
		if(root == NULL)
		{
			cout << "There was no tree to delete from" << endl;
		}
		else
		{
			cout << "Going to remove " << data << endl;
			root = rec_Remove(root, data);
		}
	}	

	template <typename T> TreeNode<T>* BST<T>::rec_Remove(TreeNode<T>* retrn, T data)
	{
		if(retrn == NULL)
		{
			cout << "Your data was not found";
		}
		else
		{
			if(data < retrn->getData())
			{
				cout << "Making left recursive call to " << retrn->getLeftBr()->getData() << endl;
				retrn->setLeftBr(rec_Remove(retrn->getLeftBr(), data));
			}
			else if(data > retrn->getData())
			{
				cout << "Making right recursive call to " << retrn->getRightBr()->getData() << endl;
				retrn->setRightBr(rec_Remove(retrn->getRightBr(), data));
			}
			else
			{
				cout << "Your data " << data << " was found" << endl;
				if(retrn->getRightBr() == NULL && retrn->getLeftBr() == NULL)
				{
					delete retrn;
				}
				else if(retrn->getLeftBr() != NULL && retrn->getRightBr() == NULL)
				{
					retrn = retrn->getLeftBr();
				}
				else if(retrn->getLeftBr() == NULL && retrn->getRightBr() != NULL)
				{
					retrn = retrn->getRightBr();
				}
				else if(retrn->getLeftBr() != NULL && retrn->getRightBr() != NULL)
				{
					cout << "At special case, " << data << " has two children" << endl;
					TreeNode<T>* replacement = retrn;
					TreeNode<T>* aboveReplace = replacement;
					replacement = replacement->getRightBr();
					while(replacement->getLeftBr() != NULL)
					{
						aboveReplace = replacement;
						replacement = replacement->getLeftBr();
					}
					if(aboveReplace == retrn)
					{	
						replacement->setLeftBr(retrn->getLeftBr());
						retrn = replacement;	
					}
					else if(replacement->getRightBr() == NULL)
					{
						retrn = replacement;
						replacement->setRightBr(retrn->getRightBr());
					}
					else if(replacement->getRightBr() != NULL)
					{
						TreeNode<T>* temp = retrn;
						while(temp->getRightBr() != NULL)
						{
							temp = temp->getRightBr();
						}
						temp->setRightBr(replacement->getRightBr());
						retrn = replacement;
						replacement->setRightBr(retrn->getRightBr());
						aboveReplace->setLeftBr(temp->getRightBr());
						temp = NULL;					
					}
				}
			}
		}
		return retrn;
	}

	template <typename T> void BST<T>::InsertLeaf(T data) 	
	{
		if(root == NULL) 
		{
			cout << "Inserting at root " << endl;
			TreeNode<T>* info = new TreeNode<T>(data);		
			root = info;
			cout << "Root now points to value " << root->getData() << endl;
		}
		else 
		{
			TreeNode<T>* info = new TreeNode<T>(data);
			TreeNode<T>* grafter = root;
			TreeNode<T>* helper = grafter;
			bool insert = true;
			while(grafter != NULL) 
			{
				if(data < grafter->getData()) 
				{
					helper = grafter;
					grafter = grafter->getLeftBr();
				}
				else if(data > grafter->getData()) 
				{
					helper = grafter;
					grafter = grafter->getRightBr();
				}
				else if(data == grafter->getData()) 
				{
					insert = false;
				}
			}
			if(insert) 
			{
				if(data < helper->getData()) 
				{
					helper->setLeftBr(info);
				}
				else if(data > helper->getData()) 
				{
					helper->setRightBr(info);
				}
				else 
				{
					cout << "Could not insert your data" << endl;
					delete info;
				}
			}
		}
	}	

	template <typename T> void BST<T>::Display() 
	{
		if(root == NULL) 
		{
		}
		else 
		{
			TreeNode<T>* roger = root;
			rec_Display(roger);
		}
	}
	
	template <typename T> void BST<T>::rec_Display(TreeNode<T>* roger) 
	{
		if(roger == NULL) 
		{
		}
		else 
		{
			rec_Display(roger->getLeftBr());
			cout << roger->getData() << endl;
			rec_Display(roger->getRightBr());
		}
	}


	template <typename T> void BST<T>::rec_Delete(TreeNode<T>* trim) 
	{
		if(trim == NULL) 
		{
		}
		else 
		{
			rec_Delete(trim->getLeftBr());
			rec_Delete(trim->getRightBr());
			cout << "Deleting " << trim->getData() << endl;
			delete trim;
		}
	}

/********************************************************	AVL Trees Inherits From BST	******************************************************/

	template <typename T> class AVLTree:BST<T> 
	{
		private:
			TreeNode<T>* root;
			T data;
			void rec_Delete(TreeNode<T>*);
			void rec_Display(TreeNode<T>*);
			TreeNode<T>* rec_Remove(TreeNode<T>*, T);	

		public:
			AVLTree();
			~AVLTree();
			void InsertLeaf(T data);
			void Remove(T data);
			void Display();
	};
}
#endif