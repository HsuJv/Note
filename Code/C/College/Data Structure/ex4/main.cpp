#include "../h/sort.h"
#include <stdlib.h>
#include <time.h> 
#define N 10001

template <class T>
void print(T A[],int n,const char *sort){
	cout << "After " << sort << "ed :";
//	for(int i=0;i<n;i++){
//		cout << A[i] << " ";
//	}
	cout << endl;
}

int main(){
	int n; 
	int *a, *b, *c, *d, *e, *f, *g; 
	cout << "Please input the number of the array:"; 
	cin >> n; 
	a = new int[n]; 
	b = new int[n]; 
	c = new int[n]; 
	d = new int[n]; 
	e = new int[n]; 
	f = new int[n]; 
	g = new int[n]; 
	
	srand(time(NULL)); 
	cout << "The random array is :"; 
	for(int i = 0; i < n; i++){		
		a[i] = rand() % N; 
		b[i] = a[i]; 
		c[i] = a[i]; 
		d[i] = a[i]; 
		e[i] = a[i]; 
		f[i] = a[i]; 
		g[i] = a[i]; 
		cout << a[i] << " "; 
	}
	cout << endl << endl << endl << endl << endl; 
	
	double timeStandard; 
	clock_t start, finish; 
	
	//SelectSort
	start = clock(); 
	selectSort<int>(a, n); 
	finish = clock(); 
	timeStandard = (double)(finish - start); 
	print<int>(a, n, "SelectSort"); 
	cout << "The time is :" << timeStandard << "ms" << endl << endl; 
				
	//InsertSort
	start = clock(); 
	insertSort<int>(b, n); 
	finish = clock(); 
	timeStandard = (double)(finish - start); 
	print<int>(b, n, "InsertSort"); 
	cout << "The time is :" << timeStandard << "ms" << endl << endl; 
	
	//BubbleSort
	start = clock(); 
	bubbleSort<int>(c, n); 
	finish = clock(); 
	timeStandard = (double)(finish - start); 
	print<int>(c, n, "BubbleSort"); 
	cout << "The time is :" << timeStandard << "ms" << endl << endl; 
	
	//QuickSort
	start = clock(); 
	quickSort<int>(d, n); 
	finish = clock(); 
	timeStandard = (double)(finish - start); 
	print<int>(d, n, "QuickSort"); 
	cout << "The time is :" << timeStandard << "ms" << endl << endl; 
	
	//MergeSort
	start = clock(); 
	mergeSort<int>(e, n); 
	finish = clock(); 
	timeStandard = (double)(finish - start); 
	print<int>(e, n, "MergeSort"); 
	cout << "The time is :" << timeStandard << "ms" << endl << endl; 
	
	//HeapSort
	start = clock(); 
	heapSort<int>(f, n); 
	finish = clock(); 
	timeStandard = (double)(finish - start); 
	print<int>(f, n, "HeapSort"); 
	cout << "The time is :" << timeStandard << "ms" << endl << endl; 
	
	//QSort
	start = clock(); 
	exQSort<int>(g, 0, n-1); 
	finish = clock(); 
	timeStandard = (double)(finish - start); 
	print<int>(g, n, "ExQuickSort"); 
	cout << "The time is :" << timeStandard << "ms" << endl << endl; 
	
	return 0; 
}
