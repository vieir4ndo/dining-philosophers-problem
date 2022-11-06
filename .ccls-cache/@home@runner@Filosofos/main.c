#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define N 5
#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

typedef int semaphore;
int state[N];
semaphore mutex = 1;
semaphore s[N];

void up (semaphore *s){
  *s = 1;
}

void down (semaphore *s){
  *s = 0;
}

void test(int i, FILE* file){
  if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING){
    state[i] = EATING;
    fprintf(file,"Philosopher %d is eating...\n", i);
    up(&s[i]);
  }
  else {
    fprintf(file,"Philosopher %d can't eat right now...\n", i);
  }
}

void think(){
  sleep(rand() % 10);
}

void take_forks(int i,  FILE* file){
  down(&mutex);
  state[i] = HUNGRY;
  fprintf(file, "Philosopher %d is hungry...\n", i);
  test(i, file);
  up(&mutex);
  down(&s[i]);
}

void eat(){
  sleep(rand() % 10);
}

void return_forks(int i, FILE* file){
  down(&mutex);
  state[i] = THINKING;
  fprintf(file,"Philosopher %d is thinking...\n", i);
  test(LEFT, file);
  test(RIGHT, file);
  up(&mutex);
}

void * philosopher(int i){
  char fileName[22];
  switch (i) {
    case 0: {
      char teste[22] = "log_philosopher_0.txt";
      strcpy(fileName, teste);
    break; }
    case 1: {
      char teste[22] = "log_philosopher_1.txt";
      strcpy(fileName, teste);
    break; }
    case 2: {
      char teste[22] = "log_philosopher_2.txt";
      strcpy(fileName, teste);
    break; }
    case 3: {
      char teste[22] = "log_philosopher_3.txt";
      strcpy(fileName, teste);
    break; }
    default: {
      char teste[22] = "log_philosopher_9.txt";
      strcpy(fileName, teste); }
  }
  
  FILE* file = fopen(fileName, "w");
  while(true){
    think();
    take_forks(i, file);
    eat();
    return_forks(i, file);
  }
}

pthread_t Thread0, Thread1, Thread2, Thread3, Thread4;

int main(void) {
  printf("Hello Philosophers\n");
  pthread_create( & Thread0, NULL, philosopher(0), NULL);
  pthread_create( & Thread1, NULL, philosopher(1), NULL);
  pthread_create( & Thread2, NULL, philosopher(2), NULL);
  pthread_create( & Thread3, NULL, philosopher(3), NULL);
  pthread_create( & Thread4, NULL, philosopher(4), NULL);

  // now join them
  pthread_join(Thread0, NULL);
  printf("Thread id %ld returned\n", Thread0);
  pthread_join(Thread1, NULL);
  printf("Thread id %ld returned\n", Thread1);
  pthread_join(Thread2, NULL);
  printf("Thread id %ld returned\n", Thread2);
  pthread_join(Thread3, NULL);
  printf("Thread id %ld returned\n", Thread3);
  pthread_join(Thread4, NULL);
  printf("Thread id %ld returned\n", Thread4);

  return 0;
}