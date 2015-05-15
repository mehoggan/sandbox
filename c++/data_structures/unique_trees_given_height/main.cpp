/*
 * main.cpp
 *
 *  Created on: Sep 18, 2010
 *      Author: Matthew Hoggan
 */

#include "BST.h"
#include "BST_Store.h"

/*
 * Global variables
 */
BST_Store* bst_store;
#define N 10
#define H 8

void permute(int* list,int m,int size){
	int i;
	int temp;
	if(m==0){
		count++;
		//cout<<"Permutation "<<count<<endl;
		BST* bst = new BST();
		for(int y=0;y<size;y++){
			//cout<<"Inserting into tree"<<endl;
			bst->insert(list[y]);
		}
		int height=bst->tree_height();
		perm++;
		if(height==H){
			total++;
			myfile<<"---------------------------------------------------\n";
			myfile<<"START TREE LIST PERM "<<perm<<" ("<<total<<")\n";
			myfile<<"---------------------------------------------------\n";
			/*
			myfile<<"#######################################\n";
			//*/
			for(int y=0;y<size;y++){
				myfile<<list[y]<<" ";
			}
			/*
			myfile<<"\n#######################################\n";
			//*/
			bst_store->Create_Tree();
			//cout<<"Inserting into BST store"<<endl;
			for(int y=0;y<size;y++){
				bst_store->Insert(list[y]);
			}
			/*
			myfile<<"..........HEIGT="<<height<<"\n";
			//*/
			myfile<<setw(5)<<"--->"<<setw(5);
			bst_store->Display_Tree_Store();
			bst_store->Increment_Tree_Count();
			bst_store->Delete_Tree();
			myfile<<"\n---------------------------------------------------\n";
			myfile<<"END TREE LIST PERM "<<perm<<" ("<<total<<")\n";
			myfile<<"---------------------------------------------------\n\n\n\n\n";
		}
		delete bst;
		bst=NULL;
	}else{
		for(i = 0; i < m; i++){
			temp=list[i];
			list[i]=list[m-1];
			list[m-1]=temp;
			permute(list, m-1, size);
			temp=list[m-1];
			list[m-1]=list[i];
			list[i]=temp;
		}
	}
}

int main(){
	bst_store=new BST_Store(N,H,N);
	int* vector=NULL;
	vector=(int*)malloc(N*sizeof(int));
	for(int x=0;x<N;x++){
		vector[x]=x+1;
	}
	//cout<<"Permutating"<<endl;
	permute(vector,N,N);
	free(vector);
	myfile<<"There were "<<total<<" trees with height "<<H<<" and "<<N<<" nodes\n";
	int unique_trees=bst_store->count_unique_trees(total);
	myfile<<"There were "<<unique_trees<<" unique trees\n";
	delete bst_store;
	exit(0);
}
////











