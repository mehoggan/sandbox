#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

struct record
{
    int num;
} *records = NULL, *copy = NULL;

typedef struct record rec;

int fact(int num)
{
    int answ;
    if(num == 1)
        return 1;
    return (answ = fact(num - 1) * num);
}

void rec_permutate()
{
    printf("\nPermutating\n");
}

int permutate(int limit)
{
    int x;
    int factorial;

    for(x = 0; x < limit; x++)
    {
        (copy + x)->num = (records + x)->num;
    }

    factorial = fact(limit);
    printf("\n\nThere will be %d permutations\n", factorial);
    //rec_permutate();
}

int main(int argc, char* argv[])
{
    int x;
    int status;
    int limit;
    limit = 0;

    if(argc < 2)
    {
        return 1;
    }
    limit = atoi(argv[1]);
    printf("Going to allocate %d slots of memory the size of %d\n", limit, sizeof(rec) * limit);
    records = (struct record*)malloc(sizeof(rec) * limit);
    copy = (struct record*)malloc(sizeof(rec) * limit);

    for(x = 0; x < limit ; x++)
    {
        (records + x)->num = rand();
        if(x != 0 && x%2 == 0)
            printf("\n");
        printf("Inserted records[%d] = %7d\t", x, (records + x)->num);
   }

   status = permutate(limit);

    printf("\n\n");
    if(records != NULL)
    {
        printf("Freeing records\n");
        free(records);
    }

    return 0;
}
