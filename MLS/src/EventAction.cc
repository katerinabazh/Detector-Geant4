#include "EventAction.hh"

using namespace std;

EventAction::EventAction(RunAction*)
{
    fEdep=0.;//c чего начинается подсчет энергии
}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)//вызов функции
{
    fEdep=0.;//чтобы с каждым новым Event начинало с 0
}


void EventAction::EndOfEventAction(const G4Event*)
{
    G4cout <<"Energu deposition: "<< fEdep << G4endl;

    ofstream data("data.txt", ios_base::app);
    data <<"Energu deposition: "<< fEdep <<"\n";
    data.close();

    G4AnalysisManager *man = G4AnalysisManager :: Instance();

    man->FillNtupleDColumn(1,0,fEdep);

    man->AddNtupleRow(1);

}