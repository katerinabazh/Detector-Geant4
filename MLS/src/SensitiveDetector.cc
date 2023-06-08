#include "SensitiveDetector.hh"

using namespace std;
extern std::ofstream data("data.txt");


SensitiveDetector::SensitiveDetector(G4String Name): G4VSensitiveDetector(Name)
{
    ofstream data("data.txt", ios_base::app);
    data << "Time(ns)        ParticleName      Energy           SciDetectorNumber         Position(cm)"<<"\n";
    data.close();
}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep ->GetTrack();
    //aStep->GetTrack()->SetTrackStatus(fStopAndKill);



    G4StepPoint *preStepPoint = aStep ->GetPreStepPoint();
    //G4StepPoint *postStepPoint = aStep ->GetPostStepPoint();
    G4double globalTime = aStep->GetPostStepPoint()->GetGlobalTime();
    PosZ = aStep->GetPreStepPoint()->GetPosition().z();

    G4ThreeVector posPhoton = preStepPoint ->GetPosition();

    const G4VTouchable *touchable =aStep ->GetPreStepPoint()->GetTouchable();
    G4int SciDetectorNumber = touchable->GetCopyNumber();
    G4double edep = aStep -> GetTotalEnergyDeposit();
    G4String ParticleName= track->GetDefinition()->GetParticleName();

    G4VPhysicalVolume *physVol = touchable -> GetVolume();
    G4ThreeVector posDetector = physVol ->GetTranslation();
    G4cout<< "Detector position: "<<posDetector<<G4endl;



    ofstream data("data.txt", ios_base::app);
    if (edep !=0.0000) {
        if((SciDetectorNumber>0  && SciDetectorNumber< 6)|| (SciDetectorNumber>1157  && SciDetectorNumber< 1162) )
        {
            data  <<globalTime<< "________";
        }
        else {  data  <<"______________"<< "______________";}

        data  <<ParticleName<< "______________";
        data << edep << "______________";
        data << SciDetectorNumber << "______________";
        data << posDetector << "______________";
        data <<"\n";
    }

    data.close();

    G4int evt = G4RunManager ::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4AnalysisManager *man = G4AnalysisManager :: Instance();
    man-> FillNtupleIColumn(0,evt);
    man ->FillNtupleDColumn(1,posDetector[0]);
    man ->FillNtupleDColumn(2,posDetector[1]);
    man ->FillNtupleDColumn(3,posDetector[2]);
    man->AddNtupleRow(0);


    return true;
}

SensitiveDetector::~SensitiveDetector()
{

}