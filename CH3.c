/*
 Compile this program : gcc -o CH3 CH3.c
 run this program after compile : ./CH3
*/
//Chapter 3.20
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN_PID 300
#define MAX_PID 5000
#define cb CHAR_BIT

int sz = MAX_PID - MIN_PID + 1;

unsigned char *b;

int allocate_map();
int allocate_pid();
void release_pid(int pid);

/* Creates and initializes a data structure for representing pids;
 returns —1 if unsuccessful, 1 if successful */
int allocate_map() {
    b = (unsigned char*)malloc((sz+cb-1)/cb * sizeof(char));
    if (b) return 1;
    return -1;
}

/* Allocates and returns a pid; returns -1
if unable to allocate a pid (all pids are in use) */
int allocate_pid() {
    int i = 0;
    int pid = b[i/cb] & (1 << (i & (cb-1)));
    while (pid != 0) {
        i++;
        pid = b[i/cb] & (1 << (i & (cb-1)));
        }

    if (i+MIN_PID > MAX_PID) return -1;
    b[i/cb] |= 1 << (i & (cb-1));
    return i+MIN_PID;
}

/* Releases a pid */
void release_pid(int pid) {
    if (pid < 300) {
        printf("\nInvalid PID: It should lie between 300 and 5000.");
        return;
    }
    int i = pid - MIN_PID;
    b[i/cb] &= ~(1 << (i & (cb-1)));
}

//method main
int main() 
{
    int map = allocate_map();
    printf("\nName : Yehezkiel V\n");
	printf("NPM  : 19340006\n");
	if (map == 1) {
        printf("\nData Structure initialized.\n");
        int id = 0, i = 0;
        while (i < 15) {
            int val = allocate_pid();
            printf("\nProcess %d: pid = %d", i+1, val);
            i++;
        }
        release_pid(303); printf("\nProcess 303 released.");
        release_pid(305); printf("\nProcess 305 released.");
        int val = allocate_pid(); 
		printf("\nProcess %d : pid = %d\n", i+1, val);
    }
    else printf("\nFailed to initialize data structure.\n");
}
