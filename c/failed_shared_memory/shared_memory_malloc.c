#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

typedef enum status
{
    PARENT,
    CHILD,
} stat;

stat* test;

void wait_sec(int x)
{
    int loop;
    for(loop = 0; loop < (x * 100000); loop++)
    {
    }
}

#define BASE_BUFFERSIZE 20
int* mutex;
int* full;
int* empty;
int* buffer;

void wait_P_test(void* S)
{
    //printf("\tBefore: The semaphore is: %x = %d\n", S, *((int*)(S)));
    while(*((int*)(S)) <= 0)
    {
        if((*(test)) == PARENT)
        {
            //printf("Stuck in Parent\n");
        }
        else
        {
            //printf("Stuck in Child\n");
            //printf("The status of the variables is:\n");
            //printf("Child: status MUTEX: %x = %d\n", mutex, *(mutex));
            //printf("Child: status EMPTY: %x = %d\n", empty, *(empty));
            //printf("Child: status FULL: %x = %d\n", full, *(full));
        }
        //printf("===============================================================================================================\n");
        //printf("Pausing\n");
        wait_sec(200);
        //printf("===============================================================================================================\n");
        //printf("Unpausing\n");
        //printf("===============================================================================================================\n");
    }
    *((int*)S) = *((int*)S) - 1;
    //printf("\tAfter: The semaphore is: %x = %d\n", S, *((int*)(S)));
}

void signal_V_increment(void* S)
{
    //printf("\tBefore: The semaphore is: %x = %d\n", S, *((int*)(S)));
    *((int*)S) = *((int*)S) + 1;
    //printf("\tAfter: The semaphore is: %x = %d\n", S, *((int*)(S)));
}

int main(int argc, char* argv[])
{
    pid_t pid;
    int loop;
    //printf("Parent: The parents pid is: %d\n", getpid());

    //Make pointer for status
    test = (stat*)malloc(sizeof(stat));

    //Get a pointer to shared memory for semaphores
    mutex = (int*)malloc(sizeof(int));
    full = (int*)malloc(sizeof(int));
    empty = (int*)malloc(sizeof(int));

    //Make the actual buffer
    buffer = (int*)malloc(sizeof(int));

    //Set initial values
    (*mutex) = 1;
    //printf("Parent: Initilizing mutex: %d\n", *(mutex));
    (*full) = 0;
    //printf("Parent: Initilizing full: %d\n", *(full));
    (*empty) = (int)((BASE_BUFFERSIZE));
    //printf("Parent: Initilizing empty: %d\n", *(empty));
    //printf("===============================================================================================================\n");
    if((pid = fork()) == -1)
    {
        perror("Fork failed");
    }
    else if(pid == 0)
    {
        int consume;
        ////printf("Child: The address of the buffer is: %x | The address of mutex is: %x | The address of full is: %x | The address of empty is: %x\n", buffer, mutex, full, empty);
        for(loop = 0; loop < BASE_BUFFERSIZE; loop++)
        {
            *(test) = CHILD;
            //printf("Child: Calling wait on FULL\n");
            wait_P_test(full);
            //printf("Child: Calling wait on MUTEX\n");
            wait_P_test(mutex);
            consume = *(buffer + loop);
            printf("Child: The item just consumed is: %d\n", *(buffer + loop));
            //printf("Child: Calling signal on MUTEX\n");
            signal_V_increment(mutex);
            //printf("Child: Calling signal on EMPTY\n");
            signal_V_increment(empty);
            //printf("===============================================================================================================\n");
        }
        //Delete the pointer to memory
        free(mutex);
        free(full);
        free(empty);
        exit(0);
    }
    ////printf("Parent: The address of the buffer is: %x | The address of mutex is: %x | The address of full is: %x | The address of empty is: %x\n", buffer, mutex, full, empty);
    for(loop = 0; loop < BASE_BUFFERSIZE; loop++)
    {
        *(test) = PARENT;
        //printf("Parent: Calling wait on EMPTY\n");
        wait_P_test(empty);
        //printf("Parent: Calling wait on MUTEX\n");
        wait_P_test(mutex);
        *(buffer + loop) = loop;
        printf("Parent: Placing item %d onto buffer\n", *(buffer + loop));
        //printf("Parent: Calling signal on MUTEX\n");
        signal_V_increment(mutex);
        //printf("Parent: Calling signal on FULL\n");
        signal_V_increment(full);
        //printf("===============================================================================================================\n");
    }
    wait(0);
    return 0;
}
