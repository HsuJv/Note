#include<stdio.h>

void scan(int a[][3]){
	int i,j;
	for (i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			scanf("%d", &a[i][j]);
}

void print(int a[][3]){
	int i,j;
	printf("The original is :\n");
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++)
			printf("%d ", a[i][j]);
		printf("\n");
	}
}

void tr(int a[][3]){
	int i,j;
	printf("The transposition is :\n");
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++)
			printf("%d ", a[j][i]);
		printf("\n");
	}
}

int main(){
	int arr[3][3];
	freopen("in.txt", "r", stdin);
	scan(arr);
	print(arr);
	tr(arr);
	return 0;
}