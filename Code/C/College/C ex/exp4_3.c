#include<stdio.h>

int l_dia(int a[][5]){
	int i, sum = 0;
	for (i = 0; i < 5; i++)
		sum += a[i][i];
	return sum;
}

int m_dia(int a[][5]){
	int i, sum = 0;
	for (i = 0; i < 5 ; i++)
		sum += a[i][4-i];
	return sum;
}

void print(int a[][5]){
	printf("The sum of lead diagonal is %d\n", l_dia(a));
	printf("The sum of minor diagonal is %d\n", m_dia(a));
}

int main(){
	int a[5][5], i, j;
	freopen("in.txt", "r", stdin);
	for (i = 0; i < 5; i++)
		for (j = 0; j < 5; j++)
			scanf("%d", &a[i][j]);
	print(a);
	return 0;
}