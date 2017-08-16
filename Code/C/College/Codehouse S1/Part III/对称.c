#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int judge(int t[][5]){
	int i, j;
	for (i = 0; i < 3; i++)
		for (j = 0; j < i; j++)
			if (t[i][j] != t[j][i]) return 0;
	return 1;
}

int main(){
	int t[5][5], i, j;
	memset (t, 0, sizeof(t));
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4 ;j++)
			scanf("%d",&t[i][j]);
	if (judge(t))	printf("Yes\n");
	else	printf ("No\n");
	return 0;
}
