#include<iostream>
#include<stdio.h>
#include<math.h>
using namespace std;
int main() {
	int a[] = { 58, 89, 32, 73, 131, 156, 30, 29, 141, 37, 133, 151, 88, 53,
			122, 126, 131, 49, 130, 115, 16, 83, 40, 145, 10, 112, 20, 147, 14,
			104, 111, 92 };
	int prefix[32], suffix[32];
	int Max = 58,i;
	prefix[0] = a[0];
	for (i = 1; i <= 31; i++)
		prefix[i] = min(prefix[i - 1], a[i]);
	suffix[31] = a[31];
	for (i = 30; i >= 0; i--)
		suffix[i] = min(suffix[i + 1], a[i]);
	printf("i\tprefix\tsuffix\n");
	for (i = 0; i <= 31; i++)
		printf("%d\t%d\t%d\n", i, prefix[i], suffix[i]);
	return 0;
}
