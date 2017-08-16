#include "../h/seqList.h"

#ifndef mSize
#define mSize 20
#endif

int main(int argc, char const *argv[]){
	int size, del;
	seqList<int> sl(mSize);
	cout << "Input the number of the elements(<20): ";
	cin >> size;
	while(getchar()!='\n');//flush the in stream
	cout << endl << "Input the " << size << " elements: ";
	for(int i = 0; i < size; i++){
		int t;
		cin >> t;
		sl.Insert(i-1, t);
	}
	while(getchar()!='\n');//flush the in stream
	cout << "The row linear list: ";
	sl.Output(cout);
	sl.Reverse();
	cout << "After reverse, the linear list turns to be: ";
	sl.Output(cout);
	cout << "Input which elements you'd like to delete: ";
	cin >> del;
	while(getchar()!='\n');//flush the in stream
	sl.deleteX(del);
	cout << endl << "After delete " << del;
	cout << ", the linear list turns to be: ";
	sl.Output(cout);
	return 0;
}
