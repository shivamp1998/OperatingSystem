#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
int shared_variable = 0;
pthread_mutex_t mux,w;
int cnt = 0;
const int X = 5;
void *writer(void* a){
	pthread_mutex_lock(&w);
	int rT = rand()%20;
	int r = ((int)a);
	sleep(rT);// Writer waiting for Random time between 0 to 20ns;
	printf("Writer Writing X no. of times\n");
	for(int i=0;i<X;i++){
		//sleep(rT);
		shared_variable++;
		
		printf("The written value is %d and no of readers present is %d\n",shared_variable,cnt);
		pthread_mutex_unlock(&w);
		shared_variable--;
	}
	
}
void *reader(void *a){
	pthread_mutex_lock(&mux);
	cnt++;
	if(cnt == 1){
		pthread_mutex_lock(&w);
	}
	pthread_mutex_unlock(&mux);
        
        int rT = rand() % 10;
        int r = ((int)a);
        
        sleep(rT);
        
        printf("Now R%d is reading....\n",r);
        
        for(int j=0; j<X; j++){
                printf("R%d read the shared value = %d\n",r, shared_variable);
        }
        printf("Number of Readers present = %d\n", cnt);
        pthread_mutex_lock(&mux);
        cnt--;
        if(cnt==0){//Now writer can come if they want
                pthread_mutex_unlock(&w);
        }
        pthread_mutex_unlock(&mux);
}

int main(){
	int NumOfReaders = 5;
	int NumOfWriters = 5;
	pthread_t readers[NumOfReaders],writers[NumOfWriters];
	pthread_mutex_init(&w,NULL);
	pthread_mutex_init(&mux,NULL);
	for(int i=0;i<5;i++){
		pthread_create(&writers[i],NULL,&writer,(int *)i);
		pthread_create(&readers[i],NULL,&reader,(int *)i);
		
	}
	for(int i=0;i<5;i++){
		pthread_join(writers[i],NULL);
		pthread_join(readers[i],NULL);
		
	}
	return 0;
}
