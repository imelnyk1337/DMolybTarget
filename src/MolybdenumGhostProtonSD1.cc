#include "MolybdenumGhostProtonSD1.hh"

MolybdenumGhostProtonSD1::MolybdenumGhostProtonSD1(const std::string& detector_name) :
    G4VSensitiveDetector(detector_name) {
    detector_name_ = detector_name;
}

MolybdenumGhostProtonSD1::~MolybdenumGhostProtonSD1() = default;

G4bool MolybdenumGhostProtonSD1::ProcessHits(G4Step* step, G4TouchableHistory*) {
    const auto* run_manager              = G4RunManager::GetRunManager();
    const G4int run_id                   = run_manager->GetCurrentRun()->GetRunID();
    const G4int event_id                 = run_manager->GetCurrentEvent()->GetEventID();
    const G4ParticleDefinition* particle = step->GetTrack()->GetParticleDefinition();

    auto* analysis_manager = G4AnalysisManager::Instance();
    if (particle == G4Proton::ProtonDefinition()) {
        if (const G4StepPoint* post_step_point = step->GetPostStepPoint();
            post_step_point->GetStepStatus() == fGeomBoundary) {
            const G4double kinetic_energy          = post_step_point->GetKineticEnergy();
            const G4ThreeVector momentum           = post_step_point->GetMomentum();
            const G4ThreeVector momentum_direction = post_step_point->GetMomentumDirection();
            const G4ThreeVector position           = post_step_point->GetPosition();
            analysis_manager->FillNtupleIColumn(5, 0, run_id);
            analysis_manager->FillNtupleIColumn(5, 1, event_id);
            analysis_manager->FillNtupleDColumn(5, 2, kinetic_energy);
            // analysis_manager->FillNtupleDColumn(10, 3, momentum.x());
            // analysis_manager->FillNtupleDColumn(10, 4, momentum.y());
            // analysis_manager->FillNtupleDColumn(10, 5, momentum.z());
            // analysis_manager->FillNtupleDColumn(10, 6, momentum_direction.x());
            // analysis_manager->FillNtupleDColumn(10, 7, momentum_direction.y());
            // analysis_manager->FillNtupleDColumn(10, 8, momentum_direction.z());
            // analysis_manager->FillNtupleDColumn(10, 9, position.x());
            // analysis_manager->FillNtupleDColumn(10, 10, position.y());
            // analysis_manager->FillNtupleDColumn(10, 11, position.z());
            analysis_manager->AddNtupleRow(5);
        }
    }
    return true;
}
