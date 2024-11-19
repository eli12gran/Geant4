#include "RunAction.hh"
#include "RunData.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction()
{
    // Set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(1);

    // Create analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetNtupleMerging(true);

    // Book histograms
    analysisManager->CreateH1("ELargeCube", "Edep in LargeCube", 100, 0., 100*MeV);
    analysisManager->CreateH1("ESmallCube", "Edep in SmallCube", 100, 0., 10*MeV);
    analysisManager->CreateH1("LLargeCube", "Track Length in LargeCube", 100, 0., 50*cm);
    analysisManager->CreateH1("LSmallCube", "Track Length in SmallCube", 100, 0., 5*cm);

    // Creating ntuple for energy deposition and track length data
    analysisManager->CreateNtuple("SimulationData", "Edep and TrackL");
    analysisManager->CreateNtupleDColumn("ELargeCube");
    analysisManager->CreateNtupleDColumn("ESmallCube");
    analysisManager->CreateNtupleDColumn("LLargeCube");
    analysisManager->CreateNtupleDColumn("LSmallCube");
    analysisManager->FinishNtuple();
}


RunAction::~RunAction()
{
    
    delete G4AnalysisManager::Instance();
}

G4Run* RunAction::GenerateRun()
{
    return new RunData;
}

void RunAction::BeginOfRunAction(const G4Run* run)
{
    G4cout << "### Run " << run->GetRunID() << " start." << G4endl;

    // Get analysis manager and open output file
    auto analysisManager = G4AnalysisManager::Instance();
    G4String fileName = "SimulationOutput.csv";
    analysisManager->OpenFile(fileName);
    G4cout << "Using " << analysisManager->GetType() << G4endl;
}

void RunAction::EndOfRunAction(const G4Run* /*aRun*/)
{
    auto analysisManager = G4AnalysisManager::Instance();
    if (analysisManager->GetH1(1)) {
        G4cout << G4endl << " ----> Histogram statistics " ;
	if(isMaster){
		G4cout << "for the entire run " << G4endl << G4endl;
	}
	else{
		G4cout << "for the local thread " << G4endl << G4endl;
	}

        G4cout << " ELargeCube : mean = "
               << G4BestUnit(analysisManager->GetH1(0)->mean(), "Energy")
               << " rms = "
               << G4BestUnit(analysisManager->GetH1(0)->rms(), "Energy") << G4endl;

        G4cout << " ESmallCube : mean = "
               << G4BestUnit(analysisManager->GetH1(1)->mean(), "Energy")
               << " rms = "
               << G4BestUnit(analysisManager->GetH1(1)->rms(), "Energy") << G4endl;

        G4cout << " LLargeCube : mean = "
               << G4BestUnit(analysisManager->GetH1(2)->mean(), "Length")
               << " rms = "
               << G4BestUnit(analysisManager->GetH1(2)->rms(), "Length") << G4endl;

        G4cout << " LSmallCube : mean = "
               << G4BestUnit(analysisManager->GetH1(3)->mean(), "Length")
               << " rms = "
               << G4BestUnit(analysisManager->GetH1(3)->rms(), "Length") << G4endl;
    }

    
    analysisManager->Write();
    analysisManager->CloseFile();
}

