//
// Created by ihor on 1/11/25.
//

#ifndef MOLYBDENUMSTACKINGACTION_HH
#define MOLYBDENUMSTACKINGACTION_HH

#include "G4Neutron.hh"
#include "G4Track.hh"
#include "G4UserStackingAction.hh"
#include "G4VProcess.hh"
#include "G4AnalysisManager.hh"
#include "MolybdenumEventAction.hh"

class MolybdenumStackingAction final : public G4UserStackingAction {
    public:
    explicit MolybdenumStackingAction(MolybdenumEventAction*);
    ~MolybdenumStackingAction() override;
    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*) override;
    // void Reset();
    // [[nodiscard]] const std::vector<G4double>& GetNeutronKineticEnergies() const;
    // [[nodiscard]] const std::vector<G4double>& GetNeutronPositionX() const;
    // [[nodiscard]] const std::vector<G4double>& GetNeutronPositionY() const;
    // [[nodiscard]] const std::vector<G4double>& GetNeutronPositionZ() const;
    // [[nodiscard]] const std::vector<G4double>& GetNeutronMomentumX() const;
    // [[nodiscard]] const std::vector<G4double>& GetNeutronMomentumY() const;
    // [[nodiscard]] const std::vector<G4double>& GetNeutronMomentumZ() const;
    //
    // private:
    // std::vector<G4double> neutron_energies_;
    // std::vector<G4double> neutron_position_x_;
    // std::vector<G4double> neutron_position_y_;
    // std::vector<G4double> neutron_position_z_;
    // std::vector<G4double> neutron_momentum_x_;
    // std::vector<G4double> neutron_momentum_y_;
    // std::vector<G4double> neutron_momentum_z_;
    private:
    MolybdenumEventAction* event_action_;
};

#endif // MOLYBDENUMSTACKINGACTION_HH
