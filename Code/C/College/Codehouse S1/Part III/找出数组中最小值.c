#include <stdio.h>


int main(){
	int i = 0, n, min;
//	freopen ("in.txt", "r", stdin);
	while ((scanf ("%d", &n)) == 1){
		if (!i) min = n;
		else 
			if (!(i%2))
			   if (min > n) min = n;
        i++;
	}
	printf ("%d", min);
	return 0;
}
