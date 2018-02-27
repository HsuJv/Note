#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//#define debug
//while debuging, delete the "//" symbol of define statement

#define outFile "score.txt" //the txt where the result save
#define idLength 6 //the max length of id
#define probNum 10 //the number of problems

#ifdef debug
#include <assert.h>
#endif

struct Pupils{
	char id[idLength + 1];
	int score;
	double 	useTime; //  to record the time user used
};

int gcd(int a,int b){
	if (b == 0) return a;
	return gcd(b, a % b);
}//to make sure the division operation can get a integer

void idInput(char* id){
	char ch;
	int i = 0;
	printf("%s", "Please input your id : ");
	while((ch = getchar()) != '\n'){
		*(id + (i++)) = ch;
		if (i == idLength)	break;
	}//Avoid the input data is too long or too short.
	if (i == idLength)	while(getchar() != '\n') i = 0; //flush the instream
	//if input data is too long then make the id arr illegal
	*(id + i) = '\0';//insert the end of this string
	#ifdef debug
	assert(strlen(id) == idLength);
	#endif
}

int idCheck(char const *id){ //Check the validity of the id input
	if (strlen(id) < idLength){
		printf("%s\n", "The id is illegal, please input a legal one!");
		return 0;
	}

	int i = 0;
	for (; i < 2 ; i++)
		if (!isupper(*(id + i))){
			printf("%s\n", "The id is illegal, please input a legal one!");
			return 0;
		}
	for (; i < idLength ; i++)
		if (!isdigit(*(id + i))){
			printf("%s\n", "The id is illegal, please input a legal one!");
			return 0;
		}
	return 1;
}

int test(){
	int score = 0, i, o;
	int dig1[probNum], dig2[probNum];	 //dig1,2 stand fot the first digit and the second digit
	int ans[probNum], userAns[probNum];  //ans = the answer, userAns = the answer of the tester
	char opp[probNum];// opp = opperator
	srand(time(0));
	for (i = 0; i < probNum; i++){
		o = rand() % 4;
		dig1[i] = rand() % 99 + 1;
		dig2[i] = rand() % 99 + 1;//avoid zero
		if (dig1[i] < dig2[i]){
			int temp = dig1[i];
			dig1[i] = dig2[i];
			dig2[i] = temp;
		}
		if (i < 4) o = i;
		switch (o){
			case 0: opp[i] = '-'; ans[i] = dig1[i] - dig2[i]; break;
			case 1: opp[i] = '*'; if (dig1[i] * dig2[i] >= 100){
					dig1[i] /= 10; dig2[i] /= 10;
					} // to ensure the result less than 100
					ans[i] = dig1[i] * dig2[i]; break;
			case 2: opp[i] = '+'; if (dig1[i] + dig2[i] >= 100)	dig1[i] -= (dig1[i] + dig2[i]) / 2;
					// to ensure the result less than 100
					ans[i] = dig1[i] + dig2[i]; break;
			case 3: opp[i] = '/'; if (dig1[i] % dig2[i])	dig2[i] = gcd (dig1[i], dig2[i]); 
					if(dig2[i] == 1){ dig1[i] = dig1[i] % 2 ? dig1[i]+1 : dig1[i]; dig2[i]++;}
					ans[i] = dig1[i] / dig2[i]; break;
			//if dig1 do not be divide by dig2, then make dig2 the gcd of two number
			}
		printf("%d %c %d = ", dig1[i], opp[i], dig2[i]);
		scanf("%d", userAns + i);
		while(getchar() != '\n'); //flush the instream
		if (userAns[i] == ans[i]) score ++;
	}

	// to print the result
	printf("\n\n\n%s\n", "The result :");
	printf("%s\n", "Prob. | Correct Answ.  |  User Ans.");
	for (i = 0; i < probNum; i++){
		printf("%d%c%d\t", dig1[i], opp[i], dig2[i]);
		printf("%d\t\t  %d\t\n", ans[i], userAns[i]);
	}
	return score * 10;
}

void recordInsert(const struct Pupils pupils, char const *fout){
	FILE *f = fopen(fout, "a");
	fprintf(f, "id : %s\tscore : %d \ttestTime : %lf\n", pupils.id, pupils.score, pupils.useTime);
	fclose(f);
}

void display(char const *id, char const *fout){
	FILE *f = fopen(fout, "r");
	char curRecord[60];

	if (f == NULL){
		printf("%s\n", "There aren't any records exist.");
		return;
	}
	printf("%s\t\t%s\t\t%s\n", "Id", "Score", "Time(sec)");
	while(fgets(curRecord, 60, f))
		if (strstr(curRecord, id) != NULL){
			int i = 0, j;
			#ifdef debug
			printf("%s", curRecord);
			printf("%d\n", strlen(curRecord));
			#endif

			for(j = 0; j < 3; j++){
				while (curRecord[i++] != ':'); 
				while (curRecord[i] != '\t' && curRecord[i] != '\n'){
					printf("%c", curRecord[++i]);
				}
				if(j != 2)	printf("\t");
			}
		}
	fclose(f);
}

int main(int argc, char const *argv[]){
	int op; //op = options
	struct Pupils pupils;


	do{
		memset(pupils.id, 0, sizeof(pupils.id));
		idInput(pupils.id);
	} while (!idCheck(pupils.id)); //input id and check id

	#ifndef debug
	printf("%s\n\n\n", "Correct id!");
	printf("%s\n", "Now turn to menu, please wait three seconds....");
	system("@ping 127.0.0.1 -n 3 > nul");
	system("cls");
	//to change the loading time
	//change the -n parameter of the ping statement
	//of course remember to modify the notice
	#endif

	do{
		clock_t start, end; //  to recode the start time and the end time of the test

		printf("%s", "(1) Start a test\n(2) Check score\n(3) Exit\
		\nInput your choose : ");
		scanf("%d", &op);
		while (getchar() != '\n'); //flush the instream
		switch (op){
			case 1: start = clock(); pupils.score = test(); end = clock();
					pupils.useTime = (double) (end - start) / 1000; // calc the time costing 
					printf("%s : %s\n", "Id", pupils.id);
					printf("%s : %d\n", "Score", pupils.score);
					printf("%s : %lf(sec)\n", "Time", pupils.useTime);
					recordInsert(pupils, outFile); break;
			case 2: display(pupils.id, outFile); printf("\n\n"); break;
			case 3: return 0;
			default : printf("%s", "Opps! Wrong option.\nPlease ");
					printf("%s\n\n\n\n", "check your input.");
					break;
		}
		printf("%s\n", "Press any key to return to menu.");
		system("@pause > nul"); system("cls");
	} while (1);
}
