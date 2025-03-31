#include "MolybdenumTargetTabletSD.hh"


MolybdenumTargetTabletSD::MolybdenumTargetTabletSD(const std::string& detector_name) :
    G4VSensitiveDetector(detector_name) {
    detector_name_ = detector_name;
}

MolybdenumTargetTabletSD::~MolybdenumTargetTabletSD() = default;

G4bool MolybdenumTargetTabletSD::ProcessHits(G4Step* step, G4TouchableHistory* history) {
    auto* analysis_manager   = G4AnalysisManager::Instance();
    const auto* run_manager  = G4RunManager::GetRunManager();
    const G4Track* track     = step->GetTrack();
    const auto particle_name = track->GetDefinition()->GetParticleName();

    if (particle_name == "proton") {

        if (const G4StepPoint* pre_step_point = step->GetPreStepPoint();
            pre_step_point->GetStepStatus() == fGeomBoundary) {
            const G4int run_id = run_manager->GetCurrentRun()->GetRunID();
            analysis_manager->FillNtupleIColumn(6, 0, run_id);

            const G4int event_id = run_manager->GetCurrentEvent()->GetEventID();
            analysis_manager->FillNtupleIColumn(6, 1, event_id);

            const G4double kinetic_energy = pre_step_point->GetKineticEnergy();
            analysis_manager->FillNtupleDColumn(6, 2, kinetic_energy);

            analysis_manager->AddNtupleRow(6);


            // G4cout << "Proton with K.E.: " << track->GetKineticEnergy() << G4endl;
        }
    }
    return true;
}
