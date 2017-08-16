#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char s[20];
}string;

int cmp( const void *a , const void *b ) { 
	string *c = (string *)a; 
	string *d = (string *)b; 
	return strcmp(c->s, d->s); 
} 

void scan(string *str){
	int i;
	for (i = 0; i < 10; i++)
		gets(str[i].s);
}

void print(string *str){
	int i;
	for (i = 0; i < 10; i++)
		printf ("%s\n", str[i].s);
}

int main(){
	string str[10];
	freopen("in.txt", "r", stdin);
	scan(str);
	qsort(str, 10, sizeof(str[0]), cmp);
	print(str);
	return 0;
}