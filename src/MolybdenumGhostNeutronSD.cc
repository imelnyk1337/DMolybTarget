#include "MolybdenumGhostNeutronSD.hh"

MolybdenumGhostNeutronSD::MolybdenumGhostNeutronSD(const std::string& detector_name) :
    G4VSensitiveDetector(detector_name) {
    detector_name_ = detector_name;
}

MolybdenumGhostNeutronSD::~MolybdenumGhostNeutronSD() = default;

G4bool MolybdenumGhostNeutronSD::ProcessHits(G4Step* step, G4TouchableHistory* history) {
    const auto* run_manager = G4RunManager::GetRunManager();
    const G4int run_id      = run_manager->GetCurrentRun()->GetRunID();
    const G4int event_id    = run_manager->GetCurrentEvent()->GetEventID();
    // G4cout << " @@@@@@@@@@@@@ @@@@@@@@@@@@@@@@ Particle detected: "
    //        << step->GetTrack()->GetParticleDefinition()->GetParticleName() << G4endl;
    const G4ParticleDefinition* particle   = step->GetTrack()->GetParticleDefinition();
    const G4Track* track                   = step->GetTrack();
    const G4StepPoint* post_step_point     = step->GetPostStepPoint();
    const G4double kinetic_energy          = post_step_point->GetKineticEnergy();
    const G4ThreeVector momentum           = post_step_point->GetMomentum();
    const G4ThreeVector momentum_direction = post_step_point->GetMomentumDirection();
    const G4ThreeVector position           = post_step_point->GetPosition();

    auto* analysis_manager = G4AnalysisManager::Instance();
    if (particle == G4Neutron::NeutronDefinition() && post_step_point->GetStepStatus() == fGeomBoundary) {
        // G4cout << "Neutron detected in ghost volume with kinetic energy: " << kinetic_energy << " MeV" << G4endl;
        analysis_manager->FillNtupleIColumn(1, 0, run_id);
        analysis_manager->FillNtupleIColumn(1, 1, event_id);
        analysis_manager->FillNtupleDColumn(1, 2, kinetic_energy);
        analysis_manager->FillNtupleDColumn(1, 3, position.x());
        analysis_manager->FillNtupleDColumn(1, 4, position.y());
        analysis_manager->FillNtupleDColumn(1, 5, position.z());
        analysis_manager->FillNtupleDColumn(1, 6, momentum.x());
        analysis_manager->FillNtupleDColumn(1, 7, momentum.y());
        analysis_manager->FillNtupleDColumn(1, 8, momentum.z());
        analysis_manager->FillNtupleDColumn(1, 9, momentum_direction.x());
        analysis_manager->FillNtupleDColumn(1, 10, momentum_direction.y());
        analysis_manager->FillNtupleDColumn(1, 11, momentum_direction.z());
        analysis_manager->AddNtupleRow(1);
    }
    else if (particle == G4Gamma::GammaDefinition() && post_step_point->GetStepStatus() == fGeomBoundary) {
        // G4cout << "Gamma detected in ghost volume with kinetic energy: " << kinetic_energy << " MeV" << G4endl;
        // G4cout << "Gamma creator model: " << track->GetCreatorModelName() << "; " << G4endl; //
        // model_G4ParticleHPNXInelasticFS_F02 G4cout << "Gamma creator process: " <<
        // track->GetCreatorProcess()->GetProcessName() << "; " << G4endl; // protonInelastic
        analysis_manager->FillNtupleIColumn(2, 0, run_id);
        analysis_manager->FillNtupleIColumn(2, 1, event_id);
        analysis_manager->FillNtupleDColumn(2, 2, kinetic_energy);
        analysis_manager->FillNtupleDColumn(2, 3, position.x());
        analysis_manager->FillNtupleDColumn(2, 4, position.y());
        analysis_manager->FillNtupleDColumn(2, 5, position.z());
        analysis_manager->FillNtupleDColumn(2, 6, momentum.x());
        analysis_manager->FillNtupleDColumn(2, 7, momentum.y());
        analysis_manager->FillNtupleDColumn(2, 8, momentum.z());
        analysis_manager->FillNtupleDColumn(2, 9, momentum_direction.x());
        analysis_manager->FillNtupleDColumn(2, 10, momentum_direction.y());
        analysis_manager->FillNtupleDColumn(2, 11, momentum_direction.z());
        analysis_manager->AddNtupleRow(2);
    }
    return true;
}
