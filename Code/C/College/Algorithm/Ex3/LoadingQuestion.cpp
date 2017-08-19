#include <iostream>
#include <string.h>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

template <class T>
int cmp(const void *a, const void *b){
	return *(T *)a - *(T *)b;
}

template <class T>
class Loading
{
private:
	int n, //集装箱数
		*x, //当前解
		*bestx; //当前第一艘船的最优解
	T c1, //第一艘轮船的核定载重量
		c2, //第二艘轮船的核定载重量
		*w, //集装箱重量数组
		total, //所有集装箱重量之和
		cw, //当前第一艘船的载重量
		bestw, //当前第一艘船的最优载重量
		r; //剩余集装箱总重量
public:
	Loading(){ //构造函数
		cout << "The authorized of the two coasters: ";
		cin >> c1 >> c2;
		cout << endl << "The number of the cargoes: ";
		cin >> n;
		x = new int [n+1];
		bestx = new int [n+1];
		w = new T [n+1];
		total = cw = bestw = r = 0;
		cout << endl << "The weights of the cargoes: ";
		for (int i = 1; i <= n; i++){
			cin >> w[i];
			total += w[i];
		}
		qsort(w+1, n, sizeof(w[1]), cmp<T>);
		r = total;
	}

	~Loading(){ //析构函数
		delete []x;
		delete []bestx;
		delete []w;
	}

	void surBacktrack(int i){//迭代找到最接近第一艘轮船载重c1的最佳装载方案, 
						//最优载重值bestw, 最优解数组bestx。
		while (1) {
			while (i<=n && cw+w[i]<=c1){
				r -= w[i];
				cw += w[i];
				x[i] = 1;
				i++;
			}
			if (i > n){
				if (cw > bestw){
					for (int j = 1; j <= n; j++) bestx[j] = x[j];
					bestw = cw;
				}
			}else{
				r -= w[i];
				x[i] = 0;
				i++;
			}
			while (cw + r <= bestw){
				i--;
				while (i>0 && !x[i]){
					r += w[i];
					i--;
				}
				if (i == 0) return;
				x[i] = 0;
				cw -= w[i];
				i++;
			}
		}
	}

	void Backtrack(int i){//找到最接近第一艘轮船载重c1的最佳装载方案, 
						//最优载重值bestw, 最优解数组bestx。
		if (i > n){//到达叶节点
			if (cw > bestw){
				for (int j = 1; j <= n; j++) bestx[j] = x[j];
				bestw = cw;
			}
			return;
		}
		//搜索子树
		r -= w[i];
		if (cw+w[i] <= c1){ //x[i]=1时的可行解约束条件
			//搜索左子树
			x[i] = 1;
			cw += w[i];
			Backtrack(i + 1);
			cw -= w[i];
		}
		if (cw+r > bestw){ //x[i]=0时增加的约束函数, 剪去不含最优解的分枝
			//搜索右子树
			x[i] = 0;
			Backtrack(i + 1);
		}
		r += w[i];
	}


	void Show(){//输出整个装载方案
		T c2p = c2;
		for (int i = 1; i <= n; i++)
			if (!bestx[i]) c2p -= w[i];
		if (c2p>=0){
			cout << "Coaster 1: ";
			for (int i = 1; i <= n; i++)
				if (bestx[i]) cout << w[i] << " ";
			cout << endl << "Coaster 2: ";
			for (int i = 1; i <= n; i++)
				if (!bestx[i]) cout << w[i] << " ";
			cout << endl;
		}
		else{
			cout << "Can't load these cargoes!" << endl;
		}
	}
};

int main(){
	Loading<int> ld;
	ld.surBacktrack(1);
	ld.Show();
}
