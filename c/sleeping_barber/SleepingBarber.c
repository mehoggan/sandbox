/*
 *  Semaphores by Matthew Hoggan
 *  Code borrowed from "Unix System Programming 2ed."
 *  Oct 29, 2009
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/*
 *  Start of global variables
 */
#define KEY (1492)
#define NUM_OF_SEMAPHORES 3
#define NUM_OF_CLIENTS 5
#define AVERAGE_HAIRCUT_TIME 10
char BUFFER[50];

typedef enum
{
  BARBER,
  DOOR,
  CHAIR
} semaphores;

typedef enum
{
    false,
    true,
} bool;

union semun
{
    int val;
    struct semid_ds *buf;
} sem_argument[NUM_OF_SEMAPHORES];

struct sembuf sem_operations[1];
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
        //printf("Successful WAIT_P for process: %d.\n", getpid());
    }
    else
    {
        //printf("Failed WAIT_P for process: %d.\n", getpid());
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
       //printf("Successful SIGNAL_V by process: %d.\n", getpid());
    }
    else
    {
       //printf("Failed SIGNAL_V by process: %d.\n", getpid());
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
        //printf("Semaphore creation id: %d, num: %d semaphore\n", *(sem_Id), semaphore_Array_Size);
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
        //printf("Semaphore[%d] with id: %d was initilized to %d\n", semaphore_Array_Index, *(sem_Id), sem_argument[semaphore_Array_Index].val);
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
    return retval;
}

int Barber(int* sem_Id)
{
    while(true)
    {
        WAIT_P(sem_Id, CHAIR);
        printf("The barber is cutting hair\n");

    }
}

int Client(int* sem_Id)
{
    printf("Client %d says ohhh crap I need to get my hair cut next week\n", getpid());
    sleep(5);
    WAIT_P(sem_Id, DOOR);
    printf("The client %d walks into the door\n", getpid());
    sleep(2);
    SIGNAL_V(sem_Id, DOOR);

    WAIT_P(sem_Id, BARBER);
    printf("Client %d is sitting in the barber chair\n", getpid());
    SIGNAL_V(sem_Id, CHAIR);
    sleep(AVERAGE_HAIRCUT_TIME);
    SIGNAL_V(sem_Id, BARBER);

    WAIT_P(sem_Id, DOOR);
    printf("Client %d walks out door\n", getpid());
    sleep(2);
    SIGNAL_V(sem_Id, DOOR);
}

int main(int argc, char* argv[])
{
    int status;
    int sem_id;
    int loop;
    int rand;
    pid_t barber, wait, client;

    /*
     *  Start of configure semaphores
     */
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

    status = set_Semaphore(&sem_id, DOOR, 1);
    if(status < 0)
    {
        printf("Failed in setting semaphore.\n");
        exit(0);
    }

    status = set_Semaphore(&sem_id, CHAIR, 0);
    if(status < 0)
    {
        printf("Failed in setting semaphore.\n");
        exit(0);
    }
    /*
     *  End of configure semaphores
     */

    if((barber = fork()) < 0)
    {
        perror("The barber does not want to work today");
        exit(0);
    }
    else if(barber == 0)
    {
        Barber(&sem_id);
        exit(0);
    }

    for(loop = 0; loop < NUM_OF_CLIENTS; loop++)
    {
        srand(loop);
        rand = random()%20;
        if(rand == 0)
        {
            rand = 10;
        }
        sleep(rand);
        if((client = fork()) < 0)
        {
            perror("A client was shot on his way to the barber shop <BANG!!!!>\n");
        }
        else if(client == 0)
        {
            Client(&sem_id);
            exit(0);
        }
    }

    while ((wait = waitpid (barber, 0, 0)) > 0)
        fprintf (stderr, "child %d at end \n", wait);

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
