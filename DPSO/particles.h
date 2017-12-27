#pragma once
//#define <stdlib.h>
#define DPSOData unsigned int

class Particle{
	
	public:
	int n;
	DPSOData *positions;
	DPSOData *velocity;
	double cost;
	DPSOData *bestPositions;
	double bestCost;
	
	void SetBest();
	Particle();
	void Swarm(int);
	~Particle();
};

Particle::Particle(){
}
void Particle::SetBest(){
	for(int i=0;i<n;i++) bestPositions[i]=positions[i];
	bestCost=cost;
}
void Particle::Swarm(int nVar){
	n=nVar;
	positions=new DPSOData[nVar];
	velocity=new DPSOData[nVar];
	bestPositions=new DPSOData[nVar];
	bestCost=999999999999999;
}
Particle::~Particle(){
	delete[] positions;
	delete[] velocity;
	delete[] bestPositions;
}

