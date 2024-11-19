#ifndef RunData_h
#define RunData_h 1

#include "G4Run.hh"
#include "globals.hh"
#include <vector>



/// This class defines data members to hold the energy deposit and track lengths
/// for the cubes in the simulation.

class RunData : public G4Run
{
public:
  RunData() = default;
  ~RunData() override = default;

  // Method to add energy and track length data for a specific cube
  void Add(G4int id, G4double de, G4double dl);

  // Method to fill event data (used by EventAction)
  void FillPerEvent();

  // Method to reset the accumulated data for a new run
  void Reset();

  // Getter methods to retrieve data for a specific cube
  G4double GetTotalEdep() const;
  G4double GetTotalTrackLength() const;

private:
  // Energy deposition (fEdep) and track length (fTrackLength) for each cube
  std::vector<G4double> fEdep;          // Energy deposited per cube
  std::vector<G4double> fTrackLength;   // Track length per cube
};

#endif 

