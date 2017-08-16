#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <string>
#include <fstream>
using namespace std;


void ReadFile(char *s){
	ifstream in(s);
	char ch;
	while (in.get(ch)) cout<<ch;
	cout<<endl;
	in.close();
}

void Change(char *s1, char *s2){
	ifstream in(s1);
	ofstream out(s2);
	char ch;
	while (in.get(ch)){
		if (isalpha(ch)){
			if (islower(ch)){
				out.put(toupper(ch));
			}
			else out.put(ch);
		}
		else out.put(ch);
	}
	in.close();
	out.close();
}

int main(){
	char s1[20], s2[20];
	cin>>s1>>s2;
	Change(s1, s2);
	ReadFile(s2);
	return 0;
}
