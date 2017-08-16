#include <iostream>
#include <string.h>

using std::cin;
using std::cout;
using std::endl;

class LCS
{
public:
	LCS(int nx, int ny, char *x, char *y){ //对数据成员m、s、a、b、c、s初始化 
		l = nx; s = ny; //对l和s赋值
		a = new char[l + 2]; //考虑下标为0的元素和字符串结束标记
		b = new char[s + 2];
		memset(a, 0, l + 2);
		memset(b, 0, s + 2);
		if (l < s){
			int t = s;
			s = l; l = t;
			strcpy(a + 1, y);
			strcpy(b + 1, x); //将x和y中的字符写入一维数组a和b中
		} else{
			strcpy(a + 1, x);
			strcpy(b + 1, y); 
		}
		c1 = new int[s + 1]; //maxlength为某个常量值
		c2 = new int[s + 1];
		memset(c1, 0, (s+1) * sizeof(int));
		memset(c2, 0, (s+1) * sizeof(int));//对二维数组c1和c2中元素进行初始化
	}

	int LCSLength(){
		for (int i = 1; i <= l; i++){
			for (int j = 1; j <= s; j++)
				if (a[i] == b[j]) c2[j] = c1[j-1] + 1;
				else c2[j] = c1[j]>c2[j-1] ? c1[j] : c2[j-1];
			for (int j = 1; j <=s; j++){
				c1[j] = c2[j];
				c2[j] = 0;
			}
		}
		return c1[s]; //返回最优解值
	}



private:
	int *c1, *c2;
	int l, s;
	char *a, *b;
};

int main(int argc, char const *argv[])
{ 
	int nx, ny;
	char *x, *y;
	cout << "The length of string x, y: ";
	cin >> nx >> ny;
	x = new char[nx];
	y = new char[ny];
	cout << endl << "String x: ";
	cin >> x;
	cout << endl << "String y: ";
	cin >> y;
	LCS lcs(nx, ny, x, y);
	cout << endl << "The length of the longest common subsequence of string x and y is: " << lcs.LCSLength() << endl;
	delete []x;
	delete []y;
	return 0;
}
