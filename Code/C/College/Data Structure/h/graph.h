#ifndef GRAPH_H
#define GRAPH_H

#ifndef IOSTREAM
#define IOSTREAM

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#endif // IOSTREAM

#ifndef RESULT_CODE_H

#include "resultCode.h"

#endif // RESULT_CODE_H

template <class T>
class graph
{
public:
	virtual resultCode insert(int u, int v, T& w) = 0;
	virtual resultCode remove(int u, int v) = 0;
	virtual bool exist(int u, int v) const = 0;
	virtual int vertices() const {return n;}
protected:
	int n, e;
};

template <class T>
class mGraph : public graph<T>
{
public:
	mGraph(int mSize, const T& noEdg){
		this->n = mSize; this->e = 0; noEdge = noEdg;
		a = new T*[this->n];
		for (int i = 0; i < this->n ; i++){
			a[i] = new T[this->n];
			for (int j = 0; j < this->n; j++) a[i][j] = noEdge;
			a[i][i] = 0;
		}
	}
	~mGraph(){
		for (int i = 0; i < this->n; i++) delete []a[i];
		delete []a;
	}
	resultCode insert (int u, int v, T& w){
		if(u<0 || v<0 || u>this->n-1 || v>this->n-1 || u==v) return failure;
		if(a[u][v] != noEdge) return duplicate;
		a[u][v] = w;
		this->e++;
		return success;
	}
	resultCode remove (int u, int v){
		if(u<0 || v<0 || u>this->n-1 || v>this->n-1 || u==v) return failure;
		if(a[u][v] == noEdge) return notPresent;
		a[u][v] = noEdge;
		this->e--;
		return success;
	}
	bool exist(int u, int v)const{
		if(u<0 || v<0 || u>this->n-1 || v>this->n-1 || u==v || a[u][v]==noEdge) return false;
		return true;
	}
protected:
	T **a;
	T noEdge;
};

template <class T>
struct eNode
{
	eNode() {nextArc = NULL;}
	eNode(int vertex, T weight, eNode* next){
		adjVex = vertex; w = weight; nextArc = next;
	}
	int adjVex;
	T w;
	eNode* nextArc;
};

template <class T>
class lGraph: public graph<T>
{
public:
	lGraph(int mSize){
		this->n = mSize; this->e = 0;
		a = new eNode<T>* [this->n];
		for (int i = 0; i < this->n; i++) a[i] = NULL;
	}
	~lGraph(){
		eNode<T> *p, *q;
		for (int i = 0; i < this->n; i++){
			p = a[i]; q = p;
			while(p != NULL) {
			    p = p->nextArc;
			    delete q;
			    q = p;
			}
		}
		delete []a;
	}
	resultCode insert(int u, int v, T& w){
		if(u<0 || v<0 || u>this->n-1 || v>this->n-1 || u==v) return failure;
		if(exist(u, v)) return duplicate;
		eNode<T> *p = new eNode<T>(v, w, a[u]);
		a[u] = p;
		this->e++;
		return success;
	}
	resultCode remove(int u, int v){
		if(u<0 || v<0 || u>this->n-1 || v>this->n-1 || u==v) return failure;
		eNode<T> *p = a[u], *q = NULL;
		while(p!=NULL && p->adjVex!=v){
			 q = p; p = p->nextArc;
		}
		if (p == NULL) return notPresent;
		if (q != NULL) q->nextArc = p->nextArc;
		else a[u] = p->nextArc;
		delete p;
		this->e--;
		return success;
	}
	bool exist(int u, int v)const{
		if(u<0 || v<0 || u>this->n-1 || v>this->n-1 || u==v) return false;
		eNode<T> *p = a[u];
		while(p!=NULL && p->adjVex!=v) p = p->nextArc;
		if (p == NULL) return false;
		else return true;
	}
protected:
	eNode<T> **a;
};

#endif // GRAPH_H
