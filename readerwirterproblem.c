#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
pthread_mutex_t w;
void* writer(void *arg) {
  int waiting_time = rand() % 10;
  int k = ((int) arg);
  pthread_mutex_lock(&w);
  printf("W%d Random time wait = %d\n", k, waiting_time);
  sleep(waiting_time);
  printf("Enter the No of time W%d wants to write\n", k);
  int t;scanf("%d", & t);
  printf("writing W%d is under process\n", k);
  int i;
  for (i=0;i<t;i++) {
    printf("Enter %dth Value to be written:\n", (i + 1));
    int u;scanf("%d",&u);
	k+=u;
	}
  printf("Shared Value Updated to = %d \n", k);
  printf("--------------------------------------------------\n");
  pthread_mutex_unlock(&w);
}



