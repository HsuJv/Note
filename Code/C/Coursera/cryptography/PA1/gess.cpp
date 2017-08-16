#include<stdio.h>
#include<string.h>

int main(){
	freopen("key.txt","r",stdin);
	int key[8];
	memset(key,0,sizeof(key));
	for(int i=0;i<7;i++)
	   scanf("%d",key+i);
    freopen("c.txt","r",stdin);
    int i,step;
    step=0;
    while (scanf("%d",&i)==1){
         if (key[step%7]) printf("%c",i^key[step%7]);
         else printf("1");
         step++;
    }
	return 0;
}
