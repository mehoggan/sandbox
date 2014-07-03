/********************/
/*Matthew Hoggan    */
/*Math 482 Fall 2010*/
/*Quick Sort		*/
/********************/

#include <iomanip>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <windows.h>

#define SIZE 120	//This determines number of times run
#define TIME 20	//This is used in pause commands
#define ELEMENTS 9	//This is for problem 6
const int size = 5;	//This is size of array
using namespace std;

//#define problem1
#define problem5

int comparison_count = 0;
int best_case = 100;
int worse_case = 0;

void check(int* array, int size)
{
	for(int x = 0; x < size - 1; x++)
	{
		if(array[x] > array[x + 1])
		{
			cout << "You screwed up" << endl;
			exit(0);
		}
	}
}

void Display(int* array, int size, int left, int right)
{
	for(int x = left; x < right; x++)
    {
		if(x != 0 && x%10 == 0)
		{
			cout << endl;
		}
        cout << setw(4) << *(array + x) << " ";
    }
    cout << endl;
}

int Partition(int* array, int begin, int end)
{
	int pivot = array[(end - 1)];
	//cout << "Pivot value is " << pivot << endl;
	int compare = begin;
	for(int loop = begin; loop < end - 1; loop++)
	{
		if(array[loop] <= pivot)
		{
			comparison_count++;
			//cout << "array[" << loop << "] = " << array[loop] << " <= " << pivot << endl;
			//cout << "swaping array[" << compare <<"] = " << array[compare]
			//     << " with array[" << loop << "] = " << array[loop] << endl;
			//Display(array, (end - begin), begin, end);
			int temp = array[compare];
			array[compare] = array[loop];
			array[loop] = temp;
			//Display(array, (end - begin), begin, end);
			compare += 1;
		}
		else
		{
			comparison_count++;
			//cout << "No swap needed at array[" << compare <<"] = " << array[compare] << endl;
			//Display(array, (end - begin), begin, end);
		}
	}
	//cout << "swaping pivot value to array[" << end - 1 <<"] = " << array[end - 1]
	//     << " with array[" << compare << "] = " << array[compare] << endl;
	//Display(array, (end - begin), begin, end);
	int temp = array[end - 1];
	array[end - 1] = array[compare];
	array[compare] = temp;
	//Display(array, (end - begin), begin, end);
	return (compare + 1);
}

void QuickSort(int* array, int begin, int end)
{
	if(begin < end)
	{
		//cout << "Partitioning" << endl;
		int index = Partition(array, begin, end);
		//cout << "Left quicksort call from index " << begin << " to " << (index - 1) << endl;
		QuickSort(array, begin, index - 1);
		//cout << "Pivot value landed at array[" << index << "]" << endl;
		//cout << "Right quicksort call from index " << (index) << " to " << end << endl;
		QuickSort(array, index, end);
		//cout << "Pivot value landed at array[" << index << "]" << endl;
	}
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
        int* array = NULL;

        for(int x = 0; x < SIZE; x++)
        {
        	//cout << "Test " << x + 1 << endl;
        	//cout << "Creating array " << endl;
        	array = new int[size];
        	for(int y = 0; y < size; y++)
        	{
                array[y] = (rand()%10) + 1;
        	}
        	//cout << "Array is" << endl;
        	//Display(array, size, 0, size);
        	//cout << "Sorting" << endl;
        	QuickSort(array, 0, size);
        	//cout << "Done Sorting" << endl;
        	num_comp[x] = comparison_count;
        	comparison_count = 0;
        	//cout << "Done Sorting" << endl;
        	Display(array, size, 0, size);
        	//cout << "There were " << num_comp[x] << " comparisons" << endl;
        	//cout << "Deleting array" << endl;
        	delete [] array;
        	array = NULL;
        }
        //cout << "Calculating best case" << endl;
        best_Case(num_comp);
        //cout << "Calculating worst case" << endl;
        worse_Case(num_comp);
        //cout << "Calculating variance and expected" << endl;
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
	QuickSort(X,0,ELEMENTS);
	printf("\nSORTED ARRAY\n");
	for(i=0;i<ELEMENTS;i++)
	{
		printf("%d ",X[i]);
	}
	printf("\nThere were %d comparisons made\n", comparison_count);
}
#endif


