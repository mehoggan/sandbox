/*
 *  Semaphores by Matthew Hoggan
 *  Code borrowed from "Unix System Programming 2ed."
 *  Oct 29, 2009
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/*
 *  Start of global variables
 */
#define KEY (1492)
#define NUM_OF_SEMAPHORES 1
char BUFFER[50];

typedef enum
{
  BARBER,
  DOOR,
  WAITING_ROOM
} semaphores;

union semun
{
    int val;
    struct semid_ds *buf;
} sem_argument[0];

struct sembuf sem_operations[NUM_OF_SEMAPHORES];
/*
 *  End of global variables
 */

void print_quit_error_message(char* message[300])
{
    write(1, message, sizeof(message));
    exit(0);
}

int WAIT_P(const int* sem_Id, int semaphore_Array_Index)
{
    int retval;
    sem_operations[0].sem_num = semaphore_Array_Index;
    sem_operations[0].sem_op = -1;
    sem_operations[0].sem_flg = 0;

    retval = semop(*(sem_Id), sem_operations, 1);

    if(retval == 0)
    {
        printf("Successful WAIT_P for process: %d.\n", getpid());
    }
    else
    {
        printf("Failed WAIT_P for process: %d.\n", getpid());
    }
    return retval;
}

int SIGNAL_V(const int* sem_Id, int semaphore_Array_Index)
{
    int retval;
    sem_operations[0].sem_num = semaphore_Array_Index;
    sem_operations[0].sem_op = 1;
    sem_operations[0].sem_flg = 0;

    retval = semop(*(sem_Id), sem_operations, 1);
    if(retval == 0)
    {
       printf("Successful SIGNAL_V by process: %d.\n", getpid());
    }
    else
    {
       printf("Failed SIGNAL_V by process: %d.\n", getpid());
    }
    return retval;
}

int configure_Semaphore(int* sem_Id, int semaphore_Array_Size)
{
    int retval = 0;
    *(sem_Id) = semget(KEY, semaphore_Array_Size, 0666 | IPC_CREAT);
    if(*(sem_Id) < 0)
    {
        retval = -1;
    }
    else
    {
        printf("Semaphore creation id: %d, num: %d semaphore\n", *(sem_Id), semaphore_Array_Size);
    }
    return retval;
}

int set_Semaphore(int* sem_Id, int semaphore_Array_Index, int value_for_Semaphore)
{
    int retval = 0;
    sem_argument[semaphore_Array_Index].val = value_for_Semaphore;
    if(semctl(*(sem_Id), semaphore_Array_Index, SETVAL, sem_argument[semaphore_Array_Index]) < 0)
    {
        retval = -1;
    }
    else
    {
        printf("Semaphore[%d] with id: %d was initilized to %d\n", semaphore_Array_Index, *(sem_Id), sem_argument[semaphore_Array_Index].val);
    }
    return retval;
}

int del_Semaphore(int* sem_Id, int semaphore_Array_Index)
{
    int retval = 0;
    if(semctl(*(sem_Id), semaphore_Array_Index, IPC_RMID) < 0)
    {
        retval = -1;
    }
}

int main(int argc, char* argv[])
{
    int status;
    int sem_id;
    int loop;

    status = configure_Semaphore(&sem_id, NUM_OF_SEMAPHORES);

    if(status < 0)
    {
        printf("Unable to obtain semaphore.\n");
        exit(0);
    }

    status = set_Semaphore(&sem_id, BARBER, 1);

    if(status < 0)
    {
        printf("Failed in setting semaphore.\n");
        exit(0);
    }

    WAIT_P(&sem_id, BARBER);
    printf("In critical section\n");
    SIGNAL_V(&sem_id, BARBER);

    for(loop = 0; loop < NUM_OF_SEMAPHORES; loop++)
    {
        status = del_Semaphore(&sem_id, loop);
        if(status < 0)
        {
            printf("Failed to remove semaphore\n");
            exit(0);
        }
    }
}
