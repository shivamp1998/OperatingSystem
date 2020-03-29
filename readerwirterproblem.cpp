#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
int shared_variable = 0;
pthread_mutex_t mux,w;//locks
int cnt = 0;//no of readers
const int X = 5;//The value of X can be modified from here
void *writer(void* a){
	int rT = rand()%10; // generates a random no b/w 0 to 10;
	int r = ((int)a);//stores the no of writer
//	sleep(rT);
	
// Writer waiting for Random time between 0 to 20ns;
// writer writes X no of times, here X is taken as 5	
	int i;
	for(i=0;i<X;i++){
	sleep(rT);
	pthread_mutex_lock(&w);
	shared_variable = shared_variable + 1;
	if(cnt==1)
	cnt=0;
	printf("Writer %d:modified Shared Variable to %d with %d readers present\n",r+1,shared_variable,cnt);
    
	pthread_mutex_unlock(&w);
}
}
void *reader(void *a){
		
		int rT = rand()%20;
		int r = ((int)a);
//		sleep(rT);
		
		
		
		
		sleep(rT);
		//reader acquires lock before modifying no of readers
		pthread_mutex_lock(&mux);
		cnt++;
		if(cnt == 1){
			pthread_mutex_lock(&w);//If this id the first reader, then it will block the writer
		}
		// Reading Section
		pthread_mutex_unlock(&mux);
		for(int i=0;i<X;i++){
		printf("Reader %d:read sharedvariable as %d with %d readers present\n",r+1,shared_variable,cnt);
		}
		// Reader acquire the lock before modifying number of reader
		pthread_mutex_lock(&mux);
		cnt--;
		if(cnt == 0){
			pthread_mutex_unlock(&w);//If this is the last reader, it will wake up the writer.
			
		}
		pthread_mutex_unlock(&mux);	
		
	}
	

		
	

int main(){
	int NumOfReaders = 5;
	int NumOfWriters = 5;
	pthread_t readers[NumOfReaders],writers[NumOfWriters];
	pthread_mutex_init(&w,NULL);
	pthread_mutex_init(&mux,NULL);
	//thread Creation
	for(int i=0;i<5;i++){
		pthread_create(&writers[i],NULL,&writer,(int *)i);
		pthread_create(&readers[i],NULL,&reader,(int *)i);
		
	}
	//Joining Thread
	for(int i=0;i<5;i++){
			pthread_join(readers[i],NULL);
			pthread_join(writers[i],NULL);
	}
	pthread_mutex_destroy(&mux);
	pthread_mutex_destroy(&w);
	return 0;
}
