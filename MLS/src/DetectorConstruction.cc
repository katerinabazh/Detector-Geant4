#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
:
  fVisAttributes()
  {}

DetectorConstruction::~DetectorConstruction()
{
    for (auto visAttributes: fVisAttributes) {
        delete visAttributes;
    }
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
    ConstructMaterials();

    return DefineVolumes();
}

void DetectorConstruction::ConstructMaterials()
{
    G4NistManager *nist= G4NistManager::Instance();

//Определение материалов
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic"); //класс материалов Material //FindorBuildMaterial функция ищет материал из скобок и присваивает worldMat

// Scintillator or Polystyrene
    G4Material *Sci = new G4Material("Scintillator",1.05*g/cm3,2);
    Sci->AddElement(nist->FindOrBuildElement ("C"),8);
    Sci->AddElement(nist->FindOrBuildElement ("H"),8);

// TYVEC
    G4Material *TYVEC = new G4Material("TYVEC",0.4*g/cm3,2); //name="TYVEC", density, ncomponents=2
    TYVEC->AddElement(nist->FindOrBuildElement ("C"),2);
    TYVEC->AddElement(nist->FindOrBuildElement ("H"),4);

//Acrylic
    G4Material* Acrylic = new G4Material("Acrylic", 1.19*g/cm3,3);
    Acrylic->AddElement(nist->FindOrBuildElement ("C"), 5);
    Acrylic->AddElement(nist->FindOrBuildElement ("H"), 8);
    Acrylic->AddElement(nist->FindOrBuildElement ("O"), 2);



//    G4double epoxy_den = 1.190*g/cm3;
//    G4double tungsten_den = 19.3*g/cm3;

//Epoxy (for FR4 )

    G4Material* Epoxy = new G4Material("Epoxy" ,  1.2*g/cm3, 2);
    Epoxy->AddElement(nist->FindOrBuildElement ("H"),2);
    Epoxy->AddElement(nist->FindOrBuildElement ("C"), 2);
    G4Material *TiO2 = new G4Material("TiO2",4.23*g/cm3,2);
    TiO2->AddElement(nist->FindOrBuildElement ("Ti"),1);
    TiO2->AddElement(nist->FindOrBuildElement ("O"),2);

    G4Material *Epotek = new G4Material("Epotek",1.2*g/cm3,2);
    Epotek->AddMaterial(TiO2,25.0*perCent);
    Epotek->AddMaterial(Epoxy,75.0*perCent);

   //PbWO4
//   G4Material *PbWO4 = new G4Material("PbWO4", 8.28*g/cm3,3);
//   PbWO4->AddElement(nist->FindOrBuildElement ("Pb"),1);
//   PbWO4->AddElement(nist->FindOrBuildElement ("W"),1);
//   PbWO4->AddElement(nist->FindOrBuildElement ("O,"),4);
    //G4Material *PbWO4 = new G4Material("Lead", 82., 207.2*g/mole, 11.34*g/cm3);
    // G4Material *PbWO4 = new G4Material("Tungsten", 74., 183.84*g/mole, 	19.3*g/cm3);
    // G4Material *PbWO4 = new G4Material("Oxygen", 8., 16.*g/mole, 	1.141*g/cm3);
    //PbWO4Material=PbWO4;


    worldMaterial = worldMat;
    ScintillatorMaterial = Sci;
    TYVECMaterial = TYVEC;
    AlMaterial = new G4Material("Alluminium", 13., 26.98*g/mole, 2.7*g/cm3);
    AcrylicMaterial = Acrylic;
    Epotek301=Epotek;
    WMaterial = new G4Material("Wolframium", 74., 183.84*g/mole, 19.25*g/cm3);

 }

void DetectorConstruction::ConstructFiber(G4int NofColumns, G4int NofRows,G4int DefenitionOfVolume)
{
    for (G4int i=0;i<NofColumns;i += 1)
    {
        for (G4int j=0;j<NofRows;j+=1)
        {
            if(DefenitionOfVolume==0)
            {
                if (i % 2 == 0)//отдельно реализуются четные и нечетные стрипы
                {
                    double k = 0.5003;
                    new G4PVPlacement(0,
                                      G4ThreeVector(-1.5009 * mm + i * mm,
                                                    (-11.5 * cm + 0.5003 * mm) + j * mm + k * mm, 0.),
                                      flogicScintillatorFiber,
                                      "physFiber",
                                      flogicFiberBox,
                                      false,
                                      6 + j + i * NofRows,
                                      true);
                } else {
                    double k = 0;
                    new G4PVPlacement(0,
                                      G4ThreeVector(-1.5009 * mm + i * mm,
                                                            (-11.5 * cm + 0.5003 * mm) + j * mm + k * mm, 0.),
                                      flogicScintillatorFiber,
                                      "physFiber",
                                      flogicFiberBox,
                                      false,
                                      6 + j + i * NofRows,
                                      true);

                }
            }
          else {
                if (i % 2 == 0)//отдельно реализуются четные и нечетные стрипы
                {
                    double k = 0.5003;
                    new G4PVPlacement(0,
                                      G4ThreeVector(-1.5009 * mm + i * mm,
                                                    (-11.5 * cm + 0.5003 * mm) + j * mm + k * mm, 0.),
                                      flogicAcrylicFiber,
                                      "physFiber1",
                                      flogicFiberBox,
                                      false,
                                      0,
                                      true);
                } else {
                    double k = 0;
                    new G4PVPlacement(0,
                                      G4ThreeVector(-1.5009 * mm + i * mm,
                                                    (-11.5 * cm + 0.5003 * mm) + j * mm + k * mm, 0.),
                                      flogicAcrylicFiber,
                                      "physFiber1",
                                      flogicFiberBox,
                                      false,
                                      0,
                                      true);

                }
            }
        }
    }


}

G4VPhysicalVolume *DetectorConstruction::DefineVolumes()
{
//WorldVolume
    G4Box *solidWorld =
        new G4Box("solidWorld",
           1.*m,
           1.*m,
           1.*m);
    G4LogicalVolume* logicWorld =
        new G4LogicalVolume(solidWorld,
                            worldMaterial,
                            "logicWorld");
    // logicWorld -> SetVisAttributes(G4VisAttributes::GetInvisible());//невидимость
    G4VPhysicalVolume* physWorld =
        new G4PVPlacement(0,
                          G4ThreeVector(0.,0.,0.),
                          logicWorld,
                          "physWorld",
                          0,
                          false,
                          0,
                          true);

//Detector Box
    G4Box *solidDetector =
            new G4Box("solidDetector",
                      17.*cm,
                      17.*cm,
                      35.*cm);
    G4LogicalVolume* logicDetector =
            new G4LogicalVolume(solidDetector,
                                worldMaterial,
                                "logicDetector");
    logicDetector -> SetVisAttributes(G4VisAttributes::GetInvisible());//невидимость
    new G4PVPlacement(0,
                      G4ThreeVector(0.,0.,0.),
                      logicDetector,
                      "physDetector",
                      logicWorld,
                      false,
                      0,
                      true);

//верхняя пластина целого счинтиллятора
    G4Box *solidAlPlate = new G4Box("solidAlPlate",11.5*cm,11.5*cm,0.005*cm);
    G4LogicalVolume* logicAlPlate=
            new G4LogicalVolume(solidAlPlate,
                                AlMaterial,
                                "logicAlPlate");
    G4Box *solidTYVECPlate = new G4Box("solidTYVECPlate",11.5*cm,11.5*cm,0.01*cm);
    G4LogicalVolume* logicTYVECPlate=
            new G4LogicalVolume(solidTYVECPlate,
                                TYVECMaterial,
                                "logicTYVECPlate");
    G4Box *solidScintillatorPlate02 = new G4Box("solidScintillatorPlate02",11.5*cm,11.5*cm,0.1*cm);
    flogicScintillatorPlate02 =
            new G4LogicalVolume(solidScintillatorPlate02,
                                ScintillatorMaterial,
                                "logicScintillatorPlate02");
    for (G4int i=0; i<2;i++){
        new G4PVPlacement(0,
                          G4ThreeVector(0.,0.,(4.0-0.125)*cm+ i*2*0.125*cm),
                          logicAlPlate,
                          "physAlPlate",
                          logicDetector,
                          false,
                          0,
                          true);
    }
    for (G4int i=0; i<2;i++) {
        new G4PVPlacement(0,
                          G4ThreeVector(0., 0., (4.0-0.11) * cm + i * 0.22 * cm),
                          logicTYVECPlate,
                          "physTYVECPlate",
                          logicDetector,
                          false,
                          0,
                          true);
    }
    new G4PVPlacement(0,
                      G4ThreeVector(0.,0.,4.0*cm),
                      flogicScintillatorPlate02,
                      "physScintillatorPlate02",
                      logicDetector,
                      false,
                      1,
                      true);

//AC антисовпадения
    G4Box *solidAnticoincidenceUpper = new G4Box("solidAnticoincidenceUpper",11.5*cm,0.1*cm,0.24*cm);
    G4LogicalVolume* logicAnticoincidenceUpper =
            new G4LogicalVolume(solidAnticoincidenceUpper,
                                ScintillatorMaterial,
                                "logicAnticoincidenceUpper");
    new G4PVPlacement(0,
                      G4ThreeVector(0.,11.7*cm,3.34*cm),
                      logicAnticoincidenceUpper,
                      "physAnticoincidenceUpper0",
                      logicDetector,
                      false,
                      0,
                      true);
    G4RotationMatrix* fieldRot3 = new G4RotationMatrix();
    fieldRot3->rotateY(180.*deg);
    new G4PVPlacement(fieldRot3,
                      G4ThreeVector(0.,-11.7*cm,3.34*cm),
                      logicAnticoincidenceUpper,
                      "physAnticoincidenceUpper1",
                      logicDetector,
                      false,
                      0,
                      true);
   G4RotationMatrix* fieldRot4 = new G4RotationMatrix();
   fieldRot4->rotateZ(90.*deg);
   new G4PVPlacement(fieldRot4,
                     G4ThreeVector(11.7*cm,0.*cm,3.34*cm),
                     logicAnticoincidenceUpper,
                     "physAnticoincidenceUpper2",
                     logicDetector,
                     false,
                     0,
                     true);
    G4RotationMatrix* fieldRot5 = new G4RotationMatrix();
    fieldRot5->rotateZ(-90.*deg);
    new G4PVPlacement(fieldRot5,
                      G4ThreeVector(-11.7*cm,0.*cm,3.34*cm),
                      logicAnticoincidenceUpper,
                      "physAnticoincidenceUpper3",
                      logicDetector,
                      false,
                      0,
                      true);

//система антисовпадений(черновая)
    new G4PVPlacement(0,
                      G4ThreeVector(0.,0.,(3.23-0.125)*cm),
                      logicAlPlate,
                      "physAlPlate",
                      logicDetector,
                      false,
                      0,
                      true);
    for (G4int i=0; i<3;i++){
        new G4PVPlacement(0,
                          G4ThreeVector(0., 0., (3.23-0.11) * cm + i * 0.22 * cm),
                          logicTYVECPlate,
                          "physTYVECPlate",
                          logicDetector,
                          false,
                          0,
                          true);
    }

//формирование слоя сцинтилл. антисовпадений(верхнего)
    G4Box *solidScintillatorAnticoincidenceUpper = new G4Box("solidScintillatorAnticoincidenceUpper",11.5*cm,5.7*cm,0.1*cm);
    flogicScintillatorAnticoincidenceUpper =
            new G4LogicalVolume(solidScintillatorAnticoincidenceUpper,
                                ScintillatorMaterial,
                                "logicScintillatorAnticoincidenceUpper");
    for (G4int i=0;i<2;i++) {
        new G4PVPlacement(0,
                          G4ThreeVector(0., -5.8 * cm + i*11.6*cm, 3.45 * cm),
                          flogicScintillatorAnticoincidenceUpper,
                          "physScintillatorAnticoincidenceUpper",
                          logicDetector,
                          false,
                          2+i,
                          true);
    }
    G4RotationMatrix* fieldRot2 = new G4RotationMatrix();
    fieldRot2->rotateZ(90.*deg);
    for (G4int i=0;i<2;i++) {
        new G4PVPlacement(fieldRot2,
                          G4ThreeVector(-5.8 * cm + i * 11.6 * cm,0. , 3.23 * cm),
                          flogicScintillatorAnticoincidenceUpper,
                          "physScintillatorAnticoincidenceUpper1",
                          logicDetector,
                          false,
                          4+i,
                          true);
    }
    new G4PVPlacement(0,
                      G4ThreeVector(0.,0.,3.575*cm),
                      logicAlPlate,
                      "physAlPlate",
                      logicDetector,
                      false,
                      0,
                      true);

//создание и множение Fiber
// сцинтиллятор
    G4double innerRadius = 0.*cm;
    G4double outerRadius = 0.5*mm;
    G4double hx = 11.5*cm;
    G4double startAngle = 0.*deg;
    G4double spanningAngle = 360.*deg;

//акриловая оболочка
    G4double innerRadius1 = 0.50001*mm;//данный размер подобран лишь для видимости счинтиллятора внутри акрила
    G4double outerRadius1 = 0.5003*mm;
    G4double hx1 = 11.5*cm;
    G4double startAngle1 = 0.*deg;
    G4double spanningAngle1 = 360.*deg;

//Fiber Box
   G4Box *solidFiberBox =
           new G4Box("solidFiberBox",
                     2.0012*mm,
                     11.5*cm,
                     11.5*cm);
   flogicFiberBox  =
            new G4LogicalVolume(solidFiberBox,
                                Epotek301,
                                "logicFiberBox");

   G4RotationMatrix* fieldRot = new G4RotationMatrix();
    fieldRot->rotateY(90.*deg);
    new G4PVPlacement(fieldRot,
                      G4ThreeVector(0.,0.,2.44*cm),
                      flogicFiberBox,
                      "physFiberBox1",
                      logicDetector,
                      false,
                      0,
                      true);
    new G4PVPlacement(fieldRot,
                      G4ThreeVector(0.,0.,-(2.0012*2 + 2.0012)*mm),
                      flogicFiberBox,
                      "physFiberBox3",
                      logicDetector,
                      false,
                      0,
                      true);

   G4RotationMatrix* fieldRot1 = new G4RotationMatrix();
    fieldRot1->rotateY(90.*deg);
    fieldRot1->rotateX(90.*deg);
    new G4PVPlacement(fieldRot1,
                      G4ThreeVector(0.,0.,2.84*cm),
                      flogicFiberBox,
                      "physFiberBox2",
                      logicDetector,
                      false,
                      0,
                      true);
    new G4PVPlacement(fieldRot1,
                      G4ThreeVector(0.,0.,-2.0012*mm),
                      flogicFiberBox,
                      "physFiberBox4",
                      logicDetector,
                      false,
                      0,
                      true);

//заполнение объема счинтилляторами fiber
    G4Tubs *solidScintillatorFiber = new G4Tubs("solidScintillatorFiber",innerRadius,outerRadius,hx,startAngle,spanningAngle);
     flogicScintillatorFiber =
        new G4LogicalVolume(solidScintillatorFiber,
                            ScintillatorMaterial,
                            "logicScintillatorFiber");
    G4int NofColumns=4;
    G4int NofRows=229;
    ConstructFiber( NofColumns,  NofRows,0);//функция создает стрипы

    G4Tubs *solidAcrylicFiber = new G4Tubs("solidAcrylicFiber",innerRadius1,outerRadius1,hx1,startAngle1,spanningAngle1);
    flogicAcrylicFiber =
         new G4LogicalVolume(solidAcrylicFiber,
                             AcrylicMaterial,
                             "logicAcrylicFiber");
    ConstructFiber( NofColumns,  NofRows,1);


//пластины сцинтилляц
    G4Box *solidScintillatorPlate04 = new G4Box("solidScintillatorPlate04",11.5*cm,11.5*cm,0.2*cm);
    flogicScintillatorPlate04 =
            new G4LogicalVolume(solidScintillatorPlate04,
                                ScintillatorMaterial,
                                "logicScintillatorPlate04");
    for (G4int i=0; i<2;i++){
         new G4PVPlacement(0,
                           G4ThreeVector(0.,0.,0.005*cm+ i*2.13*cm),
                           logicAlPlate,
                           "physAlPlate",
                           logicDetector,
                           false,
                           0,
                           true);
    }
    for (G4int i=0; i<6;i++){
        new G4PVPlacement(0,
                          G4ThreeVector(0.,0.,0.02*cm +i*0.42*cm),
                          logicTYVECPlate,
                          "physTYVECPlate",
                          logicDetector,
                          false,
                          0,
                          true);
    }
    for (G4int i=0; i<5;i++){   //5 штук сцинтилляц пластин
         new G4PVPlacement(0,
                           G4ThreeVector(0.,0.,0.23*cm +i*0.42*cm),
                           flogicScintillatorPlate04,
                           "physScintillatorPlate04",
                           logicWorld,
                           false,
                           6 + NofRows + NofColumns*NofRows + 1 +i,
                           true);
    }

//формирование слоя сцинтилл. антисовпадений(нижнего)
    G4Box *solidAlAnticoincidenceLower = new G4Box("solidAlAnticoincidenceLower",11.8*cm,11.8*cm,0.005*cm);
    G4LogicalVolume* logicAlAnticoincidenceLower =
            new G4LogicalVolume(solidAlAnticoincidenceLower,
                                AlMaterial,
                                "logicAlAnticoincidenceLower");

    G4Box *solidTYVECAnticoincidenceLower = new G4Box("solidTYVECAnticoincidenceLower",11.8*cm,11.8*cm,0.01*cm);
    G4LogicalVolume* logicTYVECAnticoincidenceLower =
            new G4LogicalVolume(solidTYVECAnticoincidenceLower,
                                TYVECMaterial,
                                "logicTYVECAnticoincidenceLower");
    G4Box *solidScintillatorAnticoincidenceLower = new G4Box("solidScintillatorAnticoincidenceLower",11.8*cm,3.9*cm,0.1*cm);
    flogicScintillatorAnticoincidenceLower =
            new G4LogicalVolume(solidScintillatorAnticoincidenceLower,
                                ScintillatorMaterial,
                                "logicScintillatorAnticoincidenceLower");
    for(G4int i=0;i<2;i++){
         new G4PVPlacement(0,
                       G4ThreeVector(0., 0., -0.905 * cm - i * 0.47 * cm),
                       logicAlAnticoincidenceLower,
                       "physAlAnticoincidenceLower",
                       logicDetector,
                       false,
                       0,
                       true);
    }
    for(G4int i=0;i<3;i++) {
        new G4PVPlacement(0,
                          G4ThreeVector(0., 0., -0.92 * cm - i*0.22*cm),
                          logicTYVECAnticoincidenceLower,
                          "physTYVECAnticoincidenceLower",
                          logicDetector,
                          false,
                          0,
                          true);
    }
    for(G4int i=0;i<3;i++) {
        new G4PVPlacement(0,
                          G4ThreeVector(0., -7.9 * cm + i * 7.9 * cm, -1.03 * cm),
                          flogicScintillatorAnticoincidenceLower,
                          "physScintillatorAnticoincidenceLower",
                          logicDetector,
                          false,
                          6 + NofRows + NofColumns*NofRows + 5 +1 +i,
                          true);
    }
    for(G4int i=0;i<3;i++) {
        new G4PVPlacement(fieldRot4,
                          G4ThreeVector(-7.9 * cm + i * 7.9 * cm,0.,  -1.25 * cm),
                          flogicScintillatorAnticoincidenceLower,
                          "physScintillatorAnticoincidenceLower1",
                          logicDetector,
                          false,
                          6 + NofRows + NofColumns*NofRows + 8 +1 +i,
                          true);
    }

//нижняя часть детектора
    G4Box *solidScintillatorPlate05 = new G4Box("solidScintillatorPlate05",11.5*cm,11.5*cm,0.25*cm);
    flogicScintillatorPlate05 =
            new G4LogicalVolume(solidScintillatorPlate05,
                                ScintillatorMaterial,
                                "logicScintillatorPlate05");
    for(G4int i=0;i<2;i++) {
        new G4PVPlacement(0,
                          G4ThreeVector(0., 0., -2.005 * cm - i * 2.47 * cm),
                          logicAlPlate,
                          "physAlPlate",
                          logicDetector,
                          false,
                          0,
                          true);
    }
    for(G4double k=2.02,i=0;i<2;i++) {
        for(G4int j=0;j<4;j++) {
            new G4PVPlacement(0,
                              G4ThreeVector(0., 0., -k * cm - j * 0.64 * cm),
                              logicTYVECPlate,
                              "physTYVECPlate",
                              logicDetector,
                              false,
                              0,
                              true);

        }
        k = 2.54;
    }
    for(G4int i=0;i<4;i++) {
        new G4PVPlacement(0,
                          G4ThreeVector(0., 0., -2.28 * cm - i* 0.64 * cm),
                          flogicScintillatorPlate05,
                          "physScintillatorPlate05",
                          logicDetector,
                          false,
                          6 + NofRows + NofColumns*NofRows + 11 +1 +i,
                          true);

    }
    G4Box *solidWolframiumPlate = new G4Box("solidWolframiumPlate",11.5*cm,11.5*cm,0.05*cm);
    G4LogicalVolume* logicWolframiumPlate =
            new G4LogicalVolume(solidWolframiumPlate,
                                WMaterial,
                                "logicWolframiumPlate");
    for(G4int i=0;i<3;i++) {
        new G4PVPlacement(0,
                          G4ThreeVector(0., 0., -2.6 * cm - i* 0.64 * cm),
                          logicWolframiumPlate,
                          "physWolframiumPlate",
                          logicDetector,
                          false,
                          0,
                          true);

    }

//AC антисовпадения нижние
    G4Box *solidAnticoincidenceLower = new G4Box("solidAnticoincidenceLower",11.5*cm,0.1*cm,1.24*cm);
    G4LogicalVolume* logicAnticoincidenceLower =
            new G4LogicalVolume(solidAnticoincidenceLower,
                                ScintillatorMaterial,
                                "logicAnticoincidenceLower");
    new G4PVPlacement(0,
                      G4ThreeVector(0.,11.7*cm,-3.24*cm),
                      logicAnticoincidenceLower,
                      "physAnticoincidenceLower0",
                      logicDetector,
                      false,
                      0,
                      true);
    new G4PVPlacement(fieldRot3,
                      G4ThreeVector(0.,-11.7*cm,-3.24*cm),
                      logicAnticoincidenceLower,
                      "physAnticoincidenceLower1",
                      logicDetector,
                      false,
                      0,
                      true);
    new G4PVPlacement(fieldRot4,
                      G4ThreeVector(11.7*cm,0.*cm,-3.24*cm),
                      logicAnticoincidenceLower,
                      "physAnticoincidenceLower2",
                      logicDetector,
                      false,
                      0,
                      true);
    new G4PVPlacement(fieldRot5,
                      G4ThreeVector(-11.7*cm,0.*cm,-3.24*cm),
                      logicAnticoincidenceLower,
                      "physAnticoincidenceLower3",
                      logicDetector,
                      false,
                      0,
                      true);

//   G4Box *solidWolframiumPlate1 = new G4Box("solidWolframiumPlate1",11.5*cm,11.5*cm,5.*cm);
//   G4LogicalVolume* logicWolframiumPlate1 =
//           new G4LogicalVolume(solidWolframiumPlate1,
//                               WMaterial,
//                               "logicWolframiumPlate1");
//   new G4PVPlacement(0,
//                     G4ThreeVector(0., 0., -10.0* cm ),
//                     logicWolframiumPlate1,
//                     "physWolframiumPlate",
//                     logicDetector,
//                     false,
//                     0,
//                     true);


// расзными цветами, визуализация
  auto visAttributes = new G4VisAttributes(G4Colour(0.9,0.9,0.0));//желтая
  flogicScintillatorPlate04->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);
  flogicScintillatorPlate02->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);
  flogicScintillatorAnticoincidenceUpper->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);
  flogicScintillatorAnticoincidenceLower->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);
  flogicScintillatorPlate05->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);

  visAttributes = new G4VisAttributes(G4Colour(0.0, 0.0, 0.9));//синяя
  logicAlPlate->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);
  logicAlAnticoincidenceLower->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);

  visAttributes = new G4VisAttributes(G4Colour(0.0,1.0,1.0));
  logicTYVECPlate->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);
  logicTYVECAnticoincidenceLower->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);

  visAttributes = new G4VisAttributes(G4Colour(0.0,1.0,0.0));//зеленый=зеленое покрытие
  flogicAcrylicFiber->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);

return  physWorld;
}

void DetectorConstruction :: ConstructSDandField()
{
    SensitiveDetector *sensDetector = new SensitiveDetector("SensitiveDetector");
    flogicScintillatorFiber ->SetSensitiveDetector(sensDetector);
    flogicScintillatorPlate04->SetSensitiveDetector(sensDetector);
    flogicScintillatorPlate02->SetSensitiveDetector(sensDetector);
    flogicScintillatorAnticoincidenceUpper->SetSensitiveDetector(sensDetector);
    flogicScintillatorAnticoincidenceLower->SetSensitiveDetector(sensDetector);
    flogicScintillatorPlate05->SetSensitiveDetector(sensDetector);

}
