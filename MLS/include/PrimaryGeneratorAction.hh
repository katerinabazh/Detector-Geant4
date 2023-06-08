#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh" //специяльно для генератора

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
	PrimaryGeneratorAction();
	~PrimaryGeneratorAction();
	
	virtual void GeneratePrimaries(G4Event*); 	//Ф-я GeneratePrimaries запускает генерацию частиц
							//G4Event - необходимый класс
private:
	G4ParticleGun *fParticleGun;//вызову пушки с частицами(?)
};

#endif
