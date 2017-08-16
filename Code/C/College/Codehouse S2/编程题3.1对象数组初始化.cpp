#include<iostream>
#include<string.h>
using namespace std;
class Student
{
	int age;
	char *name;
	public:
	 Student(int m,char *n);
	 Student();
  	 ~Student();
  	 void SetMember(int m,char *n);
  	 int Getage();
     char *Getname();
};
Student::Student(int m,char *n)
{
	age=m;
	name=new char[strlen(n)+1];
	strcpy(name,n);
}
Student::Student()
{
	age=0;
	name=new char[8];
	strcpy(name,"unnamed");
}
Student::~Student()
{
	delete[]name;
}
void Student::SetMember(int m,char *n)
{
	age=m;
	if(name)
	delete[]name;
	name=new char[strlen(n)+1];
	strcpy(name,n);
}
int Student::Getage()
{
	return age;
}
char *Student::Getname()
{
	return name;
}
int main()
{
 	Student stu[3]={Student(13,"wang")}; /* ��һ��Ԫ�ص��ô��ܹ��캯����ʼ�� */
	 /* �ڶ�������Ԫ�����޲ι��캯����ʼ����Ĭ������Ϊ 0 ������Ϊ "unnamed"*/
	 stu[2].SetMember(12,"zhang"); /* �޸ĵ�����Ԫ�ص����ݳ�Աֵ */
	 cout<<stu[0].Getage()<<","<<stu[0].Getname()<<endl; /* ������� */
	 cout<<stu[1].Getage()<<","<<stu[1].Getname()<<endl;
  	 cout<<stu[2].Getage()<<","<<stu[2].Getname()<<endl;
	 return 0;
}
