#include <omp.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include<iostream>
#include<stack>
#include<algorithm>
using namespace std;
int main(){
	int linkedList[] = {14,13,5,16,11,10,9,12,0,8,7,15,4,3,2,1},ans[16];
	bool used[16] = {0};
	stack<int> Stack;
        #pragma omp parallel shared(linkedList,used,Stack) private(i)
        {
            for(int i = 0 ; i <= 15 ; i ++){
		if(!used[i]){
			int cur = i;
			Stack.push(cur);
			used[cur] = true;
			int next = linkedList[cur]-1;
			while(next!=-1&&!used[next]){
				Stack.push(next);
				used[next] = true;
				cur = next;
				next = linkedList[cur]-1;
			}
			int step = (next >= 0 ? ans[next]+1:0);
			while(!Stack.empty()){
				ans[Stack.top()] = step++;
				Stack.pop();
			}
		}
            }    
        }
	
	for(int i = 0 ; i <= 15; i ++) cout << ans[i] << endl;
}
