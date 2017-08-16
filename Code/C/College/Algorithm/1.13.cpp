#include <iostream>
#include <stdlib.h>
using std::cin;
using std::cout;
using std::endl;

long C(int n, int m){
	if (!m || m == n) return 1;
	return C(n-1, m) + C(n-1, m-1);
}

long CO(int n, int m){
	long a[n+1][n];
	for (int i = 0; i <= n; i++){
		a[i][0] = 1;
		a[i][i] = 1;
		for (int j = 1; j < i ; j++ ){
			a[i][j] = a[i-1][j-1] + a[i-1][j];
		}
	}
	return a[n][m];
}

int main(){
	for (int i = 0; i < 11; i++){
		cout << C(10, i) << endl;
		cout << CO(10, i) << endl;
	}
	return 0;
}