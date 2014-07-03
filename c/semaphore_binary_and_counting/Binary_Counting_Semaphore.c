/*
 *  Semaphores by Matthew Hoggan
 *  Code borrowed from "Unix System Programming 2ed."
 *  Oct 29, 2009
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <sys/stat.h>

typedef struct
{
    int count_sem;
} count_semaphore;
count_semaphore sem;

typedef struct
{
    int binary_sem;
} binary_semaphore;
binary_semaphore sem_real;

void wait_P_test(int* S)
{
    int timer;
    timer = 0;
    while(*(S) <= 0)
    {
        if(timer > 100)
        {
            printf("Child (%d) forced to wait\n", getpid());
            sleep(2);
        }
        timer++;
    }
    *(S) = *(S) - 1;
    printf("P called and semaphore has value %d\n", *(S));
}

/*
 *  This is the V function for semaphore
 */
void signal_V_increment(int* S)
{
    *(S) = *(S) + 1;
    printf("V called and semaphore has value %d\n", *(S));
}

int main(int argc, char* argv[])
{
    int semkey = 0x00000001;
    int status;
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

    /*
     *  Get a pointer to shared memory
     *  and set the semaphores
     */
    buffer = shmat(shm_id1, NULL, SHM_R);
    sem.count_sem = 10;
    *((count_semaphore*)buffer) = sem;
    printf("The value of the counting semaphore is now %d\n", (((count_semaphore*)buffer) + 0)->count_sem);
    sem_real.binary_sem = 1;
    *((binary_semaphore*)(buffer + sizeof(count_semaphore))) = sem_real;
    printf("The value of the binary sempahore is now %d\n", (((binary_semaphore*)buffer + 1)->binary_sem));

    int x;
    pid_t pid;
    printf("===========================================================================================================\n");
    for(x = 0; x < 20; x++)
    {
        if((pid = fork()) == -1)
        {
            perror("Fork failed");
            exit(1);
        }
        else if(pid == 0)
        {
            buffer = shmat(shm_id1, NULL, SHM_R);
            printf("Process (%d) = %d is calling: ", getpid(), x);
            wait_P_test(&(((binary_semaphore*)buffer + 1)->binary_sem));
            printf("Process (%d) = %d is calling: ", getpid(), x);
            wait_P_test(&(((count_semaphore*)buffer)->count_sem));
            printf("Process (%d) = %d is calling: ", getpid(), x);
            signal_V_increment(&(((binary_semaphore*)buffer + 1)->binary_sem));
            printf("Child %d (%d) entering critical section\n", x, getpid());
            printf("Process (%d) = %d is calling: ", getpid(), x);
            wait_P_test(&(((binary_semaphore*)buffer + 1)->binary_sem));
            printf("Process (%d) = %d is calling: ", getpid(), x);
            signal_V_increment(&(((count_semaphore*)buffer)->count_sem));
            printf("Process (%d) = %d is calling: ", getpid(), x);
            signal_V_increment(&(((binary_semaphore*)buffer + 1)->binary_sem));

            printf("===========================================================================================================\n");
            exit(0);
        }
    }
    wait(1111);
    sleep(10);
    shmdt(&buffer);
    system("\n");
    return 0;
}
