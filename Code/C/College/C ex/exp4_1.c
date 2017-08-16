#include<stdio.h>
#include<stdlib.h>

int comp(const void *a, const void *b){
	return *(double *) a > *(double *)b ? 1 : -1;
}

int exist(double *a, double x){
	int i;
	for (i = 0; i < 10; i++)
		if (a[i] == x) return 1;
	return 0;
}

double max(double *a){
	int i, m = 0;
	for (i = 1; i < 10; i++)
		if(a[i] > a[m]) m = i;
	return a[m];
}

double aver(double *a){
	int i;
	double sum = 0.0;
	for (i = 0; i < 10; i++)
		sum += a[i];
	return sum/10;
}

void print(double *a){
	int i;
	for (i = 0; i < 10; i++)
		printf("%8f ", a[i]);
	printf("\n");
}

int main(){
	int i;
	double array[10], x;
	freopen("in.txt", "r", stdin);
	for(i = 0; i < 10; i++)
		scanf("%lf", array+i);
	qsort(array, 10, sizeof(double), comp);
	print(array);
	printf("Max = %f, Aver = %f\n", max(array), aver(array));
	scanf("%lf", &x);
	if (exist(array, x))	printf("%f is in array", x);
	else printf("%f is not in array", x);
	return 0;
}