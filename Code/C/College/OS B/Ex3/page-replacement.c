/*
The algorithm of page-replacement
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define M 12

/*assign an array*/
void setArray(int* arr, int num, int val) {
	for (int i = 0; i < num; i++) {
		*(arr + i) = val;
	}
}

/*init the table to print*/
void initArr(int arr[][M], int rnum, int cnum) {
	for (int r = 0; r < rnum; ++r) {
		for (int c = 0; c < cnum; ++c)
			arr[r][c] = -1;
	}
}

void printTable(int arr[][M], int rnum, int cnum) {
	for (int r = 0; r < rnum; ++r) {
		for (int c = 0; c < cnum; ++c)
			printf("%d\t", arr[r][c]);
		printf("\n");
	}
}

/*find page in memory*/
int findExist(int mem[], int mnum, int page) {
	for (int i = 0; i < mnum; i++) {
		if (mem[i] == page) return i;
	}
	return -1;
}

/*find empty memory in memory*/
int findEmpty(int mem[], int mnum) {
	for (int i = 0; i < mnum; i++){
		if (mem[i] == -1) return i;
	}
	return -1;
}


/*FIFO algorithm*/
int fifo(int req[], int rnum, int mnum) {
	int count;
	int pos;
	int max;

	/*assign memory*/
	int *mem = (int *)malloc(sizeof(int) * mnum);
	setArray(mem, mnum, -1);

	/*record the time page load in memory*/
	int *time = (int *)malloc(sizeof(int) * mnum);
	setArray(time, mnum, M);
	
	/*get the record table initialized*/
	int (*table)[M] = (int (*)[M])malloc(sizeof(int) * M * mnum);
	initArr(table, mnum, M);
	
	/*initialize the page fault rate to 0*/
	count = 0;

	for (int i = 0; i < rnum; i++) {
		/*copy the last record*/
		for (int j = 0; j < mnum; j++) {
			table[j][i] = i ? table[j][i - 1] : -1;
		}

		/*find whether the page in memory*/
		pos = findExist(mem, mnum, req[i]);

		/*if exist*/
		if (pos != -1) continue;

		/*else*/
		count++;

		/*find whether there is room for new page in memory*/
		pos = findEmpty(mem, mnum);

		/*if there is, place the new page in*/
		if (pos != -1) {
			mem[pos] = req[i];
			time[pos] = i;
			table[pos][i] = req[i];
			continue;
		}

		/*else, find the page to be replaced*/
		pos = 0;
		for (int j = 1; j < mnum; j++) {
			/*find the fisrt in*/
			if (time[j] < time[pos]) {
				pos = j;
			}
		}

		/*let it first out*/
		mem[pos] = req[i];
		table[pos][i] = req[i];
		time[pos] = i;
	}
	
	
	printTable(table, mnum, M);
	free(time);
	free(mem);
	free(table);
	return count;
}

/*Least Recently Used*/
int lru(int req[], int rnum, int mnum) {
	int count;
	int pos;
	int max;

	/*assign memory*/
	int *mem = (int *)malloc(sizeof(int) * mnum);
	setArray(mem, mnum, -1);

	/*record the time page load in memory*/
	int *time = (int *)malloc(sizeof(int) * mnum);
	setArray(time, mnum, M);

	/*get the record table initialized*/
	int(*table)[M] = (int(*)[M])malloc(sizeof(int) * M * mnum);
	initArr(table, mnum, M);

	/*initialize the page fault rate to 0*/
	count = 0;
	for (int i = 0; i < rnum; i++) {
		/*copy the last record*/
		for (int j = 0; j < mnum; j++) {
			table[j][i] = i ? table[j][i - 1] : -1;
		}

		/*find whether the page in memory*/
		pos = findExist(mem, mnum, req[i]);

		/*if exist*/
		if (pos != -1) {
			/*Record the last visit*/
			time[pos] = i;
			continue;
		}

		/*else*/
		count++;

		/*find whether there is room for new page in memory*/
		pos = findEmpty(mem, mnum);

		/*if there is, place the new page in*/
		if (pos != -1) {
			mem[pos] = req[i];
			table[pos][i] = req[i];
			time[pos] = i;
			continue;
		}

		/*else, find the page to be replaced*/
		pos = 0;
		for (int j = 1; j < mnum; j++) {
			/*find the least recently used*/
			if (time[j] < time[pos]) {
				pos = j;
			}
		}

		/*let it out*/
		mem[pos] = req[i];
		table[pos][i] = req[i];
		time[pos] = i;
	}

	printTable(table, mnum, M);
	free(time);
	free(mem);
	free(table);
	return count;
}

/*Optimal Page Replacement*/
int opt(int req[], int rnum, int mnum) {
	int count;
	int pos;
	int max;

	/*assign memory*/
	int *mem = (int *)malloc(sizeof(int) * mnum);
	setArray(mem, mnum, -1);

	/*record the time page load in memory*/
	int *time = (int *)malloc(sizeof(int) * mnum);
	setArray(time, mnum, M);

	/*get the record table initialized*/
	int(*table)[M] = (int(*)[M])malloc(sizeof(int) * M * mnum);
	initArr(table, mnum, M);

	/*initialize the page fault rate to 0*/
	count = 0;
	for (int i = 0; i < rnum; i++) {
		/*copy the last record*/
		for (int j = 0; j < mnum; j++) {
			table[j][i] = i ? table[j][i - 1] : -1;
		}

		/*find whether the page in memory*/
		pos = findExist(mem, mnum, req[i]);

		/*if exist*/
		if (pos != -1) 
			continue;

		/*else*/
		count++;

		/*find whether there is room for new page in memory*/
		pos = findEmpty(mem, mnum);

		/*if there is, place the new page in*/
		if (pos != -1) {
			mem[pos] = req[i];
			table[pos][i] = req[i];
			continue;
		}

		/*else, find the page to be replaced*/
		setArray(time, mnum, M);

		int k;

		/*find the time that the pages in memory will appear again in 
		the future in the require sequence*/
		for (int j = 0; j < mnum; j++) {
			for (int k = i + 1; k < rnum; k++) {
				if (mem[j] == req[k]) {
					time[j] = k;
					break;
				}
			}
		}

		pos = 0;
		for (int j = 1; j < mnum; j++) {
			/*different with the lru*/
			if (time[j] > time[pos]) {
				pos = j;
			}
		}

		/*let it out*/
		mem[pos] = req[i];
		table[pos][i] = req[i];
	}

	printTable(table, mnum, M);
	free(time);
	free(mem);
	free(table);
	return count;
}

int main(int argc, char** argv) {
	int request[M] = { 2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5, 2 };

	int count;
	int n = 3;

	count = fifo(request, M, n);
	printf("fifo: %d\n", count);

	count = lru(request, M, n);
	printf("lru: %d\n", count);

	count = opt(request, M, n);
	printf("opt: %d\n", count);

	return 0;
}
