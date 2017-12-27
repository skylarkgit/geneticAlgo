#pragma once
#include <stdlib.h>
#define DPSOData unsigned int

namespace Operations{
	
	
	DPSOData *o_plus(DPSOData*,DPSOData*,int);
	DPSOData *o_minus(DPSOData*,DPSOData*,int);
	DPSOData *o_mult(DPSOData*,DPSOData*,int);
	
	
}

DPSOData* Operations::o_plus(DPSOData x[],DPSOData y[],int n){
	
	DPSOData *result=new DPSOData[n];
	int from=rand()%n;
	int to=from+(rand()%(n-from));
	int i=0;
	while(i<n){
		if(i>=from&&i<=to) result[i]=x[i];
		else result[i]=y[i];
		i++;
	}
	return result;
	
}

DPSOData* Operations::o_mult(DPSOData x[],DPSOData y[],int n){
	
	DPSOData *result=new DPSOData[n];
	int i=0;
	while(i<n){
		if(x[i]) result[i]=y[i];
		else result[i]=0;
		i++;
	}
	return result;
	
}

DPSOData* Operations::o_minus(DPSOData x[],DPSOData y[],int n){
	
	DPSOData *result=new DPSOData[n];
	int i=0;
	while(i<n){
		if(x[i]==y[i]) result[i]=0;
		else result[i]=x[i];
		i++;
	}
	return result;
	
}