#include <stdio.h>
void fun(char *str ){
	 int i, j;
	 for (i = 0, j = 0; j < 5 ; i++)
	 if ( str[i] >= '0' && str[i] <= '9') str[j++] = str[i];
	 str[j] = '\0';
}

int main(){
	char str[100] = "Now Time is 6:12:09 AM.";
	fun (str);
	printf ("%s", str);
	return 0;
}
