#include <omp.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include<iostream>
#include<algorithm>
using namespace std;
#define CHUNKSIZE 100
#define N 32
int* cum_ps(int* A,int n,bool isPrefix){
    int B[n/2+1],i;
    int* C = new int[n+1];
    int* Z ;
    if(n==1){
        C[1] = A[1];
        return C;
    }
    #pragma omp parallel shared(A,B,n,isPrefix) private(i)
	{
		for (i=1; i <= n/2; i++)
		{
			B[i] = min(A[i*2-1],A[i*2]);
		}
	} /* end of parallel section */
    Z = cum_ps(B,n/2,isPrefix);
     #pragma omp parallel shared(A,Z,C,n,isPrefix) private(i)
	{
		for (i=1; i <= n; i++)
		{
                    if(isPrefix){
                        if(i==1) C[1] = A[1];
                        else if(i%2==1) C[i] = min(A[i],Z[(i-1)/2]);
                        else C[i] = Z[i/2];
                    }
                    else{
                        if(i==n) C[n] = A[n];
                        else if(i%2==0) C[i] = min(A[i],Z[i/2+1]);
                        else C[i] = Z[(i+1)/2];
                    }
		}
	} /* end of parallel section */
    return C;
}
main ()
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
