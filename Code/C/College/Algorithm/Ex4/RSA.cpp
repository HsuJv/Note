#include <iostream>
using namespace std;

int ext_euclid(int a, int b, int f, int e){  
  // 因  e * 0 + φ * 1 = φ  (1) 
  //     e * 1 + φ * 1 = e  (2) 
  // 则：e * (0 - 1 * (φ / e)) + ..... = φ % e 
  // 由于e和φ互质，因此一定有某一次运算后，等式右侧的φ % e == 1。 
  // 此时左侧等式中e所乘的系数就是所要求的d，即e^ (-1)
  // 将(1)式e所乘的系数用a表示，(2)式中e所乘的系数用b表示，并且令：m = φ / e;  n = φ % e     
    int m, n, t; 
    if (e == 1) return b;   
    m = f / e; 
    n = f % e; 
    t = a - b * m; 
    ext_euclid(b, t, e, n);   
} 
  
int main() { 
    // 输入质数p和q 
    int p, q; 
    cout << "输入一个质数p(如101): "; 
    cin >> p; 
    cout << "输入一个质数q(如113): "; 
    cin >> q; 
    // 求得n = p * q的值 
    int n = p * q; 
    cout << "分组加密时，每个分组的大小不能超过n = p * q = "; 
    cout << n << endl; 
 
    // 求得φ(n) = (p - 1) * (q - 1)的值 
    int f = (p - 1) * (q - 1); 
    cout << "模φ(n) = (p - 1) * (q - 1) = "; 
    cout << f << endl << endl; 
 
    // 选取与φ(n)互质的公钥e 
    int e; 
    cout << "输入与φ(n)互质的公钥e(如3533):"; 
    cin >> e; 
 
    // 由e和φ(n)生成私钥d 
    int d = ext_euclid(0, 1, f, e); 
    while (d <= 0) d += f; 
    cout << "通过调用扩展欧几里德算法，求得密钥d为：" << d << endl; 
 
    // 利用生成的公钥{e, n}对明文M进行加密 
    int M, C; 
    cout << "现在公钥{e, n}、私钥{d, n}均已生成完毕。\n\n请输入需要传输的明文内容进";
    cout << "行加密(如9726)："; 
    cin >> M; 
    C = 1; 
    for(int i = 1; i <= e; i++ ) { 
        C = C * M % n; 
    } 
    cout << "明文M = " << M << "经加密后得到密文C = M^e(mod n)：" << C << endl; 
 
    // 利用生成的私钥私钥{e, n}对密文C进行解密 
    M = 1; 
    for(int i = 1; i <= d; i++ ) { 
        M = M * C % n; 
    } 
    cout << "密文C = " << C << "经解密后得到明文M = C^d(mod n)：" << M << endl; 
} 
