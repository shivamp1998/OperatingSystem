#include<stdio.h>
#include<condition_variable.h>
#include<thread.h>
#include<random.h>
#include<mutex.h>
int main() {
  int readers = 5;
  int writers = 5;
  printf(thread::hardware_concurrency());
  
  thread threads[readers];
  
  for(int i = 0; i < readers; i++) {
    threads[thread{read}];
  }
  for(int i = 0; i < writers; i++) {
    threads[thread{write}];
  }
  for(int i = 0; i < readers + writers; i++) {
    threads[i].join();
  }
  return 0;
}
