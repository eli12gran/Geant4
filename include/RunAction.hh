#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class RunData; 

class RunAction : public G4UserRunAction {
public:
    RunAction();
    virtual ~RunAction();

    G4Run* GenerateRun() override;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;
};

#endif

