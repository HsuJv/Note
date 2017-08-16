 #include <iostream>
#include <string.h>
#define maxlength 11

using std::cin;
using std::cout;
using std::endl;

class LCS
{
public:
	LCS(int nx, int ny, char *x, char *y){ //对数据成员m、n、a、b、c、s初始化 
		m = nx; n = ny; //对m和n赋值
		a = new char[m + 2]; //考虑下标为0的元素和字符串结束标记
		b = new char[n + 2];
		memset(a, 0, m + 2);
		memset(b, 0, n + 2);
		strcpy(a + 1, x);
		strcpy(b + 1, y); //将x和y中的字符写入一维数组a和b中
		c = new int[maxlength][maxlength]; //maxlength为某个常量值
		s = new int[maxlength][maxlength];
		for (int i = 0; i < maxlength; i++){
			memset(c[i], 0, sizeof(c[i]));
			memset(s[i], 0, sizeof(s[i]));
		}//对二维数组c和s中元素进行初始化
	}

/*	int LCSLength(){
		for (int i = 0; i <= m; i++) c[i][0] = 0; //初始化行标或列标为0的元素
		for (int j = 1; j <= n; j++) c[0][j] = 0;
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++)
			if (a[i] == b[j]){ //由c[i-1][j-1]得到c[i][j]
				c[i][j] = c[i-1][j-1] + 1; s[i][j]=1;
			} else if (c[i-1][j] >= c[i][j-1]){ //由c[i-1][j]得到c[i][j]
				c[i][j] = c[i-1][j]; s[i][j] = 2;
			} else{ //由c[i][j-1]得到c[i][j]
				c[i][j] = c[i][j-1]; s[i][j] = 3;
			}
		return c[m][n]; //返回最优解值
	}
DP方法*/
	int LCSLength(){
		LCSLength(m, n);
	}

/*	void CLCS(){
		CLCS(m, n);
	}
求一个最优解*/
	void CLCS(){
		char *st; // the stack that stores answer
		st = new char [c[m][n]];
		CLCS(m, n, -1, st);
	}

private:
/*	void CLCS(int i, int j) const{ //调用私有成员函数CLCS(int,int)
		if (i == 0 || j == 0 || s[i][j] == 0) return; //终止条件
		if (s[i][j] == 1){
			CLCS(i - 1, j - 1);
			cout << a[i]; //输出最优解的当前分量
		} else if (s[i][j] == 2) CLCS(i - 1, j);
		else CLCS(i, j - 1);
	}
求一个最优解*/	
	void CLCS(int i, int j, int t, char *st) const{
		if (t == c[m][n] - 1){
			for (int i = t; i > -1; i--)
				cout << st[i];
			cout << endl;
			return;
		}
		if (i == 0 || j == 0) return;
		if (a[i] == b[j]){
			st[++t] = a[i];
			CLCS(i - 1, j - 1, t, st);
			t--;
		} else if (c[i-1][j] > c[i][j-1]) CLCS(i - 1, j, t, st);
		else if (c[i-1][j] < c[i][j-1]) CLCS(i, j - 1, t, st);
		else{
			CLCS(i - 1, j, t, st);
			CLCS(i, j - 1, t, st);
		}
	}
/*	void CLCS(int i, int j) const{ 
		if (i == 0 || j == 0) return;
		if (a[i] == b[j]){
			CLCS(i - 1, j - 1);
			cout << a[i];
		} else if (c[i-1][j] >= c[i][j-1]) CLCS(i - 1, j);
		else CLCS(i, j - 1);
	}
不构建辅助数组s*/

	int LCSLength(int i, int j){
		if (i == 0 || j == 0) return 0;
		if (c[i][j] != 0) return c[i][j];
		else if (a[i] == b[j]){ 
			c[i][j] = LCSLength(i - 1, j - 1) + 1; s[i][j] = 1;
			}
		else if (LCSLength(i - 1, j) >= LCSLength(i, j - 1)){ 
			c[i][j] = LCSLength(i - 1, j); s[i][j] = 2;
			}
		else{ 
			c[i][j] = LCSLength(i, j - 1); s[i][j] = 3;
			}
		return c[i][j];
	}

	int (*c)[maxlength], (*s)[maxlength];
	int m, n;
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
	cout << endl << "The length of the longest common subsequence of string x and y is: " << lcs.LCSLength();
	cout << endl << "And the subsequence is: " << endl;
	lcs.CLCS();
	delete []x;
	delete []y;
	return 0;
}
