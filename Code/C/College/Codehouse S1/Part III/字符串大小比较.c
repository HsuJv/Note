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


int main(){
	string str[6];
	int i;

	for (i = 0; i < 6; i++)
		gets(str[i].s);
	qsort(str,6,sizeof(str[0]),cmp); 
	for (i = 0; i < 6; i++)
		printf ("%s  ", str[i].s);
	return 0;
}

