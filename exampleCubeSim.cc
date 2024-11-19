#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

int main(int argc, char** argv) {
    // Run manager
    G4RunManager* runManager = new G4RunManager();

    // Mandatory initialization classes
    DetectorConstruction* detector = new DetectorConstruction();
    runManager->SetUserInitialization(detector);

    auto physicsList = new FTFP_BERT;
    physicsList->RegisterPhysics(new G4StepLimiterPhysics());
    runManager->SetUserInitialization(physicsList);

    // User actions
    PrimaryGeneratorAction* primaryGenAction = new PrimaryGeneratorAction();
    runManager->SetUserAction(primaryGenAction);

    RunAction* runAction = new RunAction();
    runManager->SetUserAction(runAction);

    EventAction* eventAction = new EventAction();
    runManager->SetUserAction(eventAction);

    // Initialize SteppingAction with the necessary arguments
    SteppingAction* steppingAction = new SteppingAction(detector, eventAction);
    runManager->SetUserAction(steppingAction);

    // Visualization manager
    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    // User interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // Start interactive or batch mode
    if (argc == 1) {
        // Interactive mode
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    } else {
        // Batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    // Cleanup
    delete visManager;
    delete runManager;

    return 0;
}

