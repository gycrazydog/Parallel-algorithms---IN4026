#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

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
  int nrT;
  int n;
} tThreadArg;


pthread_t callThd[NUM_THREADS];
pthread_mutex_t mutexpm;
pthread_barrier_t barr, internal_barr;

// Seed Input
int A[NMAX];

// Subset
int B[NMAX];

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

void* par_function(void* a){
	/* The code for threaded computation */
	// Perform operations on B
	tThreadArg *temp ;
	temp = (tThreadArg *)a;
	//pthread_barrier_wait(&barr);
	printf("id = %d\n",temp->id);
	return (void *)0;
}

int main ()
{
  	struct timeval startt, endt, result;
	int i, j, k, nt, t, n, c;
	void *status;
   	pthread_attr_t attr;
  	tThreadArg x[NUM_THREADS];
	
  	result.tv_sec = 0;
  	result.tv_usec= 0;

	/* Generate a seed input */
	srand ( time(NULL) );
	for(k=0; k<NMAX; k++){
		A[k] = rand();
	}
	printf("aaaaaaaaa\n");
   	/* Initialize and set thread detached attribute */
   	pthread_attr_init(&attr);
   	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	printf("|NSize|Iterations|Seq|Th01|Th02|Th04|Th08|Par16|\n");
	// for each input size
	for(c=0; c<1; c++){
		
		n=Ns[c];
		printf("| %d | %d |\n",n,TIMES);

		/* Run threaded algorithm(s) */
		for(nt=4; nt<=4; nt=nt<<1){

			result.tv_sec=0; result.tv_usec=0;
			for (j=1; j<=nt; j++)
        		{
				x[j].id = j; 
				x[j].nrT=nt; // number of threads in this round
				x[j].n=n;  //input size
				pthread_create(&callThd[j-1], &attr, par_function, (void *)&x[j]);
			}
			for(j=0; j</*NUMTHRDS*/nt; j++)
			{
				pthread_join(callThd[j], &status);
			}
			printf("after join!");
   			//result.tv_usec += (endt.tv_sec*1000000+endt.tv_usec) - (startt.tv_sec*1000000+startt.tv_usec);
			//printf("b %ld.%06ld | ", result.tv_usec/1000000, result.tv_usec%1000000);
    			pthread_barrier_destroy(&barr); 
		}
		printf("\n");
	}
	//	pthread_exit(NULL);
}
