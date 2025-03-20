//
// Created by ihor on 1/11/25.
//

#ifndef MOLYBDENUMSTACKINGACTION_HH
#define MOLYBDENUMSTACKINGACTION_HH

#include "G4AnalysisManager.hh"
#include "G4Neutron.hh"
#include "G4Proton.hh"
#include "G4Track.hh"
#include "G4UserStackingAction.hh"
#include "G4VProcess.hh"
#include "MolybdenumEventAction.hh"

class MolybdenumStackingAction final : public G4UserStackingAction {
    public:
    explicit MolybdenumStackingAction();
    ~MolybdenumStackingAction() override;
    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*) override;
};

#endif // MOLYBDENUMSTACKINGACTION_HH
