#include <stdio.h>
int f(int a[3][3], int *max,int n){
	int i, j, s = 0;
	*max = a[0][0];
	for(i = 0; i < n; i++){
 					 s +=  a[i][i];
	 				for (j = 0; j < n; j++)
					if (a[i][j] > *max) *max = a[i][j];
					}
    return s;
}

int main(){
	int a[3][3]={1, -2, 9, 4, -8, 6, 7, 0, 5};
	int max,sum; /*max�����Ԫ��ֵ��sum��Ԫ�صĺ�ֵ*/
	sum = f(a, &max, 3);
	printf("sum=%d,max=%d\n", sum, max);
	return 0;
}
