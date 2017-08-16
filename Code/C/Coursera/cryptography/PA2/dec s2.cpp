#include<stdio.h>
#include<string.h>
int main(){
	int key[35];
//	freopen("c.txt","r",stdin);
	freopen("key(ulti).txt","r",stdin);
	for (int i=1;i<=31;i++)
	  scanf("%d",key+i);
	char a[100];
	int a1[35];
	FILE *f1,*fans;
	f1=fopen("c7.txt","r");
	for (int i=1;i<=62;i++)
		fscanf(f1,"%c",a+i);
	fclose(f1);
	memset(a1,0,sizeof(a1));
	int j=1;
	for (int i=1;i<=62;i++){
	    if (a[i]>=65) a1[j]+=(a[i]-55);
	      else a1[j]+=(a[i]-48);
		if (i%2)
			a1[j]*=16;
		else j++;
	}
	fans=fopen("p.txt","a");
	for(int i=1;i<=31;i++)
	  fprintf(fans,"%c",(key[i]^a1[i]));
	fprintf(fans,"\n");
	return 0;
}
