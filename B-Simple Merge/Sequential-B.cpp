#include<iostream>
using namespace std;
int main(){
	int A[] = {28,36,40,61,68,71,123,149};
	int B[] = {2,5,18,21,24,29,31,33,
		34, 35, 47, 48, 49, 50, 52, 62,
		66, 70, 73, 80, 88, 89, 114, 124,
		125, 131, 143, 144, 145, 148, 155, 159};
	int C[40];
	int ptrA = 0 , ptrB = 0,ptrC=0;
	while(ptrA<8&&ptrB<32) C[ptrC++] = A[ptrA]<B[ptrB] ? A[ptrA++] : B[ptrB++];	
	while(ptrA<8) C[ptrC++] = A[ptrA++];
	while(ptrB<32) C[ptrC++] = B[ptrB++];
	for(int i = 0 ; i < 40 ; i ++) cout << C[i] << endl;
	return 0;
}
