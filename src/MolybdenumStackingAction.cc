#include "MolybdenumStackingAction.hh"
#include "MolybdenumGeometryConstruction.hh"

MolybdenumStackingAction::MolybdenumStackingAction()  = default;
MolybdenumStackingAction::~MolybdenumStackingAction() = default;

G4ClassificationOfNewTrack MolybdenumStackingAction::ClassifyNewTrack(const G4Track* track) {
    // check if the track is a neutron
    if (track->GetDefinition() == G4Neutron::NeutronDefinition()) {
        const auto* detector_construction = dynamic_cast<const MolybdenumGeometryConstruction*>(
            G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        if (const G4LogicalVolume* logical_molybdenum_tablet = detector_construction->GetMolybdenumLogicalVolume();
            track->GetVolume()->GetLogicalVolume() == logical_molybdenum_tablet) {
            // G4cout << "%%%%%%% Neutron creator model: " << track->GetCreatorModelName() << "; " << G4endl;
            // G4cout << "&&&&&&& Neutron creator process: " << track->GetCreatorProcess()->GetProcessName() << "; " <<
            // G4endl;
            const G4double kinetic_energy         = track->GetKineticEnergy();
            const G4ThreeVector& neutron_position = track->GetPosition();
            const G4ThreeVector& neutron_momentum = track->GetMomentum();

            auto* analysis_manager       = G4AnalysisManager::Instance();
            const auto* run_manager      = G4RunManager::GetRunManager();
            const G4int current_run_id   = run_manager->GetCurrentRun()->GetRunID();
            const G4int current_event_id = run_manager->GetCurrentEvent()->GetEventID();
            analysis_manager->FillNtupleIColumn(0, 0, current_run_id);
            analysis_manager->FillNtupleIColumn(0, 1, current_event_id);
            analysis_manager->FillNtupleDColumn(0, 2, kinetic_energy);
            // analysis_manager->FillNtupleDColumn(0, 3, neutron_position.x());
            // analysis_manager->FillNtupleDColumn(0, 4, neutron_position.y());
            // analysis_manager->FillNtupleDColumn(0, 5, neutron_position.z());
            // analysis_manager->FillNtupleDColumn(0, 6, neutron_momentum.x());
            // analysis_manager->FillNtupleDColumn(0, 7, neutron_momentum.y());
            // analysis_manager->FillNtupleDColumn(0, 8, neutron_momentum.z());
            analysis_manager->AddNtupleRow(0);
        }
    }
    else if (track->GetDefinition() == G4Proton::ProtonDefinition() && track->GetCreatorModelName() == "Undefined") {
        const auto* detector_construction = dynamic_cast<const MolybdenumGeometryConstruction*>(
            G4RunManager::GetRunManager()->GetUserDetectorConstruction());

        // const std::string current_logical_volume_name = track->GetVolume()->GetLogicalVolume()->GetName();
        // G4cout << "%%%%%%%% Proton creator model name: " << track->GetCreatorModelName()
        // << G4endl; // put this into if condition for choosing only primaries not (p, np) protons
        // G4cout << "-------- Proton creator process: " << track->GetCreatorProcess()->GetProcessName() << G4endl; //
        // SEGMENTATION FAULT
        const G4double kinetic_energy        = track->GetKineticEnergy();
        const G4ThreeVector& proton_position = track->GetPosition();
        const G4ThreeVector& proton_momentum = track->GetMomentum();

        auto* analysis_manager       = G4AnalysisManager::Instance();
        const auto* run_manager      = G4RunManager::GetRunManager();
        const G4int current_run_id   = run_manager->GetCurrentRun()->GetRunID();
        const G4int current_event_id = run_manager->GetCurrentEvent()->GetEventID();
        analysis_manager->FillNtupleIColumn(3, 0, current_run_id);
        analysis_manager->FillNtupleIColumn(3, 1, current_event_id);
        analysis_manager->FillNtupleDColumn(3, 2, kinetic_energy);
        // analysis_manager->FillNtupleDColumn(4, 3, proton_position.x());
        // analysis_manager->FillNtupleDColumn(4, 4, proton_position.y());
        // analysis_manager->FillNtupleDColumn(4, 5, proton_position.z());
        // analysis_manager->FillNtupleDColumn(4, 6, proton_momentum.x());
        // analysis_manager->FillNtupleDColumn(4, 7, proton_momentum.y());
        // analysis_manager->FillNtupleDColumn(4, 8, proton_momentum.z());
        analysis_manager->AddNtupleRow(3);
    }
    return fUrgent;
}
