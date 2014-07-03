#include <stdlib.h>
#include <stdio.h>

void printdata(int *v, int n)
{
    int i = 0;
    for (i = 0; i < n; ++i) {
        printf("%3d", v[i]);
    }
    putchar('\n');
}

int binarysearch0(int x, int *v, int n) 
{
    int low, high, mid;
    
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ( x < v[mid])
            high = mid -1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int binarysearch1(int x, int *v, int n) 
{
    int low, high, mid;
    
    low = 0;
    high = n - 1;
    while (low <= high && v[(mid = (low + high) / 2)] != x ) {
        mid = (low + high) / 2;
        if ( x < v[mid])
            high = mid -1;
        else
            low = mid + 1;
    }
    return (v[mid] == x) ? mid : -1;
}

int main(int argc, char *argv[]) 
{
    int v[10][10] = { { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
                      {10,11,12,13,14,15,16,17,18,19},
                      {20,21,22,23,24,25,26,27,28,29},
                      {30,31,32,33,34,35,36,37,38,39},
                      {40,41,42,43,44,45,46,47,48,49},
                      {50,51,52,53,54,55,56,57,58,59},
                      {60,61,62,63,64,65,66,67,68,69},
                      {70,71,72,73,74,75,76,77,78,79},
                      {80,81,82,83,84,85,86,87,88,89},
                      {90,91,92,93,94,95,96,97,97,99}
                    };
    
    int i = 0;
    for (i = 0; i < 10; ++i) {
        int search = 0;
        (i == 0) ? (search = 1000) : (search = v[i][0] + rand()%10);
        if(binarysearch1(search, v[i], 10) > -1) {
            printf("%d was found in the data: %14s", search, " ");
            printdata(v[i], 10);
        } else {

            printf("%d was NOT found in the data: %10s", search, " ");
            printdata(v[i], 10);
        }
        putchar('\n');
    }
    return 0;
}
