#ifndef PRIO_QUEUE_H
#define PRIO_QUEUE_H

#ifndef IOSTREAM
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#endif // IOSTREAM

template<class T>
class prioQueue
{
public:
	prioQueue(int mSize = 20) : maxSize(mSize){
		n = 0;
		q = new T[maxSize];
	}
	~prioQueue(){ delete [] q;}
	bool isEmpty() const{ return n == 0;}
	bool isFull() const{ return n == maxSize;}
	void append(const T &x){
		if (isFull()){
			cout << "Overflow!" << endl;
			return;
		}
		q[n++] = x;
		adjustUp(n-1);
	}
	void serve(T &x){
		if (isEmpty()){
			cout << "Underflow!" << endl;
			return;
		}
		x = q[0]; q[0] = q[--n];
		adjustDown (0, n-1);
	}
private:
	void adjustDown(int r, int j){
		int child = 2 * r + 1;
		T temp = q[r];
		while(child <= j) {
		    if ((child<j) && (q[child]>q[child+1])) child++;
		    if (temp < q[child]) break;
		    q[(child-1)/2] = q[child];
		    child = 2 * child + 1;
		}
		q[(child-1)/2] = temp;
	}
	void adjustUp(int j){
		int i = j;
		T temp = q[i];
		while(i>0 && temp<q[(i-1)/2]) {
		    q[i] = q[(i-1)/2];
		    i = (i-1) / 2;
		}
		q[i] = temp;
	}
	T *q;
	int n, maxSize;
};

#endif // PRIO_QUEUE_H
