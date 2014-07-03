/*
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>

/*
 *  4096 is the default page size for shared memory
 */
#define BASE_BUFFERSIZE 4096
int loop;

/*
 *  Used to indicate the top and bottom of the pipe
 */
int top_of_buffer;
int bottom_of_buffer;

/*
 *  Three semphore struct to be placed at top
 *  of the shared memory section
 */
typedef struct
{
    int mutex;
    int empty;
    int full;
} semaphores;

semaphores shared;

/*
 *  This is the P function for semaphore
 *  Note: this will cause spinning
 */
void wait_P_test(int* S)
{
    while(*(S) <= 0)
    {
    }
    *(S) = *(S) - 1;
}

/*
 *  This is the V function for semaphore
 */
void signal_V_increment(int* S)
{
    *(S) = *(S) + 1;
}

int main(int argc, char* argv[])
{
    system("clear");
    system("clear");

    pid_t pid;

    //Variales for shared memory
    key_t shm_key1;
    int shm_id1;
    void* buffer;
    size_t shm_page_num;
    shm_key1 = 0x777;

    //Create one page of shared memory 4096 bytes
    shm_page_num = 1;
    if((shm_id1 = shmget(shm_key1, shm_page_num, IPC_CREAT | 0777)) == -1)
    {
        perror("The system failed to get the first shared memory key");
        exit(0);
    }

    //This value is responsible for how large the buffer really is
    int qty = 500;
    int produce = 0;

    /*
     *  Get a pointer to shared memory
     *  and set the semaphores
     */
    buffer = shmat(shm_id1, NULL, SHM_R);
    shared.mutex = 1;
    shared.full = 0;
    shared.empty = (int)(((BASE_BUFFERSIZE - sizeof(semaphores))/sizeof(int)) - qty);
    *((semaphores*)buffer) = shared;
    top_of_buffer = sizeof(semaphores);
    bottom_of_buffer = shared.empty + top_of_buffer;
    produce = 0;
    printf("The range of the buffer will be from %d - %d\n", top_of_buffer, (bottom_of_buffer - qty));

    if((pid = fork()) == -1)
    {
        perror("Fork failed");
        exit(1);
    }
    else if(pid == 0)
    {
        int consume;
        char* main_string;
        char* attch;
        buffer = shmat(shm_id1, NULL, SHM_R);
        top_of_buffer = sizeof(semaphores);
        bottom_of_buffer = shared.empty + top_of_buffer;
        //perform the actual locks and consume
        for(loop = top_of_buffer; loop < (bottom_of_buffer - qty); loop = loop + sizeof(int))
        {
            wait_P_test(&(((semaphores*)buffer)->full));
            wait_P_test(&(((semaphores*)buffer)->mutex));
            consume = *((int*)(buffer + loop));
            printf("CHILD consuming:  %d\n", consume);
            signal_V_increment(&(((semaphores*)buffer)->mutex));
            signal_V_increment(&(((semaphores*)buffer)->empty));
        }
        exit(0);

    }

    //perform the actual locks and produce
    for(loop = top_of_buffer; loop < (bottom_of_buffer - qty); loop = loop + sizeof(int))
    {
        wait_P_test(&(((semaphores*)buffer)->empty));
        wait_P_test(&(((semaphores*)buffer)->mutex));
        *((int*)(buffer + loop)) = produce;
        printf("PARENT producing: %d\n", *((int*)(buffer + loop)));
        produce++;
        signal_V_increment(&(((semaphores*)buffer)->mutex));
        signal_V_increment(&(((semaphores*)buffer)->full));
    }

    //wait for child to finish
    wait(0);
    shmdt(&buffer);
    return 0;
}






/*
 *  Printing
        //display the status Parent before
        //printf("Parent: Status of Semaphores before updates\n");
        //printf("MUTEX is %d\n", ((semaphores*)buffer)->mutex);
        //printf("FULL is %d\n", ((semaphores*)buffer)->full);
        //printf("EMPTY is %d\n", ((semaphores*)buffer)->empty);
        //display the status Parent after
        //printf("PARENT: Status of Semaphores after updates\n");
        //printf("MUTEX is now %d\n", ((semaphores*)buffer)->mutex);
        //printf("FULL is now %d\n", ((semaphores*)buffer)->full);
        //printf("EMPTY is now %d\n", ((semaphores*)buffer)->empty);
 * Printing
        //display the status Child before
        //printf("CHILD: Status of Semaphores before updates\n");
        //printf("MUTEX is %d\n", ((semaphores*)buffer)->mutex);
        //printf("FULL is %d\n", ((semaphores*)buffer)->full);
        //printf("EMPTY is %d\n", ((semaphores*)buffer)->empty);
        //display the status Child after
        //printf("CHILD: Status of Semaphores after updates\n");
        //printf("MUTEX is now %d\n", ((semaphores*)buffer)->mutex);
        //printf("FULL is now %d\n", ((semaphores*)buffer)->full);
        //printf("EMPTY is now %d\n", ((semaphores*)buffer)->empty);
 *  End
 */
