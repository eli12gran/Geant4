#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4LogicalVolume.hh"

class DetectorConstruction;  // Forward declaration of DetectorConstruction class
class EventAction;  // Forward declaration of EventAction class

class SteppingAction : public G4UserSteppingAction {
public:
    // Constructor with corrected argument types based on your DetectorConstruction class
    SteppingAction(const DetectorConstruction* detConstruction, EventAction* eventAction);
    ~SteppingAction() override;

    // Override method to process each step
    void UserSteppingAction(const G4Step* step) override;

private:
    const DetectorConstruction* fDetConstruction;  // Pointer to DetectorConstruction
    EventAction* fEventAction;  // Pointer to EventAction
    G4LogicalVolume* fSmallCubeVolume;  // Pointer to the small cube logical volume
};

#endif

