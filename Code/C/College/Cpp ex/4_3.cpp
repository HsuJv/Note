#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class student{
	char num[10], name[10], sex[3];
	int score;
	public:
		student(char* , char*, char*, int);
		friend ostream& operator <<(ostream &out, const student &s);
};

student::student(char *nu = "", char *na = "", char *se = "", int s = 0){
	strcpy(num, nu);
	strcpy(name, na);
	strcpy(sex, se);
	score = s;
}

ostream& operator <<(ostream &out, const student &s){
	out<<"Number : "<<s.num<<endl;
	out<<"Name : "<<s.name<<endl;
	out<<"Sex : "<<s.sex<<endl;
	out<<"Score : "<<s.score<<endl;
	out<<endl;
	return out;
}

void CreatBiFile(char *s){
	ofstream out(s);
	student stu[3] = {student("B15041426", "xjw", "male", 90),
					  student("B15041425", "xty", "male", 95),
					  student("B15041427", "gwj", "male", 90)};
	out.write((char *) stu, sizeof(student) * 3);
	out.close();
}

void ReadBiFile(char *s){
	ifstream in(s);
	int i = 0;
	student stu[3];
	while(!in.eof()){
		in.read((char *) &stu[i++], sizeof(student));
	}
	for (i = 0; i < 3; i++)	cout<<stu[i];
	in.close();
}

int main(){
	CreatBiFile("stu.dat");
	ReadBiFile("stu.dat");
	return 0;
}
