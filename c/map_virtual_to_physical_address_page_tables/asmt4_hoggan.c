/********************/
/*Matthew E. Hoggan */
/*COMP 222 MW		*/
/*Assignment #4		*/
/********************/

#include<stdlib.h>

void enter_Params();
void map_Virtual();
void print_PageT();

struct node {
	int virtual_Page;
	int page_Frame;
}*page_Table = NULL;

typedef struct node entry;

int que_Pointer = 0;
int main_Mem = 0;
int page_Size = 0;
int replace = 0;
int num_Frames = 0;

int main() {
	int option = 0;
	while(option != 4) {
		printf("Virtual memory to Main memory mapping:\n");
		printf("---------------------------------------\n");
		printf("1) Set parameters\n");
		printf("2) Map virtual address\n");
		printf("3) Print page table\n");
		printf("4) Exit\n\n");
		printf("Enter Selection: ");
		scanf("%d", &option);
		printf("\n");
		if(option == 1) {
			enter_Params();
		}
		else if(option == 2) {
			map_Virtual();
		}
		else if(option == 3) {
			print_PageT();
		}
		else if(option == 4) {
			if(page_Table != NULL) {
				free(page_Table);
			}
		}
		else {};
	}
	return 0;
}

void enter_Params() {
	int looper = 0;
	printf("Enter main memory size (words): ");
	scanf("%d", &main_Mem);
	printf("Enter page size (words/page): ");
	scanf("%d", &page_Size);
	printf("Enter replacement policy(0 = LRU, 1 = FIFO): ");
	scanf("%d", &replace);

	num_Frames = main_Mem/page_Size;
	page_Table = (entry*)malloc(num_Frames*sizeof(entry));

	for(looper = 0; looper < num_Frames; looper++) {
		page_Table[looper].virtual_Page = -1;
	}
	que_Pointer = -1;
	printf("\n");
}

void map_Virtual() {
	int looper = 0;

	int virt_Adrs = 0;
	int virt_Page = 0;
	int offset = 0;
	int scanner = 0;
	int pg_Frm = 0;
	int physical_Address = 0;

	printf("Enter virtual memory address to access: ");
	scanf("%d", &virt_Adrs);
    
	virt_Page = virt_Adrs/page_Size;
	offset = virt_Adrs%page_Size;
	
	scanner = 0;
	while((scanner < num_Frames) && (page_Table[scanner].virtual_Page != virt_Page) && (page_Table[scanner].virtual_Page != -1)) {
		scanner++;		
	}
	
	if(scanner == num_Frames) {
		printf("Page fault!\n");
		pg_Frm = page_Table[0].page_Frame;
		for(looper = 0; looper < num_Frames - 2; looper++) {
			page_Table[looper].virtual_Page = page_Table[looper + 1].virtual_Page;
			page_Table[looper].page_Frame = page_Table[looper + 1].page_Frame;
		}
		page_Table[num_Frames - 1].virtual_Page = virt_Page;
		page_Table[num_Frames - 1].virtual_Page = pg_Frm;
	}
	else if(page_Table[scanner].virtual_Page == -1) {
		printf("Page fault!\n");
		page_Table[scanner].virtual_Page = virt_Page;
		page_Table[scanner].page_Frame = scanner;
		que_Pointer++;
	}
	else if(page_Table[scanner].virtual_Page == virt_Page) {
		physical_Address = (page_Table[scanner].page_Frame * page_Size) + offset;
		pg_Frm = page_Table[scanner].page_Frame;
		printf("Virtual address %d maps to physical address %d", virt_Adrs, physical_Address);
		if(replace == 0) {
			pg_Frm = page_Table[scanner].page_Frame;
			for(looper = scanner; looper <= que_Pointer - 1; looper++) {
				page_Table[looper].virtual_Page = page_Table[looper + 1].virtual_Page;
				page_Table[looper].page_Frame = page_Table[looper + 1].page_Frame;
			}
			page_Table[que_Pointer].virtual_Page = virt_Page;
			page_Table[que_Pointer].page_Frame = pg_Frm;
		}
		if(replace == 1) {

		}
	}
	printf("\n");
}

void print_PageT() {
	int looper = 0;
	for(looper = 0; page_Table != NULL && looper <= que_Pointer; looper++) {
		printf("VP %d --> PF %d ", page_Table[looper].virtual_Page, page_Table[looper].page_Frame);
	}
	printf("\n\n");
}