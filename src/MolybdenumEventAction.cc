#include "MolybdenumEventAction.hh"
#include <G4Event.hh>
#include <G4Track.hh>

MolybdenumEventAction::MolybdenumEventAction(MolybdenumRunAction* run_action) {
    G4AnalysisManager* analysis_manager = G4AnalysisManager::Instance();
}

MolybdenumEventAction::~MolybdenumEventAction() = default;

void MolybdenumEventAction::BeginOfEventAction(const G4Event* event) {
    const G4int event_id = event->GetEventID();
    if (!(event_id % 100'000))
        G4cout << "Event ID: " << event_id << G4endl;
}

void MolybdenumEventAction::EndOfEventAction(const G4Event* event) {}
