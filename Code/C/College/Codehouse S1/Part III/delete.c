#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int a[20];

int main(){
	  int i=0,del;
	  for (;;i++){
	  	scanf("%d",a+i);
	  	if (a[i]==0) break;
	  }
	  scanf("%d",&del);
	  printf("Before delete,elements are:\n");
	  for (i=0;;i++){
	  	printf("%5d",a[i]);
	  	if (a[i]==0) break;
	  }
	  i=0;
	  while(a[i]!=del&&a[i]!=0) i++;
	  if (a[i]==0){
	  	printf("\ndoes not exist,no operating!\n");
	  	return 0;
	  }
	  printf("\nAfter delete,elements are:\n");
	  for (i=0;;i++){
	  	if (a[i]!=del)	printf("%5d",a[i]);
	  	if (a[i]==0) break;
	  }
	  return 0;
}
