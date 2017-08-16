#include <iostream>
#include <string.h>

using std::cin;
using std::cout;
using std::endl;

void MatrixChain(int n, int *p, int **m, int **s){
	for (int i = 1; i <= n; i++) m[i][i] = 0;
	for (int r = 2; r <= n; r++)
		for (int i = 1; i <= n-r+1; i++){
			int j = i + r - 1;
			m[i][j] = m[i+1][j] + p[i] * p[i+1] * p[j+1]; //ʡ����m[i][i]=0��
			s[i][j] = i;
			for(int k = i+1; k < j; k++){
				int t = m[i][k] + m[k+1][j] + p[i]*p[k+1]*p[j+1];
				if (t < m[i][j]){
					m[i][j] = t;
					cout << "����m[" << i << "][" << j << "]��ֵΪ��" << t << endl;
					s[i][j] = k;
					cout << "����s[" << i << "][" << j << "]��ֵΪ��" << k << endl;
				}
			}
		cout << "���������m[" << i << "][" << j << "]��ֵΪ��" << m[i][j] << endl;
	}
}

int LookupChain(int i, int j, int *p, int **m, int **s){ //����Ai���˵�Aj����С��������ͬʱ��Ͽ�λ��
	if (m[i][j] > 0) return m[i][j];
	if (i == j) return 0;
	m[i][j] = LookupChain(i+1, j, p, m, s) + p[i] * p[i+1] * p[j+1];
	s[i][j] = i;
	for (int k = i+1; k < j; k++){
		int v = LookupChain(i, k, p, m, s) + LookupChain(k+1, j, p, m, s) + p[i] * p[k+1] * p[j+1];
		if (v < m[i][j]){
			cout << "����m[" << i << "][" << j << "]��ֵΪ��" << v << endl;
			m[i][j] = v;
			cout << "����s[" << i << "][" << j << "]��ֵΪ��" << k << endl;
			s[i][j] = k;
		}
	}
	cout << "���������m[" << i <<"][" << j << "]��ֵΪ��" << m[i][j] << endl;
	return m[i][j];
}

void Traceback(int i, int j, int **s){
	if (i == j) { cout << 'A' << i << ' '; return; }
	if (i < s[i][j]) cout << '(';
	Traceback(i, s[i][j], s);
	if (i < s[i][j]) cout << ')';
	if (s[i][j]+1 < j) cout << '(';
	Traceback(s[i][j]+1, j, s);
	if (s[i][j]+1 < j) cout << ')';
}

int main(int argc, char const *argv[])
{
	int n, *p, **m, **s;
	cout << "The number of matrices: ";
	cin >> n;
	p = new int [n + 2];
	memset(p, 0, (n+2) * sizeof(int));
	m = new int* [n + 1];
	s = new int* [n + 1];
	for (int i = 0; i <= n; i++){
		m[i] = new int [n + 1];
		s[i] = new int [n + 1];
		memset(m[i], 0, (n+1) * sizeof(int));
		memset(s[i], 0, (n+1) * sizeof(int));
	}
	cout << endl << "Suppose the dimension of the i-th matrix is pi * pi+1, ";
	cout << endl << "Input pi(i=1,2...n+1) as an array: ";
	for (int i = 1; i <= n+1; i++)
		cin >> p[i];
	LookupChain(1, n, p, m, s);
	cout << endl << "The chain is: ";
	Traceback(1, n, s);
	cout << endl;
	return 0;
}
