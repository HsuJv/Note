#include <iostream>
using namespace std;

int ext_euclid(int a, int b, int f, int e){  
  // ��  e * 0 + �� * 1 = ��  (1) 
  //     e * 1 + �� * 1 = e  (2) 
  // ��e * (0 - 1 * (�� / e)) + ..... = �� % e 
  // ����e�ͦջ��ʣ����һ����ĳһ������󣬵�ʽ�Ҳ�Ħ� % e == 1�� 
  // ��ʱ����ʽ��e���˵�ϵ��������Ҫ���d����e^ (-1)
  // ��(1)ʽe���˵�ϵ����a��ʾ��(2)ʽ��e���˵�ϵ����b��ʾ�������m = �� / e;  n = �� % e     
    int m, n, t; 
    if (e == 1) return b;   
    m = f / e; 
    n = f % e; 
    t = a - b * m; 
    ext_euclid(b, t, e, n);   
} 
  
int main() { 
    // ��������p��q 
    int p, q; 
    cout << "����һ������p(��101): "; 
    cin >> p; 
    cout << "����һ������q(��113): "; 
    cin >> q; 
    // ���n = p * q��ֵ 
    int n = p * q; 
    cout << "�������ʱ��ÿ������Ĵ�С���ܳ���n = p * q = "; 
    cout << n << endl; 
 
    // ��æ�(n) = (p - 1) * (q - 1)��ֵ 
    int f = (p - 1) * (q - 1); 
    cout << "ģ��(n) = (p - 1) * (q - 1) = "; 
    cout << f << endl << endl; 
 
    // ѡȡ���(n)���ʵĹ�Կe 
    int e; 
    cout << "�������(n)���ʵĹ�Կe(��3533):"; 
    cin >> e; 
 
    // ��e�ͦ�(n)����˽Կd 
    int d = ext_euclid(0, 1, f, e); 
    while (d <= 0) d += f; 
    cout << "ͨ��������չŷ������㷨�������ԿdΪ��" << d << endl; 
 
    // �������ɵĹ�Կ{e, n}������M���м��� 
    int M, C; 
    cout << "���ڹ�Կ{e, n}��˽Կ{d, n}����������ϡ�\n\n��������Ҫ������������ݽ�";
    cout << "�м���(��9726)��"; 
    cin >> M; 
    C = 1; 
    for(int i = 1; i <= e; i++ ) { 
        C = C * M % n; 
    } 
    cout << "����M = " << M << "�����ܺ�õ�����C = M^e(mod n)��" << C << endl; 
 
    // �������ɵ�˽Կ˽Կ{e, n}������C���н��� 
    M = 1; 
    for(int i = 1; i <= d; i++ ) { 
        M = M * C % n; 
    } 
    cout << "����C = " << C << "�����ܺ�õ�����M = C^d(mod n)��" << M << endl; 
} 
