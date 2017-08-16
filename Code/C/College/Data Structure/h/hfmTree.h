#ifndef HFM_TREE_H
#define HFM_TREE_H

#ifndef IOSTREAM
#define IOSTREAM

#include <iostream>
using std::cin;
using std::cout;
using std::endl;


#endif // IOSTREAM

#ifndef BINARY_TREE_H

#include "binaryTree.h"

#endif // BINARY_TREE_H

#ifndef STRING
#define STRING

#include <string>
using std::string;

#endif // STRING

#ifndef STDLIB_H
#define STDLIB_H

#include <stdlib.h>

#endif // STDLIB_H

#ifndef C_STRING
#define C_STRING

#include <cstring>

#endif // C_STRING


#ifndef PRIO_QUEUE_H

#include "prioQueue.h"

#endif // PRIO_QUEUE_H



#ifndef MAX_SIZE
#define MAX_SIZE

#define mSize 20

#endif // MAX_SIZE



template <class T>
class hfmTree : public binaryTree<T>
{
public:
	operator T() const { return weight;}
	T getW() {return weight;}
	void putW (const T &x) { weight = x;}
	void setNULL () { this->root = NULL;}
    string encoding(int i, T *w){
    	string ret("");
		encoding(i, w, this->root, ret);
		if(ret == "") return ret;
		ret = ret.erase(ret.length()-1, 1);
		return ret;
	}
	string decoding(char *str, char *s, int i, string *code){
		if (i >= strlen(str)) return NULL;
		string ret("");
		string temp("");
		decoding(str, this->root, s, ret, i, code, temp);
		return ret;
	}
private:
	T weight;
	void encoding(int i, T *w, BTNode<T>* t, string &ret){
		if (t->lChild==NULL && t->rChild==NULL){
			if (w[i]==t->element && !t->isUsed){
				ret += "2";
				t->isUsed = true;
			}
			return;
		}
		if (t->lChild != NULL){
			ret += "0";
			encoding(i, w, t->lChild, ret);
			if (ret[ret.length()-1] == '2'){
				return;
			}
			ret = ret.erase(ret.length()-1, 1);
		}
		if (t->rChild != NULL){
			ret += "1";
			encoding(i, w, t->rChild, ret);
			if (ret[ret.length()-1] == '2'){
				return;
			}
			ret = ret.erase(ret.length()-1, 1);
		}
		return;
	}
	void decoding(char *str, BTNode<T>* t, char *s, string &ret, int i, string *code, string &tmp){
		if (i > strlen(str)) return;
		else if(t->lChild==NULL && t->rChild==NULL){
			int j = 0;
			for(; tmp!=code[j]; j++);
			ret += s[j];
			tmp = "";
			decoding(str, this->root, s, ret, i, code, tmp);
		}
		else if (str[i++] == '0'){
			tmp += "0";
			decoding(str, t->lChild, s, ret, i, code, tmp);
			}
		else{
			tmp += "1";
			decoding(str, t->rChild, s, ret, i, code, tmp);
		}
	}
};


template <class T>
hfmTree<T> createHfmTree (T w[], int n){
	prioQueue <hfmTree<T> > pq(n);
	hfmTree<T> x, y, z, zero;
	for (int i = 0; i < n; i++){
		z.makeTree(w[i], x, y);
		z.putW(w[i]);
		pq.append(z);
		z.setNULL();
	}
	for (int i = 1; i < n; i++){
		pq.serve(x); pq.serve(y);
		z.makeTree(x.getW()+y.getW(), x, y);
		z.putW(x.getW() + y.getW());
		pq.append(z);
		z.setNULL();
	}
	pq.serve(z);
	return z;
}

#endif // HFM_TREE_H
