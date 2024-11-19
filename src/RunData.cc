#include "RunData.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"


void RunData::Add(G4int id, G4double de, G4double dl) {
  if (id < fEdep.size()) {
    fEdep[id] += de;
    fTrackLength[id] += dl;
  }
}


void RunData::FillPerEvent()
{
  // Access the analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Record energy deposition and track length for each cube
  for (size_t i = 0; i < fEdep.size(); ++i) {
    analysisManager->FillH1(i, fEdep[i]);
    analysisManager->FillNtupleDColumn(i, fEdep[i]);
  }

  for (size_t i = 0; i < fTrackLength.size(); ++i) {
    analysisManager->FillH1(fEdep.size() + i, fTrackLength[i]);
    analysisManager->FillNtupleDColumn(fEdep.size() + i, fTrackLength[i]);
  }

  // Finalize the event data
  analysisManager->AddNtupleRow();
}

// Method to reset energy deposition and track length for each cube
void RunData::Reset()
{
  std::fill(fEdep.begin(), fEdep.end(), 0.);
  std::fill(fTrackLength.begin(), fTrackLength.end(), 0.);
}

// Get total energy deposition across all cubes
G4double RunData::GetTotalEdep() const {
  G4double totalEdep = 0.;
  for (auto edep : fEdep) {
    totalEdep += edep;
  }
  return totalEdep;
}

// Get total track length across all cubes
G4double RunData::GetTotalTrackLength() const {
  G4double totalTrackLength = 0.;
  for (auto trackLength : fTrackLength) {
    totalTrackLength += trackLength;
  }
  return totalTrackLength;
}

