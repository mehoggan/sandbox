#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

struct peterson
{
    int turn;
    int test;
} peterson;

typedef struct peterson peter;

int main(int argc, char* argv[])
{
    pid_t pid;

    key_t shm_key;
    int shm_id;
    size_t shm_size;
    void* shm_ptr;
    int shm_loader;

    shm_key = 0x777;

    /*
     *  This will produce a page size of data which on linux
     *  is 4096 bytes worth of data so that will be
     *  4096bytes * (1int/4bytes) = 1024int, so if the size
     *  of your data changes then you have to recalculate
     *  the number of elements that can fit in your shared memory
     *  section
     */
    shm_size = 1;
    if((shm_id = shmget(shm_key, shm_size, IPC_CREAT | 0777)) == -1)
    {
        perror("The system failed to get shared memory key");
        exit(0);
    }

    printf("The size of a peterson is: %d\n", sizeof(struct peterson));
    printf("Which means that we can fit: %d Petersons into %d pages\n", (4096/sizeof(struct peterson)), shm_size);

    /*
     *  Attach shared memory to process
     *  struct peterson
     */
    shm_loader = 0;
    shm_ptr = shmat(shm_id, NULL, SHM_R);
    printf("The memory address of the shared memory segment is: %x\n", &shm_ptr);
    int loop;
    int counter;
    counter = 1;
    /*
     *  Working on filling memory
     */
    for(loop = 0; loop < ((int)((shm_size * 4096)/sizeof(struct peterson))); loop = (loop + sizeof(struct peterson)))
    {
        peter insert;
        insert.turn = counter;
        insert.test = counter + 1;
        *((peter*)shm_ptr + loop) = insert;
        printf("Slot %d in shared memory contains %d : %d\n", loop, ((peter*)shm_ptr + loop)->turn, ((peter*)shm_ptr + loop)->test);
        counter += 2;
    }

    shmdt(&shm_ptr);
    return 0;
}
