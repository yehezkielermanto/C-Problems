/*compile this program using gcc,
  gcc -o CH5 CH5.c -lpthread
  after compile, you can run this program using bash command: ./CH5
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>
#define MIN_PID 300
#define MAX_PID 5000
#define NUM_THREADS 100
#define YES 0
#define NO 1 

sem_t SEM;

pthread_t tid [100];
int counter;
pthread_mutex_t lock;

void* trythis(void* arg) 
{ 
	
} 


struct PidTable{
	int PID; 
	int isAvailable;
}*pId;

int allocate_map(){ 
int i; 
pId=(struct PidTable *)calloc((MAX_PID-MIN_PID+1),sizeof(struct PidTable)); 
if(pId==NULL){ 
	return -1;
} 
pId[0].PID=MIN_PID; 
pId[0].isAvailable=YES;
for( i=1;i<MAX_PID-MIN_PID+1;i++){
	pId[i].PID=pId[i-1].PID+1; 
	pId[i].isAvailable=YES; 
} 
return 1;
}

int allocate_pid(){ 
int i ;
 for( i=0;i<MAX_PID-MIN_PID+1;i++){
	 if(pId[i].isAvailable==YES){ 
	 pId[i].isAvailable=NO;
	 return pId[i].PID; 
} 
}
 return -1;
}

void release_pid(int pid){ 
pId[pid-MIN_PID].isAvailable=YES;
}

void *processStart(void *id){ 
long tid=(long)id; 
int pid,executionTime; 
sem_wait(&SEM); 
unsigned long c = 0;
pthread_mutex_lock(&lock); 
pid=allocate_pid();
usleep(10000); 
sem_post(&SEM); 

counter += 1; 
	printf("\n Process %d has started\n", counter); 

	for (c = 0; c < (0xFFFFFFFF); c++) 
		; 
	
	if(pid!=-1){
	printf("\nThread %ld runnning….",tid);
	printf("\nNew Process Allocated Pid= %d \n",pid);
	executionTime=rand()%10;  //random execution time
	sleep(executionTime);     //sleep time for wait for the current thread for a specified time
	printf("Process %d releasing pid \n",pid);
	release_pid(pid); 
} 
	
	printf("\n Process %d has finished\n", counter); 

	pthread_mutex_unlock(&lock); 
	
	return NULL; 

pthread_exit(NULL);

	
}

//method main
int main(){ 
allocate_map(); 
srand(time(NULL)); 
void *status;
int i;
int ret=0;
int c=0;
int error;
pthread_t thread[100];  
sem_init(&SEM,0,1);
printf("\nYehezkiel V / 19340006\n"); 


if (pthread_mutex_init(&lock, NULL) != 0) { 
		printf("\n mutex init has failed\n"); 
		return 1; 
	} 

	while (c < 0) { 
		error = pthread_create(&(tid[c]), 
							NULL, 
							&processStart, NULL); 
		if (error != 0) 
			printf("\nThread can't be created :[%s]", 
				strerror(error)); 
		c++; 
	} 

for(i=0;i<NUM_THREADS;i++){ 
ret=pthread_create(&thread[i],NULL,processStart,(void *)(i+1)); 
if(ret){
	printf("\nError creating thread");
	exit(1);
	}
}
for(i=0; i<NUM_THREADS; i++) { 
ret = pthread_join(thread[i], &status); 
if (ret) {
	printf("\nERROR; return code from pthread_join() is %d ", ret); 
	exit(-1); 
}
}
	pthread_join(tid[c], NULL); 
	 
	pthread_mutex_destroy(&lock); 

return 0;
}
