#include<stdio.h>
#include<stdlib.h>

#define N 2

struct Student{
	char ID[20];
	char name[30];
	int age;
	double score;
};

int comp(const void *a, const void *b){
	struct Student *c = (struct Student *)a;
	struct Student *d = (struct Student *)b;
	return (c->score > d->score)?-1:1;
}

void Input(struct Student *pa, int n){
	int i;
	FILE *fout;
	for (i = 0; i < n; i++){
		printf("Input student's id, name, age, score:");
		scanf("%s%s%d%lf", &pa[i].ID, &pa[i].name, &pa[i].age, &pa[i].score);
	}
	fout = fopen("out.dat", "wb");
	fwrite(pa, sizeof(*(pa+0)), N, fout);
	fclose(fout);
}

void Readout(struct Student *pa, int n){
	FILE *fin;
	int i;
	fin = fopen("out.dat", "rb");
	fread(pa, sizeof(struct Student), N, fin);
	fclose(fin);
	for (i = 0; i < n; i++)
		printf("%s %s %d %lf ", pa[i].ID, pa[i].name, pa[i].age, pa[i].score);
}

void Sort(struct Student *pa, int n){
	qsort(pa, n, sizeof(*(pa+0)), comp);
}

void Output(const struct Student *pa, int n){
	int i;
	for (i = 0; i < n; i++){
		printf("Id %s's info:\n", pa[i].ID);
		printf("Name : %s\nAge : %d\n", pa[i].name, pa[i].age);
		printf("Score : %f\n", pa[i].score);
	}
}

int main(){
	struct Student s[N];
	Input(s, N);
	Readout(s, N);
	Sort(s, N);
	Output(s, N);
	return 0;
}
