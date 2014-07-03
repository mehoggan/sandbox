/*
 *	Matthew Hoggan
 *	Fall 2010
 *	Josephus Permutation
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <fstream>

using namespace std;

ofstream myfile("output.txt");
int Total_People = 2000000;
int Skip = 2;
int Start = 2;

class Circle_Linked_List{
public:
	class Node	{
	public:
		Node(){
		}
		Node(int value){
			next = NULL;
			per = value;
		}
		~Node(){
		}
		Node* next;
		int per;
	};

	Circle_Linked_List(){
		root = NULL;
		count = 0;
	}

	~Circle_Linked_List(){
		if(root == NULL){
		}
		else{
			myfile << setw(7) << root->per;
			delete root;
			root = NULL;
		}
	}

	void Print_Count(){
	}

	void Insert(int value){
		Node* insert = new Node(value);
		if(root == NULL){
			root = insert;
			tail = insert;
			count++;
		}
		else{
			tail->next = insert;
			tail = insert;
			count++;
		}
	}

	void Make_Circle(){
		Node* slider = root;
		while(slider->next != NULL){
			slider = slider->next;
		}
		slider->next = root;
	}

	void Start_Shooting(int start, int skip){
		Node* index = root;
		int pos = 1;
		while(pos < start){
			index = index->next;
			pos++;
		}

		int count_down = skip;
		Node* trailer;

		while(count != 1){
			trailer = index;
			index = index->next;
			count_down--;
			if(count_down == 1){
				count_down = skip;
				Delete(trailer);
				index = trailer->next;
			}
		}
	}

	void Delete(Node* prev){
		if(count%10 == 0){
			myfile << endl;
		}
		if(count == 2){
			if(prev != root){
				root = prev;
				myfile << setw(7) <<  prev->next->per;
				if(count != 1){
					myfile << ", ";
				}
				delete prev->next;
				root->next = NULL;
				count--;
				cout << "Only " << root->per << " remains " << endl;
			}
			else{
				cout << "BAM roots neighbor " << root->next->per << " is dead " << endl;
				myfile << setw(7) <<  prev->next->per;
				if(count != 1){
					myfile << ", ";
				}
				delete prev->next;
				prev->next = NULL;
				count--;
			}
		}
		else if(prev->next == root){
			root = prev->next->next;
			myfile << setw(7) << prev->next->per;
			if(count != 1){
				myfile << ", ";
			}
			delete prev->next;
			prev->next = NULL;
			prev->next = root;
			count--;
		}
		else{
			Node* next_per = prev->next->next;
			myfile << setw(7) <<  prev->next->per;
			if(count != 1){
				myfile << ", ";
			}
			delete prev->next;
			prev->next = NULL;
			prev->next = next_per;
			count--;
		}
	}

	Node* root;
	Node* tail;
	int count;
};

int main(){
	Circle_Linked_List* cll = new Circle_Linked_List();
	for(int x = 1; x <= Total_People; x++){
		cll->Insert(x);
	}
	myfile << endl;
	cll->Make_Circle();
	cll->Print_Count();
	cll->Start_Shooting(Start, Skip);
	delete cll;
	cll = NULL;
}
