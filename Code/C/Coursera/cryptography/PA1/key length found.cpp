#include<stdio.h>
#include<string.h>

int main(){
    int i,sum,p[260],t,step;
    double pi;
    FILE *fin;
    for(int k=2;k<=13;k++){
    	fin=fopen("c.txt","r");
    	sum=0;step=0;
    	memset(p,0,sizeof(p));
    	while (fscanf(fin,"%d",&i)!=EOF){
    	  if (step%k==0) {
    	  	sum++;
    	  	p[i]++;
    	  }
    	  step++;
    	}
    	pi=0.0;
    	sum*=sum;
    	for(t=0;t<=255;t++)
    	  pi+=(p[t]*p[t]/(double)sum);
    	printf("%d:%f\n",k,pi);
    	fclose(fin);
    }
    return 0;
}
