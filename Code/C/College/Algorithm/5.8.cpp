#include <iostream>
#include <stdlib.h>
using std::cin;
using std::cout;
using std::endl;

template <class T>
class SortableList
{
public:
	SortableList(int mSize){
		maxSize = mSize;
		l = new T[maxSize];
		for(int i = 0; i < maxSize; i++){
			l[i] = (T) i;
		}
		n = 0;
	}
	~SortableList(){ delete []l;}

	int TSearch(const T& x, int left, int right) const{
		if (left <= right){
			int s = (right - left) / 3;
			int m1 = left  + s;
			int m2 = left + 2 * s;
			if (x < l[m1]) return TSearch(x, left, m1-1);
			else if (x > l[m2]) return TSearch(x, m2+1, right);
			else{
				if (l[m1] < x && x < l[m2]) return TSearch(x, m1+1, m2-1);
				else if (x == m1) return m1;
				else return m2;
			}
		}
		return -1;
	}

private:
	T *l;
	int maxSize;
	int n;
};


int main(int argc, char const *argv[])
{
	SortableList<int> sl(10);
	for (int i = 0; i < 10; i++)
		cout << sl.TSearch(i, 0, 9) << endl;
	cout << sl.TSearch(15, 0, 9);
	return 0;
}
