#include <stdio.h>
#include<math.h>
double fun(int n){
double s=0.0;
int i;
for(i=1;i<n;i++)
	if(!(i%3 || i%7))
		s=s+i;
	s=sqrt(s);
return s;
}

int main(){
int n;
scanf("%d",&n);
printf("sum=%lf\n",fun(n));
return 0 ;
}