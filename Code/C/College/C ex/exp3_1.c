#include<stdio.h>
#include<stdlib.h>

#define f(i,a,b) for(i=a;i<b;i++)
#define half_line 40

void DrawPic(int n, char c){
	int i,k;
	f(i,1,n+1){
		f(k,0,half_line-i)
			printf("%c",0x20);
		f(k,0,i*2-1)
			printf("%c",c);
		printf("\n");
	}
}

int main(){
	DrawPic(7,0x2a);
	DrawPic(11,0x40);
	DrawPic(20,0x24);
	return 0;
}
