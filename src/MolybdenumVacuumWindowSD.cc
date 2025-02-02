#include "MolybdenumVacuumWindowSD.hh"

MolybdenumVacuumWindowSD::MolybdenumVacuumWindowSD(const std::string& detector_name) :
    G4VSensitiveDetector(detector_name) {
    detector_name_ = detector_name;
}

MolybdenumVacuumWindowSD::~MolybdenumVacuumWindowSD() = default;

G4bool MolybdenumVacuumWindowSD::ProcessHits(G4Step* step, G4TouchableHistory* history) {
    auto* analysis_manager  = G4AnalysisManager::Instance();
    const auto* run_manager = G4RunManager::GetRunManager();
    const G4Track* track    = step->GetTrack();
    if (const auto* particle = track->GetParticleDefinition(); particle == G4Proton::ProtonDefinition()) {
        // Proton just reached the vacuum window
        if (step->GetPreStepPoint()->GetStepStatus() == fGeomBoundary) {
            // G4cout << track->GetCreatorModelName() << G4endl; // also Undefined for all the protons

            const G4int run_id = run_manager->GetCurrentRun()->GetRunID();
            analysis_manager->FillNtupleIColumn(3, 0, run_id);

            const G4int event_id = run_manager->GetCurrentEvent()->GetEventID();
            analysis_manager->FillNtupleIColumn(3, 1, event_id);

            const G4StepPoint* pre_step_point   = step->GetPreStepPoint();
            const G4double kinetic_energy_presp = pre_step_point->GetKineticEnergy();

            analysis_manager->FillNtupleDColumn(3, 2, kinetic_energy_presp);

            const G4ThreeVector& momentum_presp = pre_step_point->GetMomentum();
            analysis_manager->FillNtupleDColumn(3, 3, momentum_presp.x());
            analysis_manager->FillNtupleDColumn(3, 4, momentum_presp.y());
            analysis_manager->FillNtupleDColumn(3, 5, momentum_presp.z());

            const G4ThreeVector& momentum_direction_presp = pre_step_point->GetMomentumDirection();
            analysis_manager->FillNtupleDColumn(3, 6, momentum_direction_presp.x());
            analysis_manager->FillNtupleDColumn(3, 7, momentum_direction_presp.y());
            analysis_manager->FillNtupleDColumn(3, 8, momentum_direction_presp.z());

            const G4ThreeVector& position_presp = pre_step_point->GetPosition();
            analysis_manager->FillNtupleDColumn(3, 9, position_presp.x());
            analysis_manager->FillNtupleDColumn(3, 10, position_presp.y());
            analysis_manager->FillNtupleDColumn(3, 11, position_presp.z());

            analysis_manager->AddNtupleRow(3);
        }

        // Protons leaving the vacuum window
        if (step->GetPostStepPoint()->GetStepStatus() == fGeomBoundary) {

            const G4int run_id = run_manager->GetCurrentRun()->GetRunID();
            analysis_manager->FillNtupleIColumn(11, 0, run_id);

            const G4int event_id = run_manager->GetCurrentEvent()->GetEventID();
            analysis_manager->FillNtupleIColumn(11, 1, event_id);
            const G4StepPoint* post_step_point = step->GetPostStepPoint();

            const G4double kinetic_energy_postsp = post_step_point->GetKineticEnergy();
            analysis_manager->FillNtupleDColumn(11, 2, kinetic_energy_postsp);

            const G4ThreeVector& momentum_postsp = post_step_point->GetMomentum();
            analysis_manager->FillNtupleDColumn(11, 3, momentum_postsp.x());
            analysis_manager->FillNtupleDColumn(11, 4, momentum_postsp.y());
            analysis_manager->FillNtupleDColumn(11, 5, momentum_postsp.z());

            const G4ThreeVector& momentum_direction_postsp = post_step_point->GetMomentumDirection();
            analysis_manager->FillNtupleDColumn(11, 6, momentum_direction_postsp.x());
            analysis_manager->FillNtupleDColumn(11, 7, momentum_direction_postsp.y());
            analysis_manager->FillNtupleDColumn(11, 8, momentum_direction_postsp.z());

            const G4ThreeVector& position_postsp = post_step_point->GetPosition();
            analysis_manager->FillNtupleDColumn(11, 9, position_postsp.x());
            analysis_manager->FillNtupleDColumn(11, 10, position_postsp.y());
            analysis_manager->FillNtupleDColumn(11, 11, position_postsp.z());

            analysis_manager->AddNtupleRow(11);
        }
    }

    if (const auto* particle = track->GetParticleDefinition(); particle == G4Neutron::NeutronDefinition()) {
        // G4cout << "Neutron with energy of " << track->GetKineticEnergy()
        //        << " MeV is found; parent is: " << track->GetParentID() << G4endl;
        // G4cout << "    $ Creator process: " << track->GetCreatorProcess()->GetProcessName() << "; " << G4endl;
        // G4cout << "    $ Creator model: " << track->GetCreatorModelName() << "; " << G4endl;
    }


    return true;
}
