#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int main(int argc, char *argv){
	int total=0;
	unsigned int size=3;
	int *array=(int*)malloc(sizeof(int)*size);
	int i;
	for(i=0;i<size;i++) array[i]=i+1;
	unsigned int number=0;
	unsigned int final=(number+1)<<size; //=2^(size)
	while(number<final){
		int tmp=number;
		int cnt=0;
		printf("%d) ",++total);
		while(tmp!=0){
			if(tmp&1){
				printf("%d,",array[cnt]);
			}
			cnt++;
			tmp>>=1;
		}
		printf("\n");
		number++;
	}
	free(array);
}
