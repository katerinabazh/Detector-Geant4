#ifndef PHYSICS_HH	//чтобы убедиться,что она не включена(?) несколько раз
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh" //файл используется в physics.сс
#include "G4OpticalPhysics.hh"

class PhysicsList : public G4VModularPhysicsList
{
public:
	PhysicsList();
	~PhysicsList();
};

#endif
