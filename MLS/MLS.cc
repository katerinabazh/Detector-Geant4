#include <iostream>

#include "G4RunManager.hh" //для запуска
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "QGSP_BERT.hh"

#include "DetectorConstruction.hh" //не забыть добавить файл с коробкой детектора
#include "ActionInitialization.hh"
#include "PhysicsList.hh"


int main(int argc, char** argv){
	G4RunManager *runManager = new G4RunManager();	// RunManager заботится о событиях, степах и тд. Все это в последующем делается через RunManager
	runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new PhysicsList());
    runManager->SetUserInitialization(new QGSP_BERT(0));////добавление физики
	runManager->SetUserInitialization(new ActionInitialization());
	runManager->Initialize();

    G4UIExecutive *ui = 0;

    if(argc == 1)
    {
        ui = new G4UIExecutive(argc, argv);
    }
	
	G4VisManager *visManager = new G4VisExecutive();	//для визуального запуска Geant
	visManager->Initialize();	//запуск
	
	G4UImanager *UImanager = G4UImanager::GetUIpointer();

    if(ui)
    {
        UImanager->ApplyCommand("/control/execute vis.mac");

        ui->SessionStart();
    }
    else
    {
        UImanager->ApplyCommand("/control/execute run.mac");
    }

	return 0;
}
