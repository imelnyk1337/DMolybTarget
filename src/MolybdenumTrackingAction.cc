#include "MolybdenumTrackingAction.hh"

#include <G4TrackingManager.hh>

MolybdenumTrackingAction::MolybdenumTrackingAction(MolybdenumEventAction* event_action) {
    event_action_ = event_action;
}
MolybdenumTrackingAction::~MolybdenumTrackingAction() {}

void MolybdenumTrackingAction::PreUserTrackingAction(const G4Track* track) {
    event_action_->AddTrackPDGtoMap(track);
    event_action_->AddTrackNameToMap(track);
}

void MolybdenumTrackingAction::PostUserTrackingAction(const G4Track* track) {
    const G4int parent_id = track->GetParentID();

    if (track->GetParticleDefinition() == G4Neutron::NeutronDefinition()) {

        if (parent_id != 0) {
            G4cout << "Track " << track->GetTrackID() << " (" << track->GetParticleDefinition()->GetParticleName()
                   << ")" << " was created by " << event_action_->GetTrackPDGfromMap(parent_id) << " ("
                   << event_action_->GetTrackNameFromMap(parent_id) << ")" << G4endl;
        }
        else {
            G4cout << "Track " << track->GetTrackID() << " (" << track->GetParticleDefinition()->GetParticleName()
                   << " is primary and has no parent" << G4endl;
        }
    }
}
