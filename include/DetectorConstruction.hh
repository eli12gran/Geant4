#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH


// Import all we need in here

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "G4MagneticField.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4VSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "globals.hh"
#include "G4THitsCollection.hh"
#include "G4UniformMagField.hh"


// Calls the fucntions we´re using in the .cc file
class DetectorConstruction : public G4VUserDetectorConstruction {
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct() override;
    virtual void ConstructSDandField() override;

    G4LogicalVolume* GetSmallCubeVolume() const;
    static G4LogicalVolume* GetLogicSmallCube();  

private:
    static G4LogicalVolume* logicSmallCube;
    static G4MagneticField* fMagField;
    static G4GlobalMagFieldMessenger* fMagFieldMessenger;
};

#endif

