#include "MolybdenumEventAction.hh"

#include <G4Event.hh>

MolybdenumEventAction::MolybdenumEventAction(MolybdenumStackingAction* stacking_action) :
    stacking_action_(stacking_action) {
    G4AnalysisManager* analysis_manager = G4AnalysisManager::Instance();
}

MolybdenumEventAction::~MolybdenumEventAction() = default;

void MolybdenumEventAction::EndOfEventAction(const G4Event* event) {
    G4AnalysisManager* analysis_manager = G4AnalysisManager::Instance();
    const G4int event_id                = event->GetEventID();
    // const auto& kinetic_energies        = stacking_action_->GetNeutronKineticEnergies();
    // const auto& neutron_position_x      = stacking_action_->GetNeutronPositionX();
    // const auto& neutron_position_y      = stacking_action_->GetNeutronPositionY();
    // const auto& neutron_position_z      = stacking_action_->GetNeutronPositionZ();
    // const auto& neutron_momentum_x      = stacking_action_->GetNeutronMomentumX();
    // const auto& neutron_momentum_y      = stacking_action_->GetNeutronMomentumY();
    // const auto& neutron_momentum_z      = stacking_action_->GetNeutronMomentumZ();
    analysis_manager->FillNtupleIColumn(0, 1, event_id);

    // const std::size_t neutron_number = kinetic_energies.size();
    // for (std::size_t i = 0; i < neutron_number; ++i) {
    //     analysis_manager->FillNtupleIColumn(0, 1, event_id);
    //     analysis_manager->FillNtupleDColumn(0, 2, kinetic_energies[i]);
    //     analysis_manager->FillNtupleDColumn(0, 3, neutron_position_x[i]);
    //     analysis_manager->FillNtupleDColumn(0, 4, neutron_position_y[i]);
    //     analysis_manager->FillNtupleDColumn(0, 5, neutron_position_z[i]);
    //     analysis_manager->FillNtupleDColumn(0, 6, neutron_momentum_x[i]);
    //     analysis_manager->FillNtupleDColumn(0, 7, neutron_momentum_y[i]);
    //     analysis_manager->FillNtupleDColumn(0, 8, neutron_momentum_z[i]);
    //     analysis_manager->AddNtupleRow(0);
    // }

    // stacking_action_->Reset();
}
