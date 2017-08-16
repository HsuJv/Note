#ifndef QUEUE_H
#define QUEUE_H

#ifndef IOSTREAM
#define IOSTREAM

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#endif // IOSTREAM

template <class T>
class queue
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool isFull() const = 0;
	virtual bool getFront(T &x) const = 0;
	virtual bool enQueue(T x) = 0;
	virtual bool deQueue() = 0;
	virtual void clear() = 0;	
};

template <class T>
class seqQueue : public queue<T>
{
public:
	seqQueue(int mSize){
		maxSize = mSize;
		q = new T[maxSize];
		front = rear = 0;
	}
	~seqQueue(){ delete [] q;}
	bool isEmpty() const { return front == rear;}
	bool isFull() const { return (rear+1) % maxSize == front;}
	bool getFront (T &x) const{
		if(isEmpty()){
			cout << "Empty!" << endl; return false;
		}
		x = q[(front+1)%maxSize];
		return true;
	}
	bool enQueue(T x) {
		if (isFull()){
			cout << "Full!" << endl; return false;
		}
		q[(rear=(rear+1)%maxSize)] = x;
		return true;
	}
	bool deQueue(){
		if(isEmpty()){
			cout << "Underflow!" << endl; return false;
		}
		front = (front+1) % maxSize;
		return true;
	}
	void clear(){ front = rear = 0;}
private:
	int front, rear;
	int maxSize;
	T *q;
};

#endif // QUEUE_H
