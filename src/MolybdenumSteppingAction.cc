#include "MolybdenumSteppingAction.hh"

MolybdenumSteppingAction::MolybdenumSteppingAction(MolybdenumEventAction* event_action) {
    event_action_ = event_action;
}

MolybdenumSteppingAction::~MolybdenumSteppingAction() = default;

void MolybdenumSteppingAction::UserSteppingAction(const G4Step* step) {
    const G4Track* track = step->GetTrack();

    // Check if the track is a nucleus
    if (track->GetParticleDefinition()->GetParticleType() == "nucleus" && track->GetCurrentStepNumber() == 1) {
        const G4int Z = track->GetParticleDefinition()->GetAtomicNumber();
        const G4int A = track->GetParticleDefinition()->GetAtomicMass();

        G4cout << "New isotope produced: " << Z << " " << A << G4endl;

        const G4double production_time = track->GetGlobalTime();
        event_action_->RegisterIsotope(Z, A, production_time);
    }
}
