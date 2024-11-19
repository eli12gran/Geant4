#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

// Calls all classes necessary for the Intialization

class RunAction;
class EventAction;
class PrimaryGeneratorAction;

class ActionInitialization : public G4VUserActionInitialization {
public:
  ActionInitialization();
  ~ActionInitialization() override;

  void BuildForMaster() const override;
  void Build();  

private:
  RunAction* fRunAction;
  EventAction* fEventAction;
  PrimaryGeneratorAction* fPrimaryGeneratorAction;
};

#endif 

