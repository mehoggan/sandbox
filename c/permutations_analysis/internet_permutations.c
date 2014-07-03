#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int* list;
int execute_times;

void permute_rec(int*, int, int);

int main(int argc, char* argv[])
{
	int x;
	if(argc < 2)
	{
		perror("Too few arguments");
		return 1;
	}
	list = (int*)malloc(sizeof(int) * atoi(argv[1]));	
	for( x = 0; x < atoi(argv[1]); x++)
	{
		list[x] = (x + 1);
	}
	printf("Recursive algorithm\n");
	printf("--------------------------\n");
	permute_rec(list, atoi(argv[1]), atoi(argv[1]));
	printf("There were exactly %d swaps\n", (execute_times * 2)); 
	return(0);
}

void permute_rec(int* list, int m, int size)
{
	int i;
	int temp;
	if(m == 0)
	{
		execute_times = execute_times + 1;
		printf("execute_times is now: %d\n", execute_times);
		for(i = 0; i < size; i++)
		{
			printf("%4d",list[i]);
		}
		printf("\n");
	}
	else
	{
		for(i = 0; i < m; i++)
		{
			execute_times =	execute_times + 1;
			printf("execute_times is now: %d\n", execute_times);
			temp=list[i];
			list[i]=list[m-1];
			list[m-1]=temp;
		
			permute_rec(list, m-1, size);

			temp=list[m-1];
			list[m-1]=list[i];
			list[i]=temp;
		}
	}
} 
