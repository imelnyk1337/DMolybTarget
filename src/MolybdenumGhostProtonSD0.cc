#include "MolybdenumGhostProtonSD0.hh"
#include "MolybdenumRun.hh"

MolybdenumGhostProtonSD0::MolybdenumGhostProtonSD0(const std::string& detector_name) :
    G4VSensitiveDetector(detector_name) {
    detector_name_ = detector_name;
}

MolybdenumGhostProtonSD0::~MolybdenumGhostProtonSD0() = default;

G4bool MolybdenumGhostProtonSD0::ProcessHits(G4Step* step, G4TouchableHistory*) {
    const auto* run_manager              = G4RunManager::GetRunManager();
    auto* current_run                    = dynamic_cast<MolybdenumRun*>(run_manager->GetNonConstCurrentRun());
    const G4int run_id                   = run_manager->GetCurrentRun()->GetRunID();
    const G4int event_id                 = run_manager->GetCurrentEvent()->GetEventID();
    const G4ParticleDefinition* particle = step->GetTrack()->GetParticleDefinition();


    auto* analysis_manager = G4AnalysisManager::Instance();
    if (particle == G4Proton::ProtonDefinition()) {
        if (step->GetPostStepPoint()->GetStepStatus() == fGeomBoundary) {
            const G4StepPoint* post_step_point     = step->GetPostStepPoint();
            const G4double kinetic_energy          = post_step_point->GetKineticEnergy();
            const G4ThreeVector momentum           = post_step_point->GetMomentum();
            const G4ThreeVector momentum_direction = post_step_point->GetMomentumDirection();
            const G4ThreeVector position           = post_step_point->GetPosition();
            analysis_manager->FillNtupleIColumn(4, 0, run_id);
            analysis_manager->FillNtupleIColumn(4, 1, event_id);
            analysis_manager->FillNtupleDColumn(4, 2, kinetic_energy);

            analysis_manager->AddNtupleRow(4);

            // G4cout << "Proton (trackID: " << step->GetTrack()->GetTrackID() << ") with K.E. : " << kinetic_energy
            //        << G4endl;
            current_run->CountProtonsReachedTarget();
        }
    }
    return true;
}
