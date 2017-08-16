#include<stdio.h>
#include<string.h>
int p[1000],i;

void init(){
    int i,j;
    for (i=2;i<=1000;i++)
        if (!p[i])
            for(j=2*i;j<=1000;j+=i)
                p[j]++;
}

void print(){
    int i,count=0;
    for (i=100;i<=1000;i++){
        if (!p[i]){
            count++;
            printf("%6d",i);
        }
        if (count==5){
            count=0;
            printf("\n");
        }
    }
    printf("\n");
}

int main(){
    memset(p,0,sizeof(p));
    init();
    print();
    return 0;
}