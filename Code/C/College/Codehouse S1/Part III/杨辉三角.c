#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(){
	int t[12][12], i, j, n;
	memset (t, 0, sizeof(t));
	t[1][1] = 1;
	scanf ("%d", &n);
	for (i = 2; i <= n; i++)
		for (j = 1; j <= i; j++)
			t[i][j] = t[i-1][j-1] + t[i-1][j];
	for (i = 1; i <= n; i++){
		for (j = 1; j <= i; j++)
			printf ("%5d", t[i][j]);
		printf("\n");
	}
	return 0;
}
