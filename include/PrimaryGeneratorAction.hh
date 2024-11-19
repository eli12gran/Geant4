#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

// Forward declaration of G4ParticleGun class
class G4ParticleGun;


// This class defines the primary particle source for the simulation.
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    // Constructor and Destructor
    // The constructor initializes the particle gun, while the destructor ensures proper cleanup.
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();

    // GeneratePrimaries method
    // This method generates the primary particles for each event.
    virtual void GeneratePrimaries(G4Event* anEvent);

private:
    // Pointer to the particle gun used for generating particles
    G4ParticleGun* fParticleGun;
};

#endif

