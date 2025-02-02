#include "AuxilaryUtilities.hh"

std::vector<G4double> functions::convert_rgba_to_percents(const std::vector<G4double>& rgba) {
    constexpr G4double max = 255.;
    std::vector percents   = {rgba[0] / max, rgba[1] / max, rgba[2] / max, rgba[3]};
    return percents;
}

void functions::fill_ntuple(const G4int n_ntuple, const G4StepPoint* step_point) {
    const auto* run_manager = G4RunManager::GetRunManager();
    auto* analysis_manager  = G4AnalysisManager::Instance();
    const G4int run_id      = run_manager->GetCurrentRun()->GetRunID();
    analysis_manager->FillNtupleIColumn(n_ntuple, 0, run_id);

    const G4int event_id = run_manager->GetCurrentEvent()->GetEventID();
    analysis_manager->FillNtupleIColumn(n_ntuple, 1, event_id);

    const G4double kinetic_energy = step_point->GetKineticEnergy();
    analysis_manager->FillNtupleDColumn(n_ntuple, 2, kinetic_energy);

    const G4ThreeVector& momentum = step_point->GetMomentum();
    analysis_manager->FillNtupleDColumn(n_ntuple, 3, momentum.x());
    analysis_manager->FillNtupleDColumn(n_ntuple, 4, momentum.y());
    analysis_manager->FillNtupleDColumn(n_ntuple, 5, momentum.z());

    const G4ThreeVector& momentum_direction = step_point->GetMomentumDirection();
    analysis_manager->FillNtupleDColumn(n_ntuple, 6, momentum_direction.x());
    analysis_manager->FillNtupleDColumn(n_ntuple, 7, momentum_direction.y());
    analysis_manager->FillNtupleDColumn(n_ntuple, 8, momentum_direction.z());

    const G4ThreeVector& position = step_point->GetPosition();
    analysis_manager->FillNtupleDColumn(n_ntuple, 9, position.x());
    analysis_manager->FillNtupleDColumn(n_ntuple, 10, position.y());
    analysis_manager->FillNtupleDColumn(n_ntuple, 11, position.z());

    analysis_manager->AddNtupleRow(n_ntuple);
}
