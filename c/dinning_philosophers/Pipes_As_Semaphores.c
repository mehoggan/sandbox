#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define TRUE            1

#define N               5
#define Busy_Eating     5
#define Busy_Thinking   10
#define Left(p)         (p)
#define Right(p)        (((p) + 1) % N)

typedef int*            semaphore;

semaphore               chopstick[N];

semaphore make_semaphore(void)
{
    int* sema;
    sema = calloc(2, sizeof(int));
    pipe(sema);
    return sema;
}

void wait(semaphore S)
{
    int junk;

    if(read(S[0], &junk, 1) <= 0)
    {
        printf("ERROR: wait() failed, check semaphore creation \n");
        exit(1);
    }
}

void signal(semaphore S)
{
    if(write(S[1], "x", 1) <= 0)
    {
        printf("ERROR: wait() failed, check semaphores creation\n");
        exit(1);
    }
}

void pick_up(int me)
{
    if(me == 0)
    {
        wait(chopstick[Right(me)]);
        printf("Philosopher %d picks up right chopstick\n", me);
        sleep(1);
        wait(chopstick[Left(me)]);
        printf("Philosopher %d picks up left chopstick\n", me);
    }
    else
    {
        wait(chopstick[Left(me)]);
        printf("Philosopher %d picks up left chopstick\n", me);
        sleep(1);
        printf("Philosopher %d picks up right chopstick\n", me);
        wait(chopstick[Right(me)]);
    }

}

void put_down(int me)
{
    signal(chopstick[Left(me)]);
    signal(chopstick[Right(me)]);
}

void philosopher(int me)
{
    char* s;
    int i = 1;

    while(TRUE)
    {
        pick_up(me);
        s = i == 1 ? "st" : i == 2 ? "nd" : i == 3 ? "rd" : "th";
        printf("Philosopher %d eating for the %d%s time\n", me, i, s);
        sleep(Busy_Eating);
        put_down(me);
        printf("Philospher %d thinking \n", me);
        sleep(Busy_Thinking);
    }
}

int main()
{
    int i;

    for(i = 0; i < N; i++)
    {
        chopstick[i] = make_semaphore();
        signal(chopstick[i]);
    }

    for(i = 0; i < N - 1 ; i++)
    {
        if(fork() == 0)
            break;
    }
    philosopher(i);
}
