/*********************/
/*Matthew Hoggan     */
/*Math 482 Fall 2010 */
/*********************/
#include <iomanip>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <string>

#define SIZE 120
#define ELEMENTS 9

#define problem1
//#define problem5

using namespace std;

int comparison_count = 0;
int best_case = 100;
int worse_case = 0;

////////////////////////////////////////merge SORT STARTS HERE////////////////////////////////////////
void merge(int* array, int* temp, int size, int leftStart, int leftStop, int rightStart, int rightStop)
{
	int tempPos = leftStart;
	int tempLeft = leftStart;
	int tempRight = rightStart;
	while(tempLeft <= leftStop && tempRight <= rightStop && tempLeft != size)
	{
		if(*(array + tempLeft) <= *(array + tempRight))
		{
			comparison_count++;
			*(temp + tempPos++) = *(array + tempLeft++);
		}
		else if(*(array + tempLeft) >= *(array + tempRight))
		{
			comparison_count++;
			*(temp + tempPos++) = *(array + tempRight++);
		}
	}
	while(tempLeft <= leftStop && tempPos <= rightStop)
	{
		*(temp + tempPos++) = *(array + tempLeft++);
	}
	while(tempRight <= rightStop && tempPos <= rightStop)
	{
		*(temp + tempPos++) = *(array + tempRight++);
	}
	for(int x = leftStart; x <= rightStop; x++)
	{
		*(array + x) = *(temp + x);
	}
}

void rec_mergesort(int* array, int* temp, int size, int left, int right)
{
	int mid = 0;
	if(left == right)
	{
	}
	else
	{
		mid = (left + right)/2;
		rec_mergesort(array, temp, size, left, mid);
		rec_mergesort(array, temp, size, (mid + 1), right);
		merge(array, temp, size, left, mid, (mid + 1), right);
	}
}

void mergesort(int* array, int* temp, int size)
{
	rec_mergesort(array, temp, size, 0, size - 1);
}

void Display(int* array, int size, int left, int right)
{
	for(int x = left; x <= right; x++)
	{
		if(x != 0 && x%10 == 0) cout << endl;
		cout << setw(4) << *(array + x) << " ";
	}
	cout << endl;
}

void best_Case(double num_comp[])
{
	for(int x = 0; x < SIZE; x++)
	{
		if(num_comp[x] < best_case)
		{
			best_case = num_comp[x];
		}
	}
	cout << "The best case was " << best_case << endl;
}

void worse_Case(double num_comp[])
{
	for(int x = 0; x < SIZE; x++)
	{
		if(num_comp[x] > worse_case)
		{
			worse_case = num_comp[x];
		}
	}
	cout << "The worse case was " << worse_case << endl;
}

void expectations(double num_comp[])
{
	double sum = 0.0;
	for(int x = 0; x < SIZE; x++)
	{
		sum += num_comp[x];
	}
	double expected = sum/SIZE;
	cout << "The expected value was " << expected << endl;

	double var = 0;
	for(int x = 0; x < SIZE; x++)
	{
		var += pow((num_comp[x] - expected), 2.0);
	}
	var /= SIZE;
	cout << "The variance is " << var << endl;
}

#if defined problem1
int main() 
{
	double num_comp[SIZE];
	string cmd = " ";
	int size = 5;
	for(int x = 0; x < SIZE; x++)
	{
		cout << "Test " << x + 1 << endl;
		int* array = new int[size];
		int* temp = new int[size];
		for(int y = 0; y <= size; y++)
		{
			array[y] = (rand()%10) + 1;
		}
		Display(array, size, 0, size - 1);
		mergesort(array, temp, size);
		num_comp[x] = comparison_count;
		comparison_count = 0;
		Display(array, size, 0, size - 1);
		cout << "Had " << num_comp[x] << "comparisons" << endl;
		delete [] array;
		delete [] temp;
	}
	best_Case(num_comp);
	worse_Case(num_comp);
	expectations(num_comp);
}
#endif

#if defined problem5
int main()
{
	int i;
	int* X = new int[ELEMENTS];
	int* Y = new int[ELEMENTS];
	int count = 0;
	for(int x = ELEMENTS; x > 0; x-- )
	{
		X[count++] = x;
	}
	printf("Unsorted Array:\n");
	for(i=0;i<ELEMENTS;i++)
	{
		printf("%d ",X[i]);
	}
	mergesort(X,Y,ELEMENTS);
	printf("\nSORTED ARRAY\n");
	for(i=0;i<ELEMENTS;i++)
	{
		printf("%d ",X[i]);
	}
	printf("\nThere were %d comparisons made\n", comparison_count);
}
#endif


