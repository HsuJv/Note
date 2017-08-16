#ifndef SORT_H
#define SORT_H

#ifndef IOSTREAM
#define IOSTREAM

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#endif // IOSTREAM

template <class T>
extern void qSort(T a[], int b, int c);

template <class T>
void swap(T &a, T &b){
	T t = a;
	a = b;
	b = t;
}

template <class T>
void selectSort(T a[], int n){
	int small;
	for (int i = 0; i < n - 1; i++){
		small = i;
		for (int j = i + 1; j < n; j++)
			if (a[j] < a[small]) small = j;
		swap<T>(a[i], a[small]);
	}
}

template <class T>
void insertSort(T a[], int n){
	for (int i = 1; i < n; i++){
		int j = i;
		T t = a[i];
		while(j && t < a[j-1]) 
		    a[j] = a[(j--)-1];
		a[j] = t;
	}
}

template <class T>
void bubbleSort(T a[], int n){
	int i = n-1, j, last;
	while (i){
		last = 0;
		for (int j = 0; j < i; j++)
			if (a[j+1] < a[j]){
				swap<T>(a[j+1], a[j]);
				last = j;
			}
		i = last;
	}
}

template <class T>
void quickSort(T a[], int n){
	qSort<T>(a, 0, n-1);
}

template <class T>
void exQSort(T a[], int l, int r){
	int i, j;
	if (r - l < 9) insertSort(a+l, r-l+1);
	else if (l < r){
		i = l;
		j = r + 1;
		do{
			do{
				i++;
			}while(a[i] < a[l]);
			do{
				j--;
			}while(a[j] > a[l]);
			if(i < j) swap<T>(a[i], a[j]);
		}while(i < j);
		swap<T>(a[l], a[j]);
		qSort(a, l, j-1);
		qSort(a, j+1, r);
	}
}

template <class T>
void qSort(T a[], int l, int r){
	int i, j;
	if (l < r){
		i = l;
		j = r + 1;
		do{
			do{
				i++;
			}while(a[i] < a[l]);
			do{
				j--;
			}while(a[j] > a[l]);
			if(i < j) swap<T>(a[i], a[j]);
		}while(i < j);
		swap<T>(a[l], a[j]);
		qSort(a, l, j-1);
		qSort(a, j+1, r);
	}
}

template <class T>
void merge(T a[], int i1, int j1, int i2, int j2){
	T *t = new T[j2-i1+1];
	int i = i1, j = i2, k = 0;
	while(i <= j1 && j <= j2) {
	    if (a[i] <= a[j]) t[k++] = a[i++];
	    else t[k++] = a[j++];
	}
	while (i <= j1) t[k++] = a[i++];
	while (j <= j2) t[k++] = a[j++];
	for (i = 0; i < k; i++) a[i1++] = t[i];
	delete[] t;
}

template <class T>
void mergeSort(T a[], int n){
	int i1, j1, i2, j2;
	int size = 1;
	while (size < n){
		i1 = 0;
		while(i1+size < n) {
		    i2 = i1 + size;
		    j1 = i2 - 1;
		    if (n-i2 < size) j2 = n - 1;
		    else j2 = i2 + size - 1;
		    merge(a, i1, j1, i2, j2);
		    i1 = j2 + 1;
		}
		size <<= 1;
	}
}

template <class T>
void adjustDown(T a[], int r, int j){
	int child = r*2 + 1;
	T t = a[r];
	while(child <= j) {
	    if ((child<j) && (a[child]<a[child+1])) child++;
	    if (t >= a[child]) break;
	    a[(child-1)>>1] = a[child];
	    child = child*2 + 1;
	}
	a[(child-1)>>1] = t;
}

template <class T>
void heapSort(T a[], int n){
	for (int i = (n-2)>>1; i > -1; i--) adjustDown(a, i, n-1);
	for (int i = n-1; i; i--){
		swap<T>(a[0], a[i]);
		adjustDown(a, 0, i-1);
	}
}


#endif // SORT_H
