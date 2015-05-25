#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include<iostream>
#include<algorithm>
using namespace std;
// Number of threads
#define NUM_THREADS 32

// Number of iterations
#define TIMES 1

// Input Size
#define NSIZE 7
#define NMAX 262144
int Ns[NSIZE] = {4096, 8192, 16384, 32768, 65536, 131072, 262144};
typedef struct __ThreadArg {
  int id;
} tThreadArg;
pthread_barrier_t barr, internal_barr;
pthread_mutex_t mutexsum[17];
int linkedList[] = {0,14,13,5,16,11,10,9,12,0,8,7,15,4,3,2,1},dist[17];
void* Jump_function(void* a){
        tThreadArg *temp ;
        temp = (tThreadArg *)a;
        int cur_id = temp->id;
	if(cur_id!=linkedList[cur_id]) dist[cur_id] = 1;
	else dist[cur_id] = 0;
	pthread_barrier_wait(&barr);
	while(linkedList[cur_id]!=linkedList[linkedList[cur_id]]){
		printf("%d has father %d pointing to %d with dist = %d\n",cur_id,linkedList[cur_id],linkedList[linkedList[cur_id]],dist[cur_id]+dist[linkedList[cur_id]]);
		int next = linkedList[cur_id];
		pthread_mutex_lock(&mutexsum[cur_id]);
		pthread_mutex_lock(&mutexsum[next]);
		linkedList[cur_id] = linkedList[next];
		dist[cur_id] += dist[next];
		pthread_mutex_unlock(&mutexsum[cur_id]);
		pthread_mutex_unlock(&mutexsum[next]);
	}
        return (void *)0;
}
int main(){
	pthread_attr_t attr;
        tThreadArg x[17];
        pthread_t callThd[17];
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	void *status;
	if(pthread_barrier_init(&barr, NULL, 16))
        {
       		printf("Could not create a barrier\n");
                return -1;
        }
	for (int j=1; j<=16; j++)
        {
                x[j].id = j;
                pthread_create(&callThd[j], &attr, Jump_function, (void *)&x[j]);
        }
        for(int j=1; j<=16; j++)
        {
                pthread_join(callThd[j], &status);
        }
	for(int j=1; j <= 16 ; j ++)
	printf("%d %d\n",j,dist[j]-1);

}	
