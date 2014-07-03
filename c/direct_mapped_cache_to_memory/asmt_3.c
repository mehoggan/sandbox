/******************/
/* Matthew Hoggan */
/* Comp 222 MW    */
/* Assignment #3  */
/******************/
#include<stdlib.h>
#include<stdio.h>

void readMem();
void writeMem();

struct Node {
	int tag;
	int* block;
}*cache=NULL;
typedef struct Node line;
int* main_mem = NULL;

/*main loop*/
int status = 0;

/*Parameter variable*/
int mem_Size = 0;
int cache_Size = 0;
int block_Size = 0;

int num_Lines = 0;	

/*wirte to cache variables*/
int write_Address = 0;
int write_Value = 0;

/*loop variable*/
int x = 0;

/*read and write to cache variables*/
int read_Address = 0;

int main () {
	

	while(status != 4) {
		printf("Main memory to cache memory mapping:\n");
		printf("-------------------------------------\n");
		printf("1) Set parameters\n2) Read cache\n3) Write to cache\n4) Exit\n");
		printf("\nEnter selection: ");
		scanf("%d", &status);
		printf("\n");
		if(status == 1) {
			//Input parameters
			printf("Enter main memory size (words): ");
			scanf("%d", &mem_Size);

			printf("Enter cache size (words): ");
			scanf("%d", &cache_Size);

			printf("Enter block size (words/block): ");
			scanf("%d", &block_Size);
			
			//Build cache and main memory
			main_mem = (int*)malloc(mem_Size * sizeof(int));
			for(x = 0; x <= mem_Size - 1; x++) {
				main_mem[x] = mem_Size - x;
			}
			/*num_Lines is used for number of lines in cache*/
			num_Lines = cache_Size/block_Size;
			/*Cache is composed of tags and a pointer to an array*/
			cache = (line*)malloc(num_Lines*sizeof(num_Lines));
			for(x = 0; x <= num_Lines - 1; x++) {
				cache[x].block = NULL;   /*line 68*/
			} 
			printf("\n");
			  
		}
		/*Read from cache*/
		else if(status == 2) {
			readMem();			
		}
		else if(status == 3) {
			writeMem();
		}
		else if(status == 4) {
			if(main_mem != NULL) free(main_mem);
			for(x = 0; x < num_Lines - 1; x++) 
				if(cache[x].block != NULL) free(cache[x].block);
			if(cache != NULL) free(cache);
		}
	}
	return(0);
}

void readMem() {
	int tag = 0;
	int block_num = 0;
	int word = 0;
	int base = 0;
	int data = 0;
	printf("Enter main memory address to read from: ");
	scanf("%d", &read_Address);

	tag = read_Address/cache_Size;
	block_num = (read_Address%cache_Size)/block_Size;
	word = read_Address%block_Size;

	if(cache[block_num].block == NULL) {
		cache[block_num].block =(int*)malloc(block_Size*sizeof(int));
		/*force miss*/
		cache[block_num].tag = -1;
		/*printf("Read miss!\n");*/
	}
	if(cache[block_num].tag != tag) {
		printf("Read miss!\n");
		cache[block_num].tag = tag;
		base  = read_Address/block_Size;
		/*Transfer data from main memory to cache*/
		for(x = 0; x <= block_Size-1; x++) {
			cache[block_num].block[x] = main_mem[base*block_Size + x];
		}
	}
	data = cache[block_num].block[word];
	printf("Word %d of block %d with tag %d contains value %d\n", word, block_num, tag, data);
			
  	printf("\n");
}

void writeMem() {
	int tag = 0;
	int block_num = 0;
	int word = 0;
	int base = 0;
	int data = 0;
	printf("Enter main memory address to write to: ");
	scanf("%d", &write_Address);
	printf("Enter value to write: ");
	scanf("%d", &write_Value);

	tag = write_Address/cache_Size;
	block_num = (write_Address%cache_Size)/block_Size;
	word = write_Address%block_Size;

	if(cache[block_num].block == NULL) {
		cache[block_num].block =(int*)malloc(block_Size*sizeof(int));
		/*force miss*/
		cache[block_num].tag = -1;
		printf("Write miss!\n");
	}
	if(cache[block_num].tag != tag) {
		cache[block_num].tag = tag;
		base  = write_Address/block_Size;
		/*Transfer data from main memory to cache*/
		for(x = 0; x <= block_Size-1; x++) {
			cache[block_num].block[x] = main_mem[base*block_Size + x];
		}
		cache[block_num].block[word] = write_Value;
	}
	main_mem[write_Address] = write_Value;
	printf("Word %d of block %d with tag %d contains value %d\n", word, block_num, tag, write_Value);
	printf("\n");
}
