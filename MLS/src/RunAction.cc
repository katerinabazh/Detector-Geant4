#include "RunAction.hh"

RunAction::RunAction()
{
    G4AnalysisManager *man = G4AnalysisManager :: Instance();

    man ->CreateNtuple("Hit", "Hits");
    man ->CreateNtupleIColumn("fEvent");
    man ->CreateNtupleDColumn("fX");
    man ->CreateNtupleDColumn("fY");
    man ->CreateNtupleDColumn("fZ");
    man ->FinishNtuple(0);

    man ->CreateNtuple("Scoring", "Scoring");
    man ->CreateNtupleDColumn("LostEnergy");
    man ->FinishNtuple(1);
}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run* )
{
    G4AnalysisManager *man = G4AnalysisManager :: Instance();


    man->OpenFile("NIIKC.root");


//
//    man ->CreateNtuple("Scoring", "Scoring");
//    man->CreateNtupleDColumn("fEdep");
//    man ->FinishNtuple(1);

}

void RunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager :: Instance();

    man->Write();
    man->CloseFile();
}