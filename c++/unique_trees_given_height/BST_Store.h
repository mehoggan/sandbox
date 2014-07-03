/*
 *	Matthew Hoggan
 *  Fall 2010
 *  BST Unique Trees With N nodes, Height H
 */


#ifndef BST_STORE_H_
#define BST_STORE_H_

#include <fstream>

class BST_Store{
private:
	char** tree_store;
	int total_trees;
	int nodes_in_tree;
	int elements;
	int tree_count;
	BST* bst;
public:
	BST_Store(int total_trees,int height,int elements){
		this->total_trees=factorial(total_trees);
		this->nodes_in_tree=pow(2.0,(height+1))-1;
		this->nodes_in_tree;
		this->elements=elements;
		this->tree_count=0;
		myfile<<"There are "<<total_trees<<"! = "<<this->total_trees<<" trees, if complete they would have "<<this->nodes_in_tree<<" nodes\n";
		tree_store=new char*[this->total_trees];
		for(int x=0;x<this->total_trees;x++){
			tree_store[x]=new char[nodes_in_tree];
		}
		for(int x=0;x<this->total_trees;x++){
			for(int y=0;y<this->nodes_in_tree;y++){
				tree_store[x][y]='0';
			}
		}
	}
	~BST_Store(){
		for(int x=0;x<this->total_trees;x++){
			delete [] tree_store[x];
			tree_store[x]=NULL;
		}
		delete [] tree_store;
		tree_store=NULL;
	}
	long factorial(int n){
		int value = 2;
		if(n == 2){
		}
		else{
			value = factorial(n - 1) * n;
		}
		return value;
	}
	void Create_Tree(){
		this->bst=new BST();
	}
	void Insert(int value){
		int index=bst->insert_heap_index_return(value);
		this->tree_store[tree_count][index]='1';
	}
	void Delete_Tree(){
		delete bst;
		bst=NULL;
	}
	void Increment_Tree_Count(){
		this->tree_count++;
	}
	void Display_Tree_Store(){
		/*
		myfile<<"#######################################\n";
		//*/
		for(int y=0;y<this->nodes_in_tree;y++){
			/*
			if((y)%5==0&&y!=0){
				myfile<<"\n";
			}
			myfile<<"["<<y<<"]->"<<tree_store[this->tree_count][y];
			//*/
			myfile<<tree_store[this->tree_count][y];
		}
		/*
		myfile<<"\n#######################################\n";
		//*/
	}
	void Display_Tree_Store(int row){
		for(int y=0;y<this->nodes_in_tree;y++){
			myfile<<tree_store[row][y];
		}
	}
	int count_unique_trees(int total_generate_H){
		cout<<"Preparing to count"<<endl;
		int unique=0;
		int hex_count=this->nodes_in_tree;
		int count=0;;
		while((hex_count-=4)>0){
			count++;
		}
		myfile<<(this->nodes_in_tree)<<"/"<<4<<" = "<<count<<" hex values R "<<(this->nodes_in_tree%4)<<"\n";
		myfile<<"There will be "<<count+1<<" HEX values\n";
		char* hex=new char[4];
		int hex_index=0;
		char** all_hex=(char**)malloc(total_generate_H*sizeof(char*));
		for (int i=0;i<total_generate_H;i++) {
			all_hex[i] = (char*)malloc((count+2)*sizeof(char));
		}
		for(int i=0;i<total_generate_H;i++){
			for(int j=0;j<count+1;j++){
				all_hex[i][j]='*';
			}
			all_hex[i][count+1]='\0';
		}
		int loc=0;
		for(int row=0;row<total_generate_H;row++){
			for(int col=0;col<this->nodes_in_tree;col++){
				hex[hex_index++]=this->tree_store[row][col];
				if(hex_index==4){
					hex[4]='\0';
					hex_index=0;
					char insert=hex_value4(hex);
					all_hex[row][loc++]=insert;
				}else if(col==this->nodes_in_tree-1){
					hex[3]='\0';
					hex_index=0;
					char insert=hex_value3(hex);
					all_hex[row][loc++]=insert;
				}
			}
			loc=0;
			Display_Tree_Store(row);
			myfile<<" == ("<<all_hex[row]<<")\n";

			cout << "Before Crash" << endl;
			int count = 0;
			while(hex[count] != '\0'){
				cout << hex[count++] << " ";
			}
			cout << hex[count] << endl;
			cout << "You did no access invalid state" << endl;
			cout << "count = " << count << endl;
			delete [] hex;
			cout << "After Crash" << endl;
			hex=NULL;
			hex=new char[4];
			
		}
		bool notfound=true;
		//* THIS IS THE LAST SECTION THAT WILL BE NEEDED TO CALCULATE UNIQUE TREES
		//	COUNT THE UNIQUE HEX VALUES IN THE ALL_HEX ARRAY AND PLACE THEM INTO THE
		//	UNIQUE_HEX ARRAY.
		cout<<"DOING COUNTING NOW"<<endl;
		char** unique_hex=(char**)malloc(total_generate_H*sizeof(char*));
		for(int i=0;i<total_generate_H;i++) {
			unique_hex[i] = (char*)malloc((count+2)*sizeof(char));
		}
		for(int i=0;i<total_generate_H;i++){
			for(int j=0;j<count+1;j++){
				unique_hex[i][j]='*';
			}
			unique_hex[i][count+1]='\0';
		}
		for(int i=0;i<total_generate_H;i++){
			bool duplicate=false;
			for(int k=0;k<total_generate_H;k++){
				if(strcmp(unique_hex[k],all_hex[i])==0){
						duplicate=true;
				}
			}
			if(!duplicate){
				unique_hex[unique++]=all_hex[i];
			}
		}
		for(int i=0;i<total_generate_H&&unique_hex[i][0]!='*';i++){
			myfile<<unique_hex[i]<<endl;
		}
		cout<<"DELETING UNIQUE_HEX and ALL_HEX AT SAME TIME"<<endl;
		for(int i=0;i<total_generate_H;i++){
			printf("Freeing address %p\n", unique_hex[i]);
			free(unique_hex[i]);
		}
		free(unique_hex);
		unique_hex = NULL;
		//	THIS IS THE END OF THE LAST SECTION
		//*/
		free(all_hex);
		all_hex = NULL;
		return unique;
	}
	char hex_value4(char binary[5]){
		if(strcmp(binary,"0001")==0){
			return '1';
		}else if(strcmp(binary,"0010")==0){
			return '2';
		}else if(strcmp(binary,"0011")==0){
			return '3';
		}else if(strcmp(binary,"0100")==0){
			return '4';
		}else if(strcmp(binary,"0101")==0){
			return '5';
		}else if(strcmp(binary,"0110")==0){
			return '6';
		}else if(strcmp(binary,"0111")==0){
			return '7';
		}else if(strcmp(binary,"1000")==0){
			return '8';
		}else if(strcmp(binary,"1001")==0){
			return '9';
		}else if(strcmp(binary,"1010")==0){
			return 'A';
		}else if(strcmp(binary,"1011")==0){
			return 'B';
		}else if(strcmp(binary,"1100")==0){
			return 'C';
		}else if(strcmp(binary,"1101")==0){
			return 'D';
		}else if(strcmp(binary,"1110")==0){
			return 'E';
		}else if(strcmp(binary,"1111")==0){
			return 'F';
		}else{
			return '0';
		}

	}
	char hex_value3(char binary[4]){
		if(strcmp(binary,"001")==0){
			return '1';
		}else if(strcmp(binary,"010")==0){
			return '2';
		}else if(strcmp(binary,"011")==0){
			return '3';
		}else if(strcmp(binary,"100")==0){
			return '4';
		}else if(strcmp(binary,"101")==0){
			return '5';
		}else if(strcmp(binary,"110")==0){
			return '6';
		}else if(strcmp(binary,"111")==0){
			return '7';
		}else{
			return '0';
		}
	}
};

#endif /* BST_STORE_H_ */
