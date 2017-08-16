#include<stdio.h>
#include<stdlib.h>

#define f(i, a, b) for(i = a; i < b; i++)

int comp(const void *a, const void *b){
	return *(double *) a > *(double *)b ? 1 : -1;
}
void scan(double *a){
	int i;
	f(i, 0, 10){
		scanf("%lf", a+i);
	}
}

void print_add(double *a){
	int i;
	printf("The address of every element in array is:\n");
	f(i, 0, 10)
		printf("%f\t%llu\n", a[i], &a[i]);
}

void aver_min_max(double *a){
	int i;
	double sum = 0.0, min = 1.0/0.0, max = -min;
	f(i, 0, 10){
		sum += *(a+i);
		if (*(a+i) < min) min = *(a+i);
		if (*(a+i) > max) max = *(a+i);
	}
	printf("Average = %f\n", sum/10);
	printf("Min = %f, Max = %f\n", min, max);
}

void print_sorted(double *a){
	int i;
	printf("The array after sorted is:\n");
	f(i, 0, 10)
		printf("%f\n", *(a+i));
}

int main(){
	double array[10], *p;
	p = array;
	freopen("in.txt", "r", stdin);
	scan(p);
	print_add(array);
	aver_min_max(p);
	qsort(p, 10, sizeof(double), comp);
	print_sorted(p);
	return 0;
}
