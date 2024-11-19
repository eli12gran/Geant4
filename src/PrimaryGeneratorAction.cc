#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4RandomTools.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "Randomize.hh"

// Constructor
// Initializes the particle gun and sets the default particle to a muon with a predefined energy and direction.
PrimaryGeneratorAction::PrimaryGeneratorAction() {
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    // Set default particle to muon
    auto particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("mu-");
    fParticleGun->SetParticleDefinition(particleDefinition);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleEnergy(300. * MeV);
}

// Destructor
// Cleans up the particle gun when the `PrimaryGeneratorAction` object is destroyed.
PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}

// GeneratePrimaries
// Generates the primary particles for an event. Determines the size of the world volume and sets the initial position
// of the particles. If the world volume is not found or is not of box shape, an exception is logged.
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    G4double worldZHalfLength = 0.;
    auto worldLV = G4LogicalVolumeStore::GetInstance()->GetVolume("World");

    G4Box* worldBox = nullptr;
    if (worldLV) {
        // Attempt to retrieve the world box dimensions
        worldBox = dynamic_cast<G4Box*>(worldLV->GetSolid());
    }

    if (worldBox) {
        // Get the Z half-length of the world box
        worldZHalfLength = worldBox->GetZHalfLength();
    } else {
        // Log a warning if the world volume is not found or has an unexpected shape
        G4ExceptionDescription msg;
        msg << "World volume of box shape not found." << G4endl;
        msg << "Perhaps you have changed geometry." << G4endl;
        G4Exception("PrimaryGeneratorAction::GeneratePrimaries()",
                    "MyCode0002", JustWarning, msg);
    }

    // Set the initial position of the particle gun
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -10. * m));

    // Generate the primary vertex for the event
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

