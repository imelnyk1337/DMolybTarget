#include "MolybdenumEventAction.hh"

#include <G4Event.hh>

MolybdenumEventAction::MolybdenumEventAction(MolybdenumRunAction* run_action) : run_action_(run_action) {
    G4AnalysisManager* analysis_manager = G4AnalysisManager::Instance();
}

MolybdenumEventAction::~MolybdenumEventAction() = default;

void MolybdenumEventAction::EndOfEventAction(const G4Event* event) {
    // G4AnalysisManager* analysis_manager = G4AnalysisManager::Instance();
    // const G4int event_id                = event->GetEventID();
    // analysis_manager->FillNtupleIColumn(0, 1, event_id);
    // analysis_manager->FillNtupleIColumn(1, 0, event_id);
}
