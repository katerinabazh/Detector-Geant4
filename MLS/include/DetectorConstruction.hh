#ifndef DETETORCONSTRUCTION_HH
#define DETETORCONSTRUCTION_HH


#include "G4SystemOfUnits.hh" //необходим,чтобы использовать метры,сантиметры,градусы,гигаэлектрон-вольт и т.д.
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh" //использовался в construction.cc для физического объема
#include "G4NistManager.hh" //для взятия материала (окружающего) детектор из готовой библиотеки
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "SensitiveDetector.hh"

#include <vector>
#include "G4PVParameterised.hh"

//файл с детектором добавляется в конструкцию детектора


class G4VisAttributes;


class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
	DetectorConstruction();
	~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

							
private:
    void DefineCommands();

    void ConstructMaterials();
    void ConstructFiber(G4int NofColumns, G4int NofRows,G4int k);

    virtual G4VPhysicalVolume *DefineVolumes();
    G4Material* worldMaterial;  // pointer to the target  material
    G4Material* ScintillatorMaterial;
    G4Material* TYVECMaterial;
    G4Material* AlMaterial;
    G4Material* WMaterial;
    G4Material* AcrylicMaterial;
    G4Material* Epotek301;
//    G4Material* PbWO4Material;





    std::vector<G4VisAttributes*> fVisAttributes;
	G4LogicalVolume* flogicScintillatorFiber;
    G4LogicalVolume* flogicAcrylicFiber;
    G4LogicalVolume*  flogicFiberBox;
    G4LogicalVolume*  flogicScintillatorPlate04;
    G4LogicalVolume*  flogicScintillatorPlate02;
    G4LogicalVolume*  flogicScintillatorAnticoincidenceUpper;
    G4LogicalVolume* flogicScintillatorAnticoincidenceLower;
    G4LogicalVolume* flogicScintillatorPlate05;
    virtual void ConstructSDandField() override;
};

#endif
