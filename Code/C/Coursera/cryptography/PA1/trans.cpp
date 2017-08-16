#include<stdio.h>

int main(){
	FILE *fin;
	int j,temp;
	char i;
	freopen("c.txt","w",stdout);
	fin=fopen("in.txt","r");
	j=1;temp=0;
    while (fscanf(fin,"%c",&i)!=EOF){
      if (i>=65) temp+=(i-55);
        else temp+=(i-48);
      if(j%2) temp*=16;
        else {
        	printf("%d ",temp);
        	temp=0;
        }
        j++;
    }
    return 0;
}
