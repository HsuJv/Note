#ifndef SEQ_LIST_H
#define SEQ_LIST_H


#ifndef LINEAR_LIST_H

#include "linearList.h"

#endif // LINEAR_LIST_H

template <class T>
class seqList : public linearList<T>
{
public:
	seqList(int mSize){
		maxLength = mSize;
		elements = new T[maxLength];
		n = 0;
	}
	~seqList() { delete[] elements;}
	bool IsEmpty() const {return n == 0;}
	int Length() const {return n;}
	bool Find(int i, T& x) const {
		if(i < 0 || i > n-1){
			cout<<"Out of Bounds"<<endl;
			return false;
		}
		x = elements[i];
		return true;
	}
	int Search(T x) const{
		for(int j = 0; j < n; j++)
			if (elements[j] == x) return j;
		return -1;
	}
	bool Insert(int i, T x){
		if (i < -1 || i > n-1){
			cout << "Out of Bounds" << endl;
			return false;
		}
		if (n == maxLength){
			cout << "OverFlow" << endl;
			return false;
		}
		for (int j = n-1; j > i; j--){
			elements[j+1] == elements[j];
		}
		n++;
		elements[i+1] = x;
		return true;
	}
	bool Delete(int i){
		if(!n){
			cout << "Underflow" << endl;
			return false;
		}
		if(i < 0 || i > n-1)
		{
			cout << "Out of Bounds" << endl; 
			return false;
		}
		for(int j = i; j < n; j++)	elements[j] = elements[j+1];
		n--;
		return true;
	}
	bool Update(int i, T x){
		if(i < 0 || i > n-1){
			cout << "Out of Bounds" << endl; 
			return false;
		}
		elements[i] = x;
		return true;
	}
	void Output(ostream& out) const {
		for(int i = 0; i < n; i++)	out << elements[i] << " ";
		out << endl;
	}
	void Reverse(){
		int i = 0,j = n-1;
		while(i < j){
			T t = elements[i];
			elements[i++] = elements[j];
			elements[j--] = t;
		}
	}
	bool deleteX(const T& x){
		bool ret = false;
		int del;
		while ((del = Search(x)) != -1)
			ret = Delete(del);
		return ret;
	}
private:
	int maxLength;
	T *elements;
	int n;
};

#endif // SEQ_LIST_H
