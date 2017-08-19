#include <iostream>
#include <stdlib.h>
#include <math.h>
using std::cin;
using std::cout;
using std::endl;

template <class T>
class SortableList
{
public:
	SortableList(int mSize){
		maxSize = mSize;
		l = new T[maxSize+1];
		n = 0;
	}
	~SortableList(){ delete []l;}

	void Input(){
		cout << "n: ";
		cin  >> n;
		cout << endl << "Array l: ";
		for(int i = 0; i < n; i++)
			cin >> l[i];
		l[n] = INT_MAX;
		cout << endl;
	}

	void Output(){
		for(int i = 0; i < n; i++)
			cout << l[i] << " ";
		cout << endl;
	}
/*
	void MergeSort(){
		MergeSort(0, n - 1);
	}

	void QuickSort(){
		QuickSort(0, n - 1);
	}*/

	int Select(int k, T& x){
		int ans = Select(k, 0, n - 1, 5);
		x = l[ans];
		return ans;
	}

private:
	T *l;
	int maxSize;
	int n;
/*
	void Merge(int left, int mid, int right){
		int *t = new int[right-left+1];
		int i = left, j = mid + 1, k = 0;
		while((i<=mid) && (j<=right))
			if (l[i] <= l[j]) t[k++] = l[i++];
			else t[k++] = l[j++];
		while (i <= mid) t[k++] = l[i++];
		while (j <= right) t[k++] = l[j++];
		for (i = 0, k = left; k <= right; ) l[k++] = t[i++];
	}
	
	void MergeSort(int left, int right){
		if (left < right){
			int mid = (left + right) / 2;
			MergeSort(left, mid);
			MergeSort(mid + 1, right);
			Merge(left, mid, right);
			}
	}*/

	void Swap(int i, int j){
		int c = l[i];
		l[i] = l[j];
		l[j] = c;
	}

	int Partition(int left, int right){
		int i = left, j = right + 1;
		do{
		do i++; while (l[i] < l[left]);
		do j--; while (l[j] > l[left]);
		if (i < j) Swap(i, j);
		}while (i < j);
		Swap(left, j);
		return j;
	}
/*
	void QuickSort(int left, int right){
		if (left < right){
		int j = Partition(left, right);
		QuickSort(left, j - 1);
		QuickSort(j + 1, right);
		}
	}*/
	void InsertSort(int left, int right){
		for (int i = left + 1; i <= right; i++){
			int j = i;
			T t = l[i];
			while(j && t < l[j - 1]) 
			    l[j] = l[(j--) - 1];
			l[j] = t;
		}
	}

	int Select(int k, int left, int right, int r){ 
		//每个分组r个元素, 寻找第k小元素
		int n = right - left + 1;
		if (n <= r){ //若问题足够小, 使用直接插入排序
			InsertSort(left, right);
			return left + k - 1; //取其中的第k小元素, 其下标为left+k-1
		}
		for (int i = 1; i <= n / r; i++){
			InsertSort(left + (i-1) * r, left + i * r - 1);
		//二次取中规则求每组的中间值	
			Swap(left + i - 1, left + (i-1) * r + (int)ceil((double)r/2) - 1);
		//将每组的中间值交换到子表前部集中存放
		}
		int j = Select((int)ceil((double)n/r/2), left, left + (n/r) - 1, r);
		//求二次中间值, 其下标为j
		Swap(left, j); //二次中间值为枢纽元, 并换至left处
		j = Partition(left, right); //对表（子表）进行分划操作	
		if (k == j - left + 1) return j; //返回第k小元素下标
		else if (k < j - left + 1)
		return Select(k, left, j - 1, r);//在左子表求第k小元素
		else return Select(k - (j-left+1), j+1, right, r);
		//在右子表求第k-(j-left+1)小元素
	}

};


int main(int argc, char const *argv[])
{
	SortableList<int> sl(10);
	int x, k;
	sl.Input();
//	sl.QuickSort();
//  sl.MergeSort();
	cout << "k:";
	cin >> k;
	sl.Select(k, x);
	cout << "The k-th minor number is: " << x << endl;
	return 0;
}

