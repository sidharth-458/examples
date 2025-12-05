#include<stdio.h>

int pos_nt_zero(int n){
	int c = n;
	int p0 = 0;
	int p1 = 1;
	while( !(c & 1) && (c!=0)){
		c>>1;
		p0++;
	}
	while(c & 1){
		c >>1;
		p1++;
	}
	if(p1 + p0 == 31 || p1 + p0 == 0){
		return -1;
	}

	p = p

int nearestlarge(int n){
	
