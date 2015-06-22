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
int A[] = {28,36,40,61,68,71,123,149};
int B[] = {2,5,18,21,24,29,31,33,
                34, 35, 47, 48, 49, 50, 52, 62,
                66, 70, 73, 80, 88, 89, 114, 124,
                125, 131, 143, 144, 145, 148, 155, 159};
int C[40];
main(){
    int i;
    int n = 40;
    #pragma omp parallel shared(A,B,n) private(i)
	{
		for (i=0; i < 8; i++)
		{
                        int num = A[i];
			int l = 0,r = 31;
                        while(l<=r){
                                int mid = (l+r)/2;
                                if(num>B[mid]) l = mid+1;
                                else r = mid-1;
                        }
                        C[i+l] = num;
		}
	} /* end of parallel section */
    #pragma omp parallel shared(A,B,n) private(i)
	{
		for (i=0; i < 32; i++)
		{
			int num = B[i];
                        int l = 0,r = 7;
                        while(l<=r){
                                int mid = (l+r)/2;
                                if(num>A[mid]) l = mid+1;
                                else r = mid-1;
                        }
                        C[i+l] = num;
		}
	} /* end of parallel section */
        for(int i = 0 ; i < 40 ; i ++)
	printf("%d %d\n",i,C[i]);
}