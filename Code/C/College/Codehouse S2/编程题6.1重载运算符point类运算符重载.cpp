#include<iostream> 
using namespace std;

class point{
	private:
		int i, j, k;
	public:
		point(int i = 0, int j = 0, int k = 0){
			this->i = i;
			this->j = j;
			this->k = k;
		}
		
		friend ostream& operator<<(ostream& out, point& p){
			out<<"("<<p.i<<","<<p.j<<","<<p.k<<")\n";
			return out;
		}
		
		friend bool operator>(point& p1, point& p2){
			int d1 = p1.i * p1.i + p1.j * p1.j + p1.k * p1.k;
			int d2 = p2.i * p2.i + p2.j * p2.j + p2.k * p2.k;
			return d1 > d2;
		}
};

int main(){  
	int a,b,c;
	int o,p,q;//���������������ֵ�Ӽ�������
	cin>>a>>b>>c>>o>>p>>q;//��������6������
	point p1(a,b,c),p2(o,p,q);//��������������Ϊp1��p2
	cout<<p1<<p2;//�������ص�<<��������p1��p2
	cout<<"p1>p2:"<<(p1>p2)<<endl; 
	cout<<"p2>p1:"<<(p2>p1)<<endl;//�������ص�>������Ƚ�p1,p2��ԭ��ľ��벢����ʽ���
	return 0;
}
