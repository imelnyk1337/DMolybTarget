#include "MolybdenumEventAction.hh"
#include <G4Event.hh>
#include <G4Track.hh>

MolybdenumEventAction::MolybdenumEventAction(MolybdenumRunAction* run_action) {
    G4AnalysisManager* analysis_manager = G4AnalysisManager::Instance();
}

MolybdenumEventAction::~MolybdenumEventAction() = default;

void MolybdenumEventAction::BeginOfEventAction(const G4Event* event) {}

void MolybdenumEventAction::EndOfEventAction(const G4Event* event) {}
