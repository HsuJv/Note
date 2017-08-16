#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#ifndef IOSTREAM
#define IOSTREAM

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#endif // IOSTREAM

#ifndef QUEUE_H

#include "queue.h"

#endif // QUEUE


template<class T>
struct BTNode{
	BTNode(){ lChild = rChild = NULL;}
	BTNode(const T& x){
		element = x; lChild = rChild = NULL;
		isUsed = false;
	}
	BTNode(const T& x, BTNode<T>* l,BTNode<T>* r){
		element = x; lChild = l; rChild = r;
		isUsed = false;
	}
	T element;
	BTNode<T> *lChild, *rChild;
	bool isUsed;
};

template<class T>
class binaryTree
{
public:
	binaryTree(){ root = NULL;}
	~binaryTree(){ }
	bool isEmpty() const{
		if (root == NULL)
			return true;
		return false;
	}
	void clear(){
		if (isEmpty()) return;
		clear(root);
	}
	bool getRoot(T &x) const{
		if(root != NULL){
			x = root->element; return true;
		}
	}
	void makeTree(const T& x, binaryTree<T>& left, binaryTree<T>& right){
		if(root != NULL && &left == &right) return;
		root = new BTNode<T>(x, left.root, right.root);
		left.root = right.root = NULL;
	}
	void breakTree(T& x, binaryTree<T>& left, binaryTree<T>& right){
		if(root == NULL || &right == &left || left.root != NULL || right.root != NULL) return;
		x = root->element;
		left.root = root->lChild;
		right.root = root->rChild;
		delete root; root = NULL;
	}
	void preOrder(void (*visit)(T& x)){
		preOrder(visit, root);
	}
	void inOrder(void (*visit)(T& x)){
		inOrder(visit, root);
	}
	void postOrder(void (*visit)(T& x)){
		postOrder(visit, root);
	}
	void copy(binaryTree<T> &bt){
		clear();
		root = copy(bt.root);	
	}
	void swap(){
		swap(root);
	}
	int getNumOfLeaves(){
		if (root == NULL) return 0;
		return getNumOfLeaves(root);
	}
	int getHeightOfTree(){
		if (root == NULL) return 0;
		return getHeightOfTree(root);
	}
	void leftToRightOrder(){
		int mSize = getNumOfLeaves() + 1;
		seqQueue<BTNode<T>*> a1(mSize), a2(mSize);
		a1.enQueue(root);
		leftToRightOrder(a1, a2, 1);
	}
protected:
	BTNode<T>* root;
private:
	void clear(BTNode<T>* &t){
		if (t == NULL) return;
		clear(t->lChild);
		clear(t->rChild);
		t = NULL;
	}
	void preOrder(void (*visit)(T& x), BTNode<T> *t){
		if (t == NULL) return;
		visit(t->element);
		preOrder(visit, t->lChild);
		preOrder(visit, t->rChild);
	}
	void inOrder(void (*visit)(T& x), BTNode<T> *t){
		if (t == NULL) return;
		inOrder(visit, t->lChild);
		visit(t->element);
		inOrder(visit, t->rChild);
	}
	void postOrder(void (*visit)(T& x), BTNode<T> *t){
		if (t == NULL) return;
		postOrder(visit, t->lChild);
		postOrder(visit, t->rChild);
		visit(t->element);
	}
	void swap(BTNode<T>* &t) {
		if (t == NULL) return;
		BTNode<T> *q;
		q = t->lChild;
		t->lChild = t->rChild;
		t->rChild = q;
		swap(t->lChild);
		swap(t->rChild);
	}
	BTNode<T>* copy(BTNode<T>* t){
		if (t == NULL) return NULL;
		BTNode<T> *q = new BTNode<T>(t->element);
		q->lChild = copy(t->lChild);
		q->rChild = copy(t->rChild);
		return q;
	}
	int getNumOfLeaves(BTNode<T> *t){
		if (t->lChild == NULL && t->rChild == NULL) return 1;
		if (t->lChild == NULL) return getNumOfLeaves(t->rChild);
		if (t->rChild == NULL) return getNumOfLeaves(t->lChild);
		return getNumOfLeaves(t->rChild) + getNumOfLeaves(t->lChild);
	}
	int getHeightOfTree(BTNode<T> *t){
		if (t == NULL) return 0;
		int r = getHeightOfTree(t->rChild);
		int l = getHeightOfTree(t->lChild);
		return 1 + (r>l?r:l);
	}
	void leftToRightOrder(seqQueue<BTNode<T>*> &a1, seqQueue<BTNode<T>*> &a2, int h){
		while(!a1.isEmpty()) {
		    BTNode<T> *q;
		    a1.getFront(q);
		    a1.deQueue();
		    cout << q->element << "\t";
		    if (q->lChild != NULL) a2.enQueue(q->lChild);
		    if (q->rChild != NULL) a2.enQueue(q->rChild);
		}
		cout << endl;
		if (h != getHeightOfTree()) leftToRightOrder(a2, a1, h+1);
	}
};

template<class T>
void visit(T &x){
	cout << x << " ";
}

#endif // BINARY_TREE_H
