#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(){
	char s[60];
	long long i = 0, sum = 0, k = 0;
	scanf ("%[^\n]", s);
	while (s[i] != '\0'){
		if (isdigit(s[i])) 	{
			sum =  sum * 10 + s[i] - 48;
			k = 1;
		}
		i++;
	}
	if (k)	printf ("%.4f\n", (double) sum);
	else	printf ("the digital string is empty!\n");
	return 0;
}
