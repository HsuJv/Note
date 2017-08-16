#ifndef LINEAR_LIST_H
#define LINEAR_LIST_H


#ifndef IOSTREAM_H
#define IOSTREAM_H

#include <iostream>
using namespace std;

#endif // IOSTREAM_H

template <class T>
class linearList
{
public:
	virtual bool IsEmpty() const = 0;
	virtual int Length() const = 0;
	virtual bool Find(int i, T& x) const = 0;
	virtual int Search(T x) const = 0;
	virtual bool Insert(int i, T x)  = 0;
	virtual bool Delete(int i) = 0;
	virtual bool Update(int i, T x) = 0;
	virtual void Output(ostream& out) const = 0;
};

#endif // LINEAR_LIST_H
