#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

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

void test(int i, char fileName[]){
  if (state[i] == HUNGRY){
    while (true) {
      if (state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        FILE* file = fopen(fileName, "a");
        fprintf(file, "Philosopher %d is eating...\n", i);
        fclose(file);
        up(&s[i]);
        break;
      }
      else {
        FILE* file = fopen(fileName, "a");
        fprintf(file, "Philosopher %d is hungry but wasn't able to eat because there were no forks available...\n", i);
        fclose(file);
      }
    }
  }
}

void think(){
  sleep(rand() % 10);
}

void take_forks(int i,  char fileName[]){
  down(&mutex);
  state[i] = HUNGRY;
  FILE* file = fopen(fileName, "a");
  fprintf(file, "Philosopher %d is hungry...\n", i);
  fclose(file);
  test(i, fileName);
  up(&mutex);
  down(&s[i]);
}

void eat(){
  sleep(rand() % 10);
}

void return_forks(int i,  char fileName[]){
  down(&mutex);
  state[i] = THINKING;
  FILE* file = fopen(fileName, "a");
  fprintf(file, "Philosopher %d is thinking...\n", i);
  fclose(file);
  test(LEFT, fileName);
  test(RIGHT, fileName);
  up(&mutex);
}

void * philosopher0(void * data);
void * philosopher1(void * data);
void * philosopher2(void * data);
void * philosopher3(void * data);
void * philosopher4(void * data);

void * philosopher0(void * data){
  int i = 0;
  char fileName[] = "log_thread_0.txt";
  FILE* file = fopen(fileName, "w");
  fclose(file);
  for (int j =0; j<2; j++){
    think();
    take_forks(i, fileName);
    eat();
    return_forks(i, fileName);
  }
}

void * philosopher1(void * data){
  int i = 1;
  char fileName[] = "log_thread_1.txt";
  FILE* file = fopen(fileName, "w");
  fclose(file);
  for (int j =0; j<2; j++){
    think();
    take_forks(i, fileName);
    eat();
    return_forks(i, fileName);
  }
}


void * philosopher2(void * data){
  int i = 2;
  char fileName[] = "log_thread_2.txt";
  FILE* file = fopen(fileName, "w");
  fclose(file);
  for (int j =0; j<2; j++){
    think();
    take_forks(i, fileName);
    eat();
    return_forks(i, fileName);
  }
}


void * philosopher3(void * data){
  int i = 3;
  char fileName[] = "log_thread_3.txt";
  FILE* file = fopen(fileName, "w");
  fclose(file);
  for (int j =0; j<2; j++){
    think();
    take_forks(i, fileName);
    eat();
    return_forks(i, fileName);
  }
}


void * philosopher4(void * data){
  int i = 4;
  char fileName[] = "log_thread_4.txt";
  FILE* file = fopen(fileName, "w");
  fclose(file);
  for (int j =0; j<2; j++){
    think();
    take_forks(i, fileName);
    eat();
    return_forks(i, fileName);
  }
}

pthread_t Thread0, Thread1, Thread2, Thread3, Thread4;

int main(void) {
  printf("Hello Philosophers\n");
  pthread_create( & Thread0, NULL, philosopher0, NULL);
  pthread_create( & Thread1, NULL, philosopher1, NULL);
  pthread_create( & Thread2, NULL, philosopher2, NULL);
  pthread_create( & Thread3, NULL, philosopher3, NULL);
  pthread_create( & Thread4, NULL, philosopher4, NULL);

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