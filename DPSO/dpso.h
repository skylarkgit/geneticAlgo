#pragma once

#include<iostream>
#include "stdfunc.h"
#include "operations.h"
#include "particles.h"
#define DPSOData unsigned int
#include<string.h>

class DPSO{
	
	
	//******_______PRIVATE_______******
	private:;
	
	//******_______PUBLIC_______******
	public:
	double bestCost;
	DPSOData* bestPositions;
	Particle* pop;
	
	int maxIt,npop,nVar,Acc;
	DPSO();
	~DPSO();
	void optimize();
	virtual double CostFunction(DPSOData *)=0;
	virtual void initialize(DPSOData*)=0;
	virtual void fill(DPSOData*)=0;
	
	//******_______Uninstantiated METHOD_______******
	static void optimize(void (*CostFunction)(DPSOData *)); 
	
	
};


DPSO::DPSO(){
	maxIt=1;
	npop=2;
	Acc=3;
	pop=new Particle[npop];
	bestCost=99999999999999999;
}

void DPSO::optimize(){
	//std::cout<<"optimizing"<<std::endl;
	int i,j,n=nVar;
	
	for(i=0;i<npop;i++){
		pop[i].Swarm(n);
		initialize(pop[i].positions);					//Initialize positions
		
		memset(pop[i].velocity,0,nVar*sizeof(DPSOData));	//Set velocity to zero
		pop[i].cost=CostFunction(pop[i].positions);		//Cost Calculation
		pop[i].SetBest();								//Set Current cost as best
		if(pop[i].cost<bestCost) {
			bestCost=pop[i].cost;
			bestPositions=pop[i].bestPositions;
		}
	}
	

	for(j=0;j<maxIt;j++){
		//std::cout<<"Iteration "<<j<<std::endl;
		
		using namespace Operations;
		
		for(i=0;i<npop;i++){
			
			//V=V+((R1x(P-X))+(R2x(PG-X)))
			DPSOData *R1=probArray(Acc,n);
			DPSOData *R2=probArray(Acc,n);
			
			DPSOData *result2=o_minus(bestPositions,pop[i].positions,n);
			DPSOData *result1=o_minus(pop[i].bestPositions,pop[i].positions,n);
			DPSOData *G=o_mult(R1,result1,n);
			DPSOData *L=o_mult(R2,result2,n);
			
			delete[] result1;
			delete[] result2;
			delete[] R1;
			
			for(int k=0;k<n;k++) std::cout<<pop[i].positions[k]<<" ";std::cout<<std::endl;
			
			result1=o_plus(G,L,n);
			result2=pop[i].velocity;
			pop[i].velocity=o_plus(result2,result1,n);
			fill(pop[i].velocity);
			R1=pop[i].positions;
			
			for(int k=0;k<n;k++) std::cout<<pop[i].positions[k]<<" ";std::cout<<std::endl;
			pop[i].positions=o_plus(R1,pop[i].velocity,n);
			for(int k=0;k<n;k++) std::cout<<pop[i].positions[k]<<" ";std::cout<<std::endl;
			pop[i].cost=CostFunction(pop[i].positions);		//Cost Calculation
			
			if(pop[i].cost<pop[i].bestCost) pop[i].SetBest();
			if(pop[i].cost<bestCost) {
				bestCost=pop[i].cost;
				bestPositions=pop[i].bestPositions;
			}
			
			for(int k=0;k<n;k++) std::cout<<pop[i].positions[k]<<" ";std::cout<<"("<<pop[i].bestCost<<")"<<std::endl;
			
			delete[] result1;
			delete[] result2;
			delete[] G;
			delete[] L;
			delete[] R1;
			delete[] R2;
		}
		
	}
}
DPSO::~DPSO(){
	delete[] pop;
}