// https://en.wikipedia.org/wiki/Pthreads

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 3

void *perform_work(void *arguments){
  int index = *((int*)arguments);
  int sleep_time = 1 + rand() % NUM_THREADS;
  printf("THREAD %d: started.\n", index);
  printf("THREAD %d: will be sleeping for %d seconds.\n", index, sleep_time);
  sleep(sleep_time);
  printf("THREAD %d: Ended.\n", index);
  return NULL;
}

int main(void) {
  pthread_t threads[NUM_THREADS];
  int thread_args[NUM_THREADS];
  int i;
  int result_code;
  
  //create all threads one by one
  for (i = 0; i < NUM_THREADS; i++) {
    printf("IN MAIN: Creating thread %d.\n", i);
    thread_args[i] = i;
    result_code = pthread_create(&threads[i], NULL, perform_work, &thread_args[i]);
    assert(!result_code);
  }

  printf("IN MAIN: All threads was created.\n");

  //wait for each thread to complete
  for (i = 0; i < NUM_THREADS; i++) {
    result_code = pthread_join(threads[i], NULL);
    assert(!result_code);
    printf("IN MAIN: Thread %d has ended.\n", i);
  }

  printf("MAIN program has ended.\n");
  return 0;
}
/*
// Global variable: accesible to all threads

int thread_count;

void *Hello(void *rank); //Thread function

int main(int argc, char* argv[]) {
    long thread; // Use long in case of a 64-bit system
    pthread_t thread_handles;
    
    // Get number of threads from cammand line
    thread_count = strtol(argv[1], NULL, 10);
    
    thread_handles = malloc(thread_count* sizeof(pthread_t));
    
    for (thread = 0; thread < thread_count; thread++)
        pthread_create(&thread_handles[thread],NULL, Hello, (void*) thread);
    printf("Hello from the main thread\n");
    
    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);
    
    free(thread_handles);
    return 0;
}

void *Hello(void* rank){
    // Use long in case of 64-bit system
    long my_rank = (long) rank;
    
    printf("Hello from thread %ld of %d\n", my_rank, thread_count);
    
    return NULL;
}
*/
