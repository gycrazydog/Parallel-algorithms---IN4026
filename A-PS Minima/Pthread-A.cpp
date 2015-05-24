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
  int n;
  int* A;
  int* B;
  int* C;
  int* Z;
} tThreadArg;


pthread_mutex_t mutexpm;
pthread_barrier_t barr, internal_barr;


void init(int n){
	/* Initialize the input for this iteration*/
	// B <- A
	printf("init");
}

void seq_function(int m){
	/* The code for sequential algorithm */
	// Perform operations on B
	printf("sequential");
}

void* min_function(void* a){
	tThreadArg *temp ;
	temp = (tThreadArg *)a;
	int cur_id = temp->id;
	int *B = temp->B;
	int *A = temp->A;
	B[cur_id] = min(A[2*cur_id-1],A[2*cur_id]);
	return (void *)0;
}
void* prefix_function(void* a){
	tThreadArg *temp ;
	temp = (tThreadArg *)a;
	int cur_id = temp->id;
	int *Z = temp->Z;
	int *A = temp->A;
	int *C = temp->C;
	if(cur_id==1) C[1] = A[1];
	else if(cur_id%2==1) C[cur_id] = min(A[cur_id],Z[(cur_id-1)/2]);
	else C[cur_id] = Z[cur_id/2];
	return (void *)0;
}
void* suffix_function(void* a){
        tThreadArg *temp ;
        temp = (tThreadArg *)a;
        int cur_id = temp->id;
        int *Z = temp->Z;
        int *A = temp->A;
        int *C = temp->C;
	int n = temp->n;
        if(cur_id==n) C[n] = A[n];
        else if(cur_id%2==0) C[cur_id] = min(A[cur_id],Z[cur_id/2+1]);
        else C[cur_id] = Z[(cur_id+1)/2];
        return (void *)0;
}

int* cum_ps(int* A,int n,bool isPrefix){
	int B[n/2+1];
	int* C = new int[n+1];
	int* Z ;
//		printf("enter %d\n",n);
	if(n==1){
		C[1] = A[1];
		return C;
	}
	pthread_attr_t attr;
	tThreadArg x[n];
	pthread_t callThd[n];
   	pthread_attr_init(&attr);
   	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	void *status;
	for (int j=1; j<=n/2; j++)
        {
		x[j].id = j; 
		x[j].A= A;
		x[j].B = B;
		x[j].C = C;
		pthread_create(&callThd[j-1], &attr, min_function, (void *)&x[j]);
	}
	for(int j=0; j<n/2; j++)
	{
		pthread_join(callThd[j], &status);
	}
	Z = cum_ps(B,n/2,isPrefix);
	//for(int i = 1 ; i <= n/2 ; i ++) printf("Z[%d] = %d\n",i,Z[i]);	
	for (int j=1; j<=n; j++)
        {
		x[j].id = j; 
		x[j].A = A;
		x[j].C = C;
                x[j].Z = Z;
		x[j].n = n;
		void* (*assign_function)(void*) = isPrefix ? prefix_function:suffix_function;
		pthread_create(&callThd[j-1], &attr, assign_function, (void *)&x[j]);
	}
	for(int j=0; j<n; j++)
	{
		pthread_join(callThd[j], &status);
	}
//	printf("after join!\n");
    	return C;
}
int main ()
{
  	struct timeval startt, endt, result;
   	
	srand ( time(NULL) );

	int a[] = { 111111111, 58, 89, 32, 73, 131, 156, 30, 29, 141, 37, 133, 151, 88, 53,
			122, 126, 131, 49, 130, 115, 16, 83, 40, 145, 10, 112, 20, 147, 14,
			104, 111, 92 };
	int* prefix = cum_ps(a,32,true);
	int* suffix = cum_ps(a,32,false);
	for(int i = 1 ; i <= 32 ; i ++)
	printf("%d\t%d\t%d\n",i,prefix[i],suffix[i]);
	printf("over");
	return 0;
}
