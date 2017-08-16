#include<stdio.h>
#include<stdlib.h>

#define N 2

struct Student{
	int id;
	char name[20];
	double math, ch, eng;//maths,chinese,english
	double aver;
};//struct Studentdent

int comp(const void *a, const void *b){
	struct Student *c = (struct Student *)a;
	struct Student *d = (struct Student *)b;
	return (c->aver < d->aver)?-1:1;
}

void Input(struct Student *pa, int n){
	int i;
	for (i = 0; i < n; i++){
		printf("Input student's id, name, score:");
		scanf("%d%s%lf%lf%lf", &pa[i].id, &pa[i].name, &pa[i].math, &pa[i].ch, &pa[i].eng);
		pa[i].aver = (pa[i].math+pa[i].ch+pa[i].eng)/3;
	}
}

void Sort(struct Student *pa, int n){
	qsort(pa, n, sizeof(*(pa+0)), comp);
}

void Output(const struct Student *pa, int n){
	int i;
	for (i = 0; i < n; i++){
		printf("Id %d's info:\n", pa[i].id);
		printf("Name : %s\nEnglish score : %f\n", pa[i].name, pa[i].eng);
		printf("Math score : %f\nChinese score : %f\n", pa[i].math, pa[i].ch);
		printf("Average score : %f\n", pa[i].aver);
	}
}

int main(){
	struct Student s[N];
	int i;
	Input(s, N);
	for (i = 0; i < N; i++){
		int k;
		k = 1;
		if (s[i].math < 60) k = 0;
		else if (s[i].ch < 60) k = 0;
		else if (s[i].eng < 60) k = 0;
		if (!k){
			printf("Id %d failed.\n", s[i].id);
			printf("Name : %s\nEnglish score : %f\n", s[i].name, s[i].eng);
			printf("Math score : %f\nChinese score : %f\n", s[i].math, s[i].ch);
			printf("Average score : %f\n", s[i].aver);
		}
	}
	Sort(s, N);
	Output(s, N);
	return 0;
}
