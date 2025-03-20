#include "MolybdenumTrackingAction.hh"

#include <G4TrackingManager.hh>

MolybdenumTrackingAction::MolybdenumTrackingAction(MolybdenumEventAction* event_action) {
    event_action_ = event_action;
}
MolybdenumTrackingAction::~MolybdenumTrackingAction() = default;

void MolybdenumTrackingAction::PreUserTrackingAction(const G4Track* track) {}

void MolybdenumTrackingAction::PostUserTrackingAction(const G4Track* track) {}
