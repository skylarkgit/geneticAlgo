#pragma once

#include<stdlib.h>

unsigned int* probArray(int acc,int n){
	unsigned int *x=new unsigned int[n];
	
	while(n--) {
		if((rand()%acc)==0) x[n]=1;
		else x[n]=0;
	}
	return x;
}