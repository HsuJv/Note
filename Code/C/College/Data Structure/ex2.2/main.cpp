#include "../h/hfmTree.h"
#include <fstream>
using std::ifstream;
using std::ofstream;

inline void flush(){
	while(getchar()!='\n');//flush the in stream
	//fflush(stdout)
}

inline void displayMenu(){
	cout << "-------------------------MENU-------------------------" << endl;
	cout << "--------------(B)Make a Huffman Tree------------------" << endl;
	cout << "--------------(T)Display the preorder and inorder-----" << endl;
	cout << "--------------(E)Generate the encoding----------------" << endl;
	cout << "--------------(C)Encode-------------------------------" << endl;
	cout << "--------------(D)Decode-------------------------------" << endl;
	cout << "--------------(P)Display the result-------------------" << endl;
	cout << "--------------(X)Exit---------------------------------" << endl;
	cout << "Input your option: ";
}

inline bool chooseOption(char op){
	if (op!=66 && op!=67 && op!=68 && op!=69 && op!=80 && op!= 84 && op!=88){
		cout << "Invalid option, please input 'B', 'T', 'E', 'C', 'D', 'P' or 'X'." << endl;
		cout << "Do input a valid option: ";
		return false;
	}
	return true;
}

int main(int argc, char const *argv[]){
	char op, s[mSize], str[mSize*mSize];
	int n;
	double w[mSize];
	string code[mSize];
	bool init = false;
	hfmTree<double> ht;
	do{
		system("cls");
		displayMenu();
		do{
			cin >> op;
			flush();
			op = toupper(op);
			cout << endl;
		}while(!chooseOption(op));
		switch((int)op){
			case 66: {
				if (init){
					cout << "Already a Huffman tree exist! ";
					cout << "You are ought not to choose this option." << endl;
					cout << "Or do you want to rebuild a Huffman tree?(Y/N)";
					char ch;
					do{
						cin >> ch;
						flush();
						if (ch=='y' || ch=='Y') init = false;
						else if(ch=='n' || ch=='N');
						else {
							cout << "You will input Y or N to make a choice." << endl;
						}
					}while(ch!='n' && ch!='N' && ch!='y' && ch!='Y');
				}
				if (!init){
					memset(s, 0, sizeof(s));
					memset(w, 0, sizeof(w));
					cout << "Input the number of characters: ";
					cin >> n;
					flush();
					cout << endl << "Input the characters and their weights, for each line ";
					cout << "it should be 'char weight':" << endl;
					for (int i = 0; i < n; i++){
						cin >> s[i] >> w[i];
						flush();
					}
					ht = createHfmTree(w, n);
					init = true;
				}
				break;
			}
			case 84:{
				if (!init){
					cout << "There aren't any Huffman trees exist." << endl;
					cout << "Please choose option B first." << endl;
					break;
				} 
				cout << "Preorder: ";
				ht.preOrder(visit); cout << endl;
				cout << "Inorder: ";
				ht.inOrder(visit); cout << endl; break;
			}
			case 69:{
				if (!init){
					cout << "There aren't any Huffman trees exist." << endl;
					cout << "Please choose option B first." << endl;
					break;
				}  
				for (int i = 0; i < n; i++)
					code[i] = ht.encoding(i, w);
				for (int i = 0; i < n; i++)
					cout << s[i] << " : " << code[i] << endl;
				break;
			}
			case 67:{
				if (!init){
					cout << "There aren't any Huffman trees exist." << endl;
					cout << "Please choose option B first." << endl;
					break;
				}
				ofstream ft("textfile.txt"), fc("codefile.txt");
				cout << "Input a text(less than " << mSize << " words): ";
				scanf("%s", str);
				flush();
				cout << "The encoding is: ";
				string c("");
				for (int i = 0; i < strlen(str); i++){
					int j;
					for (j = 0; j < mSize; j++)
						if (str[i] == s[j]) break;
					c += code[j];
				}
				cout << c << endl;
				ft << str;
				fc << c;
				ft.close(); fc.close(); break;
			}
			case 68:{
				if (!init){
					cout << "There aren't any Huffman trees exist." << endl;
					cout << "Please choose option B first." << endl;
					break;
				} 
				ifstream fc("codefile.txt");
				ofstream fr("result.txt");
				if (!fc.is_open()) {
					cout << "There aren't any codefiles exist." << endl;
					cout << "Please choose option C first." << endl;
					break;
				}
				fc >> str;
				string m;
				m = ht.decoding(str, s, 0, code);
				cout << "The plant massage is: " << m << endl;
				fr << m;
				fc.close(); fr.close(); break;
			}
			case 80:{
				if (!init){
					cout << "There aren't any Huffman trees exist." << endl;
					cout << "Please choose option B first." << endl;
					break;
				}
				ifstream ft("textfile.txt"), fc("codefile.txt"), fr("result.txt");
				if (!ft.is_open()) {
					cout << "There aren't any textfiles exist." << endl;
					cout << "Please choose option C first." << endl;
					break;
				}
				if (!fr.is_open()){
					cout << "There aren't any results exist." << endl;
					cout << "Please choose option D first." << endl;
					break;
				}
				ft >> str;
				cout << "Text: " << str << endl;
				fc >> str;
				cout << "Code: " << str << endl;
				fr >> str;
				cout << "Result: " << str << endl;
				ft.close(); fc.close(); fr.close();
				break;
			}
			case 88: return 0;
		}
		cout << "Press any key to back to menu..." << endl;
		system("pause > nul");
	}while(1);
}
