#include "../h/binaryTree.h"

int main(int argc, char const *argv[]){
	binaryTree<char> a, b, x1, x2, y, z, bt;
	y.makeTree('F', a, b);
	z.makeTree('G', a, b);
	x2.makeTree('C', y, z);
	y.makeTree('D', a, b);
	z.makeTree('E', a, b);
	x1.makeTree('B', y, z);
	bt.makeTree('A', x1, x2);
	cout << "the raw bt is: ";
	bt.preOrder(visit); cout << endl;
	bt.swap();
	cout << "After swaping, bt is: ";
	bt.preOrder(visit); cout << endl;
	a.copy(bt);
	cout << "After copying, a is: ";
	a.preOrder(visit); cout << endl;
	cout << "bt's order from left to right :" << endl;
	bt.leftToRightOrder(); cout << endl;
	cout << "bt's height: ";
	cout << bt.getHeightOfTree() << endl;
	cout << "After clearing, bt is: ";
	bt.clear();
	bt.preOrder(visit); cout << endl;
	return 0;
}
