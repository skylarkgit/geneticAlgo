#include<iostream>
#include "dpso.h"
#include<bits/stdc++.h>
using namespace std;

class multiProcSchdl : public DPSO{
	
	public:
	int machines;
	double *taskCost;
	double CostFunction(DPSOData *);
	void initialize(DPSOData*);
	void fill(DPSOData*);
	multiProcSchdl(int);
	~multiProcSchdl();
};

multiProcSchdl::multiProcSchdl(int n){
	nVar=n;
	machines=5;
	
	taskCost=new double[n];
}
multiProcSchdl::~multiProcSchdl(){
	
	delete[] taskCost;
}

double multiProcSchdl::CostFunction(DPSOData* x){
	double unitcost[machines],most=0,temp;
	memset(unitcost,0,machines*sizeof(double));
	for(int i=0;i<nVar;i++){
		temp=(unitcost[x[i]-1]+=taskCost[i]);
		if(temp>most) most=temp;
	}
	return most;
}

void multiProcSchdl::initialize(DPSOData* x){
	for(int i=0;i<nVar;i++) x[i]=1+(rand()%machines);
}

void multiProcSchdl::fill(DPSOData* x){
	double cost=0,unitcost[machines],most=0,temp;
	memset(unitcost,0,machines*sizeof(double));
	for(int i=0;i<nVar;i++){
		if(x[i])
		unitcost[x[i]-1]+=taskCost[i];
	}
	sort(unitcost,unitcost+machines);
	for(int i=0;i<nVar;i++){
		if(x[i]) continue;
		x[i]=1+(rand()%machines);
	}
}

int main(){
	int n=20;
	multiProcSchdl s(n);
	s.taskCost[0]=1;s.taskCost[1]=1;s.taskCost[2]=1;s.taskCost[3]=1;s.taskCost[4]=1;
	s.taskCost[5]=1;s.taskCost[6]=1;s.taskCost[7]=1;s.taskCost[8]=1;s.taskCost[9]=1;
	s.taskCost[14]=1;s.taskCost[10]=1;s.taskCost[11]=1;s.taskCost[12]=1;s.taskCost[13]=1;
	s.taskCost[15]=1;s.taskCost[16]=1;s.taskCost[17]=1;s.taskCost[18]=1;s.taskCost[19]=1;
	s.optimize();
	//while(n--) cout<<endl<<s.bestPositions[n]<<endl;
	cout<<s.bestCost<<endl;
}