/*
 *	Matthew Hoggan
 *  Fall 2010
 *  BST Unique Trees With N nodes, Height H
 */

#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace std;

/*
 * Global Variables and definitions
 */
int count=0;
int total=0;
int perm=0;
ofstream myfile("6_nodes_2_height.txt");

class BST{
private:
	class Node{
	public:
		Node(){
		}
		Node(int value){
			this->value=value;
			this->left=NULL;
			this->right=NULL;
		}
		int get_value(){
			return this->value;
		}
		int set_value(int value){
			this->value=value;
		}
		Node* get_left(){
			return this->left;
		}
		void set_left(Node* child){
			this->left=child;
		}
		Node* get_right(){
			return this->right;
		}
		void set_right(Node* child){
			this->right=child;
		}
	private:
		Node *left,*right;
		int value;
	};
	Node* root;
public:
	BST(){
		root=NULL;
	}
	BST(int value){
		root=new Node(value);
	}
	~BST(){
		if(root==NULL){
		}else{
			rec_delete(root);
			root=NULL;
		}
	}
	void rec_delete(Node* curr_node){
		if(curr_node!=NULL){
			rec_delete(curr_node->get_left());
			rec_delete(curr_node->get_right());
			delete curr_node;
			curr_node=NULL;
		}
	}
	void insert(int value){
		if(this->root==NULL){
			this->root=new Node(value);
		}else{
			Node* insert=new Node(value);
			rec_insert(root, insert);
		}
	}
	Node* rec_insert(Node* curr_node, Node* insert){
		Node* rtn;
		if(curr_node==NULL){
			rtn=insert;
		}else{
			rtn=curr_node;
			if(insert->get_value()<curr_node->get_value()){
				curr_node->set_left(rec_insert(curr_node->get_left(),insert));
			}else if(insert->get_value()>curr_node->get_value()){
				curr_node->set_right(rec_insert(curr_node->get_right(),insert));
			}
		}
		return rtn;
	}
	int insert_heap_index_return(int value){
		Node* slider=root;
		Node* parent=root;
		int index=0;
		/*
		myfile<<"INSERTING "<<value<<"\n";
		myfile<<"INDEX IS NOW..............................["<<index<<"]\n";
		//*/
		if(root==NULL){
			root = new Node(value);
		}else{
			while(slider!=NULL){
				if(value<slider->get_value()){
					parent=slider;
					slider=slider->get_left();
					index=2*index+1;
				}else if(value>=slider->get_value()){
					parent=slider;
					slider=slider->get_right();
					index=2*index+2;
				}
				/*
				myfile<<"INDEX IS NOW..............................["<<index<<"]\n";
				//*/
			}
			if(value<parent->get_value()){
				parent->set_left(new Node(value));
			}else if(value>=parent->get_value()){
				parent->set_right(new Node(value));
			}
		}
		/*
		myfile<<value<<" was inserted at INDEX("<<index<<") in the array\n";
		//*/
		return index;
	}
	void dis_tree(){
		if(root==NULL){
		}else{
			rec_dis_tree(root);
		}
	}
	void rec_dis_tree(Node* curr_node){
		if(curr_node==NULL){
		}
		else{
			rec_dis_tree(curr_node->get_left());
			rec_dis_tree(curr_node->get_right());
			printf("%d ", curr_node->get_value());
		}
	}
	int tree_height(){
		int rtn=-1;
		if(root==NULL){
			rtn=-1;
		}else{
			rtn=rec_tree_height(root);
		}
		return rtn;
	}
	int rec_tree_height(Node* level){
		if(level==NULL){
			return 0;
		}else if(level==root){
			return max(rec_tree_height(level->get_left()),rec_tree_height(level->get_right()));
		}else{
			return 1+max(rec_tree_height(level->get_left()),rec_tree_height(level->get_right()));
		}
	}
	int max(int a, int b){
		int rtn=a;
		if(b>a){
			rtn=b;
		}
		return rtn;
	}
	Node* get_root(){
		return this->root;
	}
};

#endif /* BST_H_ */
