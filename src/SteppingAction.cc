#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "G4Step.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

// Constructor
// Associates the `DetectorConstruction` and `EventAction` objects with the stepping action.
SteppingAction::SteppingAction(const DetectorConstruction* detConstruction, EventAction* eventAction)
    : G4UserSteppingAction(), fDetConstruction(detConstruction), fEventAction(eventAction) {}

// Destructor
// No specific cleanup is required since no dynamic memory is allocated.
SteppingAction::~SteppingAction() {}

// UserSteppingAction
// This method is called for each step of a particle in the simulation.
// It determines whether the step occurred in the `SmallCube` logical volume and, if so, accumulates the energy deposition and step length.
void SteppingAction::UserSteppingAction(const G4Step* step) {
    // Get the logical volume of the current step
    G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

    // Check if the step occurs in the `SmallCube` logical volume
    if (volume == DetectorConstruction::GetLogicSmallCube()) {
        // Get the total energy deposited in this step
        G4double edep = step->GetTotalEnergyDeposit();

        // Calculate the step length for charged particles only
        G4double stepLength = 0.0;
        if (step->GetTrack()->GetDefinition()->GetPDGCharge() != 0) {
            stepLength = step->GetStepLength();
        }

        // Add the energy deposition and step length to the event action
        fEventAction->Add("SmallCube", edep, stepLength);
    }
}

