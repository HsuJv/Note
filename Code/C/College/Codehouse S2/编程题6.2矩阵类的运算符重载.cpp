#include <iostream>
using namespace std;
#include <stdlib.h>
class Matrix
{
int row,col;
int *m;
public:
   Matrix(int,int);
   Matrix()
   {row=col=0; 
   m=NULL;}
   ~Matrix();
 Matrix & operator+(Matrix &);
   void operator=(Matrix &b);
   void disp();
};
Matrix::Matrix(int a,int b)
{
	row=a;
	col=b;
	m=new int[row*col];
	cout<<"请输入该矩阵元素:";
  for(int i=0;i<row;i++)  
	  for(int j=0;j<col;j++)  
		  cin>>m[i*col+j];
}
Matrix::~Matrix()
{
	delete[]m;
}
Matrix & Matrix::operator+(Matrix &b)
{
	
	if(col==b.col&&row==b.row) 
	{  
		for(int i=0;i<row;i++)  
			for(int j=0;j<col;j++)   
				(*(m+i*col+j))+=(*(b.m+i*b.col+j));
	}  
	else 	
	{  
		cout<<"program terminated!"<<endl; 
	    exit(0); 
	}
		return *this;
}
void Matrix::operator =(Matrix &b)
{
delete []m; 
 m=new int[b.row*b.col]; 
row=b.row;
  col=b.col;
for(int i=0;i<row;i++) 
  for(int j=0;j<col;j++)   
	  *(m+i*col+j)=*(b.m+i*b.col+j); 
}
void Matrix::disp()
{
       for(int i=0;i<row;i++)
        {
                cout<<'\t';
                for(int j=0;j<col;j++)
                        cout<<*(m+i*col+j)<<'\t';
                cout<<endl;
        }
}
int main()
{
        int row_a,col_a,row_b,col_b;
        cout<<"请输入am矩阵的行数和列数:";
        cin>>row_a>>col_a;
        Matrix am(row_a,col_a);
        cout<<"请输入bm矩阵的行数和列数:";
        cin>>row_b>>col_b;
        Matrix bm(row_b,col_b),cm;
        cout<<"am:"<<endl;
        am.disp();
        cout<<"bm:"<<endl;
        bm.disp();
        cm=am+bm;
        cout<<"cm=am+bm:"<<endl;
        cm.disp();
        am=bm;
        cout<<"am=bm:"<<endl;
        am.disp();
        return 0;
}
