#include "MolybdenumStackingAction.hh"
#include "MolybdenumDetectorConstruction.hh"

MolybdenumStackingAction::MolybdenumStackingAction()= default;
MolybdenumStackingAction::~MolybdenumStackingAction() = default;

G4ClassificationOfNewTrack MolybdenumStackingAction::ClassifyNewTrack(const G4Track* track) {
    // check if the track is a neutron
    if (track->GetDefinition() == G4Neutron::NeutronDefinition()) {
        const auto* detector_construction = dynamic_cast<const MolybdenumDetectorConstruction*>(
            G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        if (const G4LogicalVolume* logical_molybdenum_tablet = detector_construction->GetMolybdenumLogicalVolume();
            track->GetVolume()->GetLogicalVolume() == logical_molybdenum_tablet) {
            const G4double kinetic_energy         = track->GetKineticEnergy();
            const G4ThreeVector& neutron_position = track->GetPosition();
            const G4ThreeVector& neutron_momentum = track->GetMomentum();

            // G4cout << "A neutron was found with kinetic energy of " << kinetic_energy
            //        << "\n\t\tat position: " << neutron_position << "\n\t\twith momentum: " << neutron_momentum
            //        << G4endl;
            // neutron_energies_.push_back(kinetic_energy);
            // neutron_position_x_.push_back(neutron_position.x());
            // neutron_position_y_.push_back(neutron_position.y());
            // neutron_position_z_.push_back(neutron_position.z());
            // neutron_momentum_x_.push_back(neutron_momentum.x());
            // neutron_momentum_y_.push_back(neutron_momentum.y());
            // neutron_momentum_z_.push_back(neutron_momentum.z());
            auto* analysis_manager = G4AnalysisManager::Instance();
            analysis_manager->FillNtupleDColumn(0, 2, kinetic_energy);
            analysis_manager->FillNtupleDColumn(0, 3, neutron_position.x());
            analysis_manager->FillNtupleDColumn(0, 4, neutron_position.y());
            analysis_manager->FillNtupleDColumn(0, 5, neutron_position.z());
            analysis_manager->FillNtupleDColumn(0, 6, neutron_momentum.x());
            analysis_manager->FillNtupleDColumn(0, 7, neutron_momentum.y());
            analysis_manager->FillNtupleDColumn(0, 8, neutron_momentum.z());
            analysis_manager->AddNtupleRow(0);
        }
    }
    return fUrgent;
}

// void MolybdenumStackingAction::Reset() {
//     neutron_energies_.clear();
//     neutron_position_x_.clear();
//     neutron_position_y_.clear();
//     neutron_position_z_.clear();
//     neutron_momentum_x_.clear();
//     neutron_momentum_y_.clear();
//     neutron_momentum_z_.clear();
// }
//
// const std::vector<G4double>& MolybdenumStackingAction::GetNeutronKineticEnergies() const { return neutron_energies_;
// } const std::vector<G4double>& MolybdenumStackingAction::GetNeutronPositionX() const { return neutron_position_x_; }
// const std::vector<G4double>& MolybdenumStackingAction::GetNeutronPositionY() const { return neutron_position_y_; }
// const std::vector<G4double>& MolybdenumStackingAction::GetNeutronPositionZ() const { return neutron_position_z_; }
// const std::vector<G4double>& MolybdenumStackingAction::GetNeutronMomentumX() const { return neutron_momentum_x_; }
// const std::vector<G4double>& MolybdenumStackingAction::GetNeutronMomentumY() const { return neutron_momentum_y_; }
// const std::vector<G4double>& MolybdenumStackingAction::GetNeutronMomentumZ() const { return neutron_momentum_z_; }
