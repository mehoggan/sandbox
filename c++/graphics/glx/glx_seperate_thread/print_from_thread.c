#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/gl.h>

typedef 
struct data {
  int x;
  int y;
} DATA;

void *
render_thread2(void *x) {
  int count = 0;
  while (count >= 0) {
    sleep(4);
    fprintf(stdout, "From thread %d -- %d\n", ((DATA *)(x))->x, ((DATA *)(x))->y);
    count++;
  }
  void *y = &count;
  return y;
}

void *
render_thread(void *x) {
  int count = 0;
  while (count >= 0) {
    sleep(1);
    fprintf(stdout, "From thread %d\n", *((int*)(x)));
    count++;
  }
  void *y = &count;
  return y;
}

int
main(int argc, char **argv)
{
  /*
   * Step ???: Create thread
   */
  pthread_t thread_1;
  int pass = 1;
  pthread_create(&thread_1, NULL, render_thread, &pass);

  pthread_t thread_2;
  DATA d = {1, 2};
  pthread_create(&thread_2, NULL, render_thread2, &d);

  int count = 0;
  while (count >= 0) {
    sleep(2);
    fprintf(stdout, "From main thread\n");
    count++;
  }
  pthread_join(thread_2, NULL);
  pthread_join(thread_1, NULL);
  exit(0);
}















