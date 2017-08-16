#include<stdio.h>
#include<ctype.h>

int main(){
	char ch;
	FILE *fout;
	freopen("in.txt", "r", stdin);
	fout = fopen("out.txt", "wb");
	while(scanf("%c", &ch) == 1){
		printf("%c", ch);
		if (isalpha(ch)) fprintf(fout, "%d ", ch);
	}
	fclose(fout);
	return 0;
}