/*************************************************************************
    > File Name: merge.c
    > Author: Hsu
    > Mail: lem4315063@outlook.com 
    > Created Time: 2018-04-30
 ************************************************************************/

#include <stdio.h>

/*
 * Traditional merge sort
 * imperative style
 * not friendly to condition move instructions
 */
void merge(long src1[], long src2[], long dest[], long n){
    long i1 = 0, i2 = 0, id = 0;
    while(i1 < n && i2 < n){
        if (src1[i1] < src2[i2])
            dest[id++] = src1[i1++];
        else
            dest[id++] = src2[i2++];
    }

    while(i1 < n)
        dest[id++] = src1[i1++];
    while(i2 < n)
        dest[id++] = src2[i2++];
}

/*
 * Modified merge sort
 * functional style
 * friendly to condition move instructions
 */
void merge2(long src1[], long src2[], long dest[], long n){
    long i1 = 0, i2 = 0, id = 0;
    while(i1 < n && i2 < n){
        long v1 = src1[i1];
        long v2 = src2[i2];
        int take = v1 < v2;
        dest[id++] = take ? v1 : v2;
        i1 += take;
        i2 += (1-take);
    }

    while(i1 < n)
        dest[id++] = src1[i1++];
    while(i2 < n)
        dest[id++] = src2[i2++];
}
