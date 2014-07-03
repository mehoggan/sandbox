/*
 *	Memory Inefficient
 *	Generate an Infinite number of Power Sets
 *	Author: Matthew E. Hoggan
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int count;

typedef struct set {
	int* S;
	int size;
	int last_index;
} SET;

typedef struct node {
	SET* sub_set;
	struct node* next;
} NODE;

typedef struct stack {
	NODE* head;
	NODE* tail;
	int node_count;
} STACK;

/*	S={1,2,3,4}
 *	P(S)={
 *		{},{1},{1,2},{1,3},{1,4},{1,2,3},{1,2,4},{1,3,4},
 *		{1,2,3,4},{2},{2,3},{2,4},{2,3,4},{3},{3,4},{4}
 *	};
 */

void print_sub_set(SET *sub_set) {
	printf("%d)\t\t{",++count);
	int h;
	for(h=0;h<sub_set->size;h++) {
		if(h!=sub_set->size-1) printf("%d,",sub_set->S[h]);
		else printf("%d}\n",sub_set->S[h]);
	}
}

void calculate_power_set(int set_index,SET* set,int SIZE,STACK* stack) {
	if(set_index==0) {
		printf("%d)\t\t{},\n",++count);
	}else {
		calculate_power_set(set_index-1,set,SIZE,stack);
		//At the top of each return the stack will
		//will be empty. build sets with one size
		if(stack->head==NULL) {
			SET *tmp_set;
			tmp_set=(SET*)malloc(sizeof(SET));
			tmp_set->S=(int*)malloc(sizeof(int));
			tmp_set->S[0]=set->S[set_index-1];
			tmp_set->size=1;
			NODE *tmp_node;
			tmp_node=(NODE*)malloc(sizeof(NODE));
			tmp_node->sub_set=tmp_set;
			tmp_node->next=NULL;
			tmp_node->sub_set->last_index=set_index-1;
			stack->head=tmp_node;
			stack->tail=tmp_node;
		}
		
		while(stack->head!=NULL) {
			SET *top_set=stack->head->sub_set;
			print_sub_set(top_set);
			int i;
			for(i=top_set->last_index;i<SIZE-1;i++){
				SET *tmp_set=(SET*)malloc(sizeof(SET));
				tmp_set->S=(int*)malloc(sizeof(int)*(top_set->size+1));
				tmp_set->size=top_set->size+1;
				tmp_set->last_index=i+1;
 				int j;
				for(j=0;j<top_set->size;j++) tmp_set->S[j]=top_set->S[j];
				tmp_set->S[j]=set->S[i+1];
				NODE *insert_node=(NODE*)malloc(sizeof(NODE));
				insert_node->sub_set=tmp_set;
				insert_node->next=NULL;
				stack->tail->next=insert_node;
				stack->tail=insert_node;
			}
	
			NODE *tmp_node=stack->head->next;
			free(stack->head->sub_set->S);
			free(stack->head->sub_set);
			free(stack->head);
			stack->head=NULL;
			stack->head=tmp_node;
		}
	}
}

int main(int argc, char** argv) {
	count=0;
	printf("\tP(S)={\n");
	int SIZE=10;
	SET *set=(SET*)malloc(sizeof(SET));
	set->S=(int*)malloc(sizeof(int)*SIZE);
	int i;
	for(i=0;i<SIZE;i++) set->S[i]=i+1;
	STACK stack;
	stack.head=NULL;
	stack.tail=NULL;
	calculate_power_set(SIZE,set,SIZE,&stack);
	printf("\t};\n");
	free(set->S);
	free(set);
}
