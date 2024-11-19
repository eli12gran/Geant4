#include "DetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

// Static member definitions
// These static members are shared across all instances of the DetectorConstruction class.
// `logicSmallCube` holds the logical volume for the small cube,
// while `fMagField` and `fMagFieldMessenger` manage the global magnetic field setup.
G4LogicalVolume* DetectorConstruction::logicSmallCube = nullptr;
G4MagneticField* DetectorConstruction::fMagField = nullptr;
G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = nullptr;

// Constructor
// Initializes the DetectorConstruction object.
DetectorConstruction::DetectorConstruction() {
    // Constructor code (if any)
}

// Getter for logicSmallCube
// Provides access to the logical volume of the small cube.
G4LogicalVolume* DetectorConstruction::GetLogicSmallCube() {
    return logicSmallCube;
}

// Destructor
// Cleans up allocated resources for magnetic field management.
DetectorConstruction::~DetectorConstruction() {
    delete fMagFieldMessenger;
    delete fMagField;
}

// Construct method
// Defines the physical and logical volumes of the detector.
// - Creates the world volume as a large box filled with vacuum.
// - Adds a larger cube at the center of the world.
// - Populates the larger cube with a 5x5x5 grid of smaller cubes.
G4VPhysicalVolume* DetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();
    
    // Define world volume
    G4double worldSize = 1.0 * km;
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_Galactic");
    G4Box* solidWorld = new G4Box("World", worldSize / 2, worldSize / 2, worldSize / 2);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, true);

    // Define large cube
    G4double largeCubeSize = 0.5 * m;
    G4Box* solidLargeCube = new G4Box("LargeCube", largeCubeSize / 2, largeCubeSize / 2, largeCubeSize / 2);
    G4Material* largeCubeMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    G4LogicalVolume* logicLargeCube = new G4LogicalVolume(solidLargeCube, largeCubeMat, "LargeCube");
    new G4PVPlacement(0, G4ThreeVector(), logicLargeCube, "LargeCube", logicWorld, false, 0, true);

    // Define small cubes and arrange them in a grid within the large cube
    G4double smallCubeSize = 0.1 * m;
    G4Box* solidSmallCube = new G4Box("SmallCube", smallCubeSize / 2, smallCubeSize / 2, smallCubeSize / 2);
    G4Material* smallCubeMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    logicSmallCube = new G4LogicalVolume(solidSmallCube, smallCubeMat, "SmallCube");

    for (G4int x = 0; x < 5; ++x) {
        for (G4int y = 0; y < 5; ++y) {
            for (G4int z = 0; z < 5; ++z) {
                G4double posX = (x - 2) * smallCubeSize;
                G4double posY = (y - 2) * smallCubeSize;
                G4double posZ = (z - 2) * smallCubeSize;
                new G4PVPlacement(0, G4ThreeVector(posX, posY, posZ), logicSmallCube, "SmallCube", logicLargeCube, false, 0, true);
            }
        }
    }

    return physWorld;
}

// Magnetic field construction
// Defines the global magnetic field for the simulation.
// Creates a magnetic field messenger to manage the field and registers it for automatic deletion.
void DetectorConstruction::ConstructSDandField() {
    G4ThreeVector fieldValue;  // Magnetic field vector (zero by default)
    fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
    fMagFieldMessenger->SetVerboseLevel(1);

    // Register the field messenger for cleanup when the simulation ends
    G4AutoDelete::Register(fMagFieldMessenger);
}

