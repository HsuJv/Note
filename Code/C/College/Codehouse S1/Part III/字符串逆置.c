#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void reverse (char *s){
	char *p = s, *q = p+strlen(s)-1, t;
	while (p<q){
		t = *p;
		*(p++) = *q;
		*(q--) = t;
	}
}

int main(){
	char s[200];
	gets (s);
	reverse (s);
	puts (s);
	return 0;
}
