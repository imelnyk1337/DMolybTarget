#include "MolybdenumVacuumWindowSD.hh"

MolybdenumVacuumWindowSD::MolybdenumVacuumWindowSD(const std::string& detector_name) :
    G4VSensitiveDetector(detector_name) {
    detector_name_  = detector_name;
    temp_track1_id_ = -1;
    temp_track2_id_ = -1;
}

MolybdenumVacuumWindowSD::~MolybdenumVacuumWindowSD() = default;

G4bool MolybdenumVacuumWindowSD::ProcessHits(G4Step* step, G4TouchableHistory* history) {
    auto* analysis_manager  = G4AnalysisManager::Instance();
    const auto* run_manager = G4RunManager::GetRunManager();
    const G4Track* track    = step->GetTrack();
    const G4int track_id    = track->GetTrackID();
    const auto* particle    = track->GetParticleDefinition();

    if (particle == G4Proton::ProtonDefinition()) {

        // Proton just reached the vacuum window
        // if the current track id is not equal to the previously recorded - we haven't processed that track before
        if (step->GetPreStepPoint()->GetStepStatus() == fGeomBoundary && track_id != temp_track1_id_) {
            // G4cout << track->GetCreatorModelName() << G4endl; // also Undefined for all the protons

            const G4int run_id = run_manager->GetCurrentRun()->GetRunID();
            analysis_manager->FillNtupleIColumn(7, 0, run_id);

            const G4int event_id = run_manager->GetCurrentEvent()->GetEventID();
            analysis_manager->FillNtupleIColumn(7, 1, event_id);

            const G4StepPoint* pre_step_point   = step->GetPreStepPoint();
            const G4double kinetic_energy_presp = pre_step_point->GetKineticEnergy();

            analysis_manager->FillNtupleDColumn(7, 2, kinetic_energy_presp);

            analysis_manager->AddNtupleRow(7);

            temp_track1_id_ = track_id;
        }

        // Protons leaving the vacuum window
        if (step->GetPostStepPoint()->GetStepStatus() == fGeomBoundary && track_id != temp_track2_id_) {

            const G4int run_id = run_manager->GetCurrentRun()->GetRunID();
            analysis_manager->FillNtupleIColumn(8, 0, run_id);

            const G4int event_id = run_manager->GetCurrentEvent()->GetEventID();
            analysis_manager->FillNtupleIColumn(8, 1, event_id);
            const G4StepPoint* post_step_point = step->GetPostStepPoint();

            const G4double kinetic_energy_postsp = post_step_point->GetKineticEnergy();
            analysis_manager->FillNtupleDColumn(8, 2, kinetic_energy_postsp);

            analysis_manager->AddNtupleRow(8);

            temp_track2_id_ = track_id;
        }
    }
    return true;
}
