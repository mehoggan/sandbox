#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

key_t sem_key;
int sem_id;

void get_sem(int semcount)
{
        static int onlyonce = 0;
        char *filekey;

        sem_key = 0x777;
        if ((sem_id = semget(sem_key, semcount, 0666 | IPC_CREAT)) == (-1))
        {
            perror("Failed to get semaphore id");
            exit(1);
        }
}

void rel_sem()
{
        if (semctl(sem_id, 0, IPC_RMID, 0) == (-1))
        {
            perror("Failed to control semaphore id");
            exit(1);
        }
}


void set_sem(int semnum, int value)
{
        if (semctl(sem_id, semnum, SETVAL, value) == (-1))
        {
            perror("Failed to control semaphore id");
            exit(1);
        }
}


int P(int semnum)
{
        struct sembuf sb, *sbp;
        sb.sem_num=semnum;
        sb.sem_op= (-1);
        sb.sem_flg=0;
        sbp= (&sb);
        return(semop(sem_id, sbp, 1));
}


int V(int semnum)
{
        struct sembuf sb, *sbp;
        sb.sem_num=semnum;
        sb.sem_op= 1;
        sb.sem_flg=0;
        sbp= (&sb);
        return(semop(sem_id, sbp, 1));
}

main()
{
        char *shmptr;
        int k;

        get_sem(1);             /*  get same 2 semaphores as shm1  */
        set_sem(0,1);

        printf("\n");
        for(k = 1; k < 6; k++)
        {
                /*(void)*/ P(0);    /*  wait until ok to read shared memory  */
                /*(void)*/ printf("p() worked\n");
                /*(void)*/ V(0);    /*  ok for shm1 to write shared memory  */
        }
        rel_sem();   /*  release semaphores back to system  */
        return(0);
}

