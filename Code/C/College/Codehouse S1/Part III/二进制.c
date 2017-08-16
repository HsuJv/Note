#include<stdio.h>
#include<stdlib.h>

int n, bin[2000], i;

int main(){
	scanf ("%o", &n);
	while (n){
		if (n & 1) bin[i++] = 1;
		else bin[i++] = 0;
		n >>= 1;
	}
	while (i)
		printf ("%d", bin[--i]);
	return 0;
}
