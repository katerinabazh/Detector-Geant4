#ifndef SENSITIVEDETECTOR_HH
#define SENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
//#include "SteppingAction.hh"
//#include "RunAction.hh"

#include "g4root.hh"

#include <iostream>
#include <fstream>

class SensitiveDetector : public G4VSensitiveDetector
{
public:
    SensitiveDetector(G4String);
    ~SensitiveDetector();
    G4double PosZ;

private:
     G4bool ProcessHits(G4Step* , G4TouchableHistory* );

};

#endif
