#include "ActionInitialization.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"

// The ActionInitialization class is responsible for defining the user actions 
// (e.g., RunAction, EventAction, PrimaryGeneratorAction) used during the Geant4 simulation. 
// These actions are the building blocks of the simulation, defining what happens at different 
// levels: run, event, and primary particle generation.

ActionInitialization::ActionInitialization()
: G4VUserActionInitialization(),
  fRunAction(nullptr),  // Initialize pointer to RunAction as nullptr
  fEventAction(nullptr), // Initialize pointer to EventAction as nullptr
  fPrimaryGeneratorAction(nullptr) // Initialize pointer to PrimaryGeneratorAction as nullptr
{ }

// Destructor for the ActionInitialization class
ActionInitialization::~ActionInitialization() {}

// This method is called when the master thread is initialized in a multi-threaded simulation.
// It defines actions to be used by the master thread (e.g., collecting and merging data 
// from worker threads).
void ActionInitialization::BuildForMaster() const {
  // Assign RunAction to the master thread
  SetUserAction(new RunAction);
}

// This method is called for each worker thread and for sequential runs.
// It sets up the user-defined actions for primary generation, run management, and event management.
void ActionInitialization::Build() {
  
  // Instantiate and initialize the primary generator action
  fPrimaryGeneratorAction = new PrimaryGeneratorAction;

  // Instantiate and initialize the run action
  fRunAction = new RunAction;

  // Instantiate and initialize the event action
  fEventAction = new EventAction;

  // Register the primary generator action with the simulation
  SetUserAction(fPrimaryGeneratorAction);

  // Register the run action with the simulation
  SetUserAction(fRunAction);

  // Register the event action with the simulation
  SetUserAction(fEventAction);
}

