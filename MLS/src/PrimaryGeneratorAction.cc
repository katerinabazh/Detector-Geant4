#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
	fParticleGun = new G4ParticleGun(1);

    G4ParticleTable *particleTable = G4ParticleTable :: GetParticleTable();
    G4String particleproton="proton";
    //G4ParticleDefinition *particle = particleTable->FindParticle("e-"); //собирает всю ифу по частице "протон"(масса,энергия и тд) и передает (G4ParticleDefinition)
    G4ParticleDefinition *particle = particleTable->FindParticle(particleproton);

    G4double x0 = (G4UniformRand())*cm;
    G4double y0 = (G4UniformRand())*cm;
    G4double z0 = 17.5*cm;
    G4ThreeVector pos(x0,y0,z0);

    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleEnergy(1*GeV);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,-1.));
    fParticleGun ->SetParticlePosition(pos);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
	delete fParticleGun;
}

void PrimaryGeneratorAction :: GeneratePrimaries(G4Event *anEvent)
{
 	fParticleGun ->GeneratePrimaryVertex(anEvent);
}