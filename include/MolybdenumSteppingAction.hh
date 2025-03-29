#ifndef MOLYBDENUMSTEPPINGACTION_HH
#define MOLYBDENUMSTEPPINGACTION_HH

#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"
#include "G4UserSteppingAction.hh"
#include "MolybdenumEventAction.hh"
#include "MolybdenumRun.hh"

class MolybdenumSteppingAction final : public G4UserSteppingAction {
    public:
    MolybdenumSteppingAction();
    ~MolybdenumSteppingAction() override;
    void UserSteppingAction(const G4Step*) override;

    std::map<G4int, G4String> isotope_id_name_;
};


#endif // MOLYBDENUMSTEPPINGACTION_HH
