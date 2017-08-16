#include<stdio.h>
#define PI 3.14159265

double radius,height;

int main(){
    printf("Plz input the radius and height:");
    scanf("%lf%lf",&radius,&height);
    printf("\nThe area is %.2f;\n",2*PI*radius*height+2*PI*radius*radius);
    printf("And the volumn is %.2f\n",PI*radius*radius*height);
    return 0;
}