/********************/
/*Matthew Hoggan    */
/*Math 482 Fall 2010*/
/*Heap Sort			*/
/********************/

#include <iomanip>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <string>

#define SIZE 120

using namespace std;

int comparison_count = 0;
int best_case = 100;
int worse_case = 0;

////////////////////////////////////////HEAP SORT STARTS HERE////////////////////////////////////////
void trickle(int heap[], int start, int end)
{
	int maxChild = -1;
	if((2 * start + 1) > end)
	{
		maxChild = -1;
	}
	else
	{
		maxChild = (2 * start + 1);
	}
	if((2 * start + 2) > end || maxChild == -1)
	{	//All these conditions find max child
		maxChild = -1;					//Return -1 if max child out of bounds
	}
	else if(2 * start + 2 < end && heap[2 * start + 2] > heap[maxChild])
	{
		maxChild = (2 * start + 2);
	}
	int temp = heap[start];
	while(maxChild < end && maxChild != -1 && heap[maxChild] > temp  )
	{
		heap[start] = heap[maxChild];
		start = maxChild;				//Slide all values up to parent if necessary
		if((2 * start + 1) > end)
		{
			maxChild = -1;
		}
		else
		{
			maxChild = (2 * start + 1);		//All these conditions find max child
		}						//Return -1 if max child out of bounds
		if((2 * start + 2) > end || maxChild == -1)
		{
			maxChild = -1;
		}
		else if(2 * start + 2 < end && heap[2 * start + 2] > heap[maxChild])
		{
				maxChild = (2 * start + 2);
		}
	}
	heap[start] = temp;					//Place value where it belongs
}

void trickle_Heap(int heap[], int start, int end)
{
	int maxChild = -1;
	if((2 * start + 1) > end) 
	{
		maxChild = -1;
	}
	else 
	{
		maxChild = (2 * start + 1);
	}
	if((2 * start + 2) > end || maxChild == -1) 
	{	//All these conditions find max child
		maxChild = -1;					//Return -1 if max child out of bounds
	}
	else if(2 * start + 2 < end && heap[2 * start + 2] > heap[maxChild]) 
	{
		comparison_count++;
		cout << "Compared to right child " << heap[2 * start + 2] << " to " << heap[maxChild] << " right child greater" << endl;
		maxChild = (2 * start + 2);
	} 
	else if(maxChild != -1 && heap[maxChild] >= heap[2 * start + 2])
	{
		comparison_count++;
		cout << "Compared to right child " << heap[2 * start + 2] << " to " << heap[maxChild] << " right child less" << endl;
	}
	int temp = heap[start];
	int hold_MaxChild = maxChild;
	while(maxChild < end && maxChild != -1 && heap[maxChild] > temp  ) 
	{
		comparison_count++;
		cout << "Compared to max child " << heap[maxChild] << " to " << temp << " max child greater" << endl;
		heap[start] = heap[maxChild];				
		start = maxChild;				//Slide all values up to parent if necessary
		if((2 * start + 1) > end) 
		{
			maxChild = -1;
		}
		else 
		{
			maxChild = (2 * start + 1);		//All these conditions find max child					
		}						//Return -1 if max child out of bounds
		if((2 * start + 2) > end || maxChild == -1) 
		{
			maxChild = -1;
		}
		else if(2 * start + 2 < end && heap[2 * start + 2] > heap[maxChild]) 
		{
			maxChild = (2 * start + 2);
		} 
	}
	if(hold_MaxChild != -1 && heap[hold_MaxChild] <= temp)
	{
		comparison_count++;
		cout << "Compared to max child " << heap[maxChild] << " to " << heap[2 * start + 2] << " max child is less" << endl;
	}
	heap[start] = temp;					//Place value where it belongs
}

void loop_HeapSort(int heap[], int size)
{	//Actual sort
	int del = 0;
	for(int bef_Sorted = size - 1; bef_Sorted > 0; bef_Sorted--)
	{
		int temp = heap[del];			//Remove first value
		heap[del] = heap[bef_Sorted];		//move last value in heap to front
		heap[bef_Sorted] = temp;			//Place largest value into array (stored at end of heap)
		trickle(heap, del, bef_Sorted);		//Trickle the new found root to its new place
	}
}

void HeapSort(int a[], int size)
{
	for(int x = size - 1; x >= 0; x--)
	{
		trickle_Heap(a, x, size);			//Build heap from end to save on complexity
	}
	loop_HeapSort(a, size);
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

void variance(double variance[])
{

}

int main()
{
		double num_comp[SIZE];
        string cmd = " ";
        int size = 5;
        for(int x = 0; x < SIZE; x++)
        {
        	cout << "Test " << x + 1 << endl;
        	int* array = new int[size];
        	for(int y = 0; y <= size; y++)
        	{
                array[y] = (rand()%10) + 1;
        	}
        	Display(array, size, 0, 4);
        	HeapSort(array, size);
        	num_comp[x] = comparison_count;
        	comparison_count = 0;
        	Display(array, size, 0, 4);
        	cout << "There were " << num_comp[x] << " comparisons" << endl;
        	delete [] array;
        }
        best_Case(num_comp);
        worse_Case(num_comp);
        expectations(num_comp);
        variance(num_comp);
}

