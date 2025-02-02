#include "MolybdenumTargetTabletSD.hh"


MolybdenumTargetTabletSD::MolybdenumTargetTabletSD(const std::string& detector_name) :
    G4VSensitiveDetector(detector_name) {
    detector_name_ = detector_name;
}

MolybdenumTargetTabletSD::~MolybdenumTargetTabletSD() = default;

G4bool MolybdenumTargetTabletSD::ProcessHits(G4Step* step, G4TouchableHistory* history) {
    const auto* run_manager = G4RunManager::GetRunManager();
    auto* analysis_manager  = G4AnalysisManager::Instance();

    if (const G4ParticleDefinition* particle = step->GetTrack()->GetParticleDefinition();
        particle == G4Proton::ProtonDefinition()) {

        if (const G4StepPoint* pre_step_point = step->GetPreStepPoint();
            pre_step_point->GetStepStatus() == fGeomBoundary) {
            const G4int run_id = run_manager->GetCurrentRun()->GetRunID();
            analysis_manager->FillNtupleIColumn(5, 0, run_id);

            const G4int event_id = run_manager->GetCurrentEvent()->GetEventID();
            analysis_manager->FillNtupleIColumn(5, 1, event_id);

            const G4double kinetic_energy = pre_step_point->GetKineticEnergy();
            analysis_manager->FillNtupleDColumn(5, 2, kinetic_energy);


            const G4ThreeVector& momentum = pre_step_point->GetMomentum();
            analysis_manager->FillNtupleDColumn(5, 3, momentum.x());
            analysis_manager->FillNtupleDColumn(5, 4, momentum.y());
            analysis_manager->FillNtupleDColumn(5, 5, momentum.z());

            const G4ThreeVector& momentum_direction = pre_step_point->GetMomentumDirection();
            analysis_manager->FillNtupleDColumn(5, 6, momentum_direction.x());
            analysis_manager->FillNtupleDColumn(5, 7, momentum_direction.y());
            analysis_manager->FillNtupleDColumn(5, 8, momentum_direction.z());

            const G4ThreeVector& position = pre_step_point->GetPosition();
            analysis_manager->FillNtupleDColumn(5, 9, position.x());
            analysis_manager->FillNtupleDColumn(5, 10, position.y());
            analysis_manager->FillNtupleDColumn(5, 11, position.z());

            analysis_manager->AddNtupleRow(5);
        }
    }
    return true;
}
