#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(){
	int i,dig=0;
	char a[5];
	scanf ("%s", a);
	for (i=0; i<4; i++)
		if (!isdigit(a[i]) && !(tolower(a[i]) >= 97 && tolower(a[i]) <= 102)){
			printf ("Original data error\n");
			return 0;
		}
	i=0;
	do{
		if (!isdigit(a[i])) 	a[i] = tolower(a[i]) - 97 + 10;
		else a[i] = a[i] - 48;
		dig = dig * 16 + a[i++];
	}while(i<4);
	printf ("The dec data is:%d\n",dig);
	return 0;
}
