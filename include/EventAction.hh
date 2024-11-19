// In EventAction.hh
#ifndef EventAction_h
#define EventAction_h
#include "RunData.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"

class RunData;  // Forward declaration of RunData class

class EventAction : public G4UserEventAction {
public:
    EventAction();
    ~EventAction() override;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;

   void Add(G4String const& name, double energy, double trackLength);
private:
    void PrintEventStatistics(G4double totalEdep, G4double totalTrackLength) const;
};

#endif

