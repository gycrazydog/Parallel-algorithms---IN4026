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
typedef struct __ThreadArg {
  int id;
} tThreadArg;
int A[] = {28,36,40,61,68,71,123,149};
int B[] = {2,5,18,21,24,29,31,33,
                34, 35, 47, 48, 49, 50, 52, 62,
                66, 70, 73, 80, 88, 89, 114, 124,
                125, 131, 143, 144, 145, 148, 155, 159};
int C[40];
int Rab[8];
int Rba[32];
int Ns[NSIZE] = {4096, 8192, 16384, 32768, 65536, 131072, 262144};
void* Rab_function(void* a){
        tThreadArg *temp ;
        temp = (tThreadArg *)a;
        int num = A[temp->id];
	int l = 0,r = 31;
	while(l<=r){
		int mid = (l+r)/2;
		if(num>B[mid]) l = mid+1;
		else r = mid-1;
	}
	Rab[temp->id] = l;
        return (void *)0;
}
void* Rba_function(void* a){
        tThreadArg *temp ;
        temp = (tThreadArg *)a;
        int num = B[temp->id];
	int l = 0,r = 7;
        while(l<=r){
                int mid = (l+r)/2;
                if(num>A[mid]) l = mid+1;
                else r = mid-1;
        }
        Rba[temp->id] = l;
        return (void *)0;
}
void* Ca_function(void* a){
        tThreadArg *temp ;
        temp = (tThreadArg *)a;
        int cur_id = temp->id;
	C[cur_id+Rab[cur_id]] = A[cur_id];
	return (void *)0;
}
void* Cb_function(void* a){
        tThreadArg *temp ;
        temp = (tThreadArg *)a;
        int cur_id = temp->id;
        C[cur_id+Rba[cur_id]] = B[cur_id];
	return (void *)0;
}
int main(){
	pthread_attr_t attr;
        tThreadArg x[40];
        pthread_t callThd[40];
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        void *status;
	for (int j=0; j<=7; j++)
        {
                x[j].id = j;
                pthread_create(&callThd[j], &attr, Rab_function, (void *)&x[j]);
        }
        for(int j=0; j<=7; j++)
        {
                pthread_join(callThd[j], &status);
        }
	for (int j=0; j<=31; j++)
        {
                x[j].id = j;
                pthread_create(&callThd[j], &attr, Rba_function, (void *)&x[j]);
        }
        for(int j=0; j<=31; j++)
        {
                pthread_join(callThd[j], &status);
        }
	for( int j=0; j<=7; j++)
        {
                x[j].id = j;
                pthread_create(&callThd[j], &attr, Ca_function,(void *)&x[j]); 
        }
        for(int j=0; j<=7; j++)
        {
                pthread_join(callThd[j], &status);
        }
        for (int j=0; j<=31; j++)
        {
                x[j].id = j;
                pthread_create(&callThd[j], &attr, Cb_function, (void *)&x[j]);
        }
        for(int j=0; j<=31; j++)
        {
                pthread_join(callThd[j], &status);
        }
	for(int i = 0 ; i < 40 ; i ++)
	printf("%d %d\n",i,C[i]);
 
        return 0;
}

