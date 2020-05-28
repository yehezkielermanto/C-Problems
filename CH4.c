//chapter 4.20
/*
 compile this program : gcc -o CH4 CH4.c -lpthread
 run this program after compile : ./CH4
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>
#include<semaphore.h>
#define MIN_PID 300
#define MAX_PID 5000
#define NUM_THREADS 100
#define YES 0
#define NO 1 

sem_t SEM;

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
pid=allocate_pid();
usleep(10000); 
sem_post(&SEM); 
if(pid!=-1){
	printf("\nThread %ld runnning….",tid);
	printf("\nNew Process Allocated Pid= %d \n",pid);
	executionTime=rand()%10;  //random execution time
	sleep(executionTime);     //sleep time for wait for the current thread for a specified time
	printf("Process %d releasing pid \n",pid);
	release_pid(pid); 
} 
pthread_exit(NULL);
}

int main(){ 
allocate_map(); 
srand(time(NULL)); 
void *status;
int i;
int ret=0;
pthread_t thread[100];  // 100 threads
sem_init(&SEM,0,1);
printf("\nYehezkiel V / 19340006\n"); 
for(i=0;i<NUM_THREADS;i++){ 
ret=pthread_create(&thread[i],NULL,processStart,(void*)(i+1)); 
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
return 0;
}
