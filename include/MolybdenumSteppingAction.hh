#ifndef MOLYBDENUMSTEPPINGACTION_HH
#define MOLYBDENUMSTEPPINGACTION_HH

#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4Track.hh"
#include "G4UserSteppingAction.hh"
#include "MolybdenumEventAction.hh"

class MolybdenumSteppingAction final : public G4UserSteppingAction {
    public:
    explicit MolybdenumSteppingAction(MolybdenumEventAction*);
    ~MolybdenumSteppingAction() override;
    void UserSteppingAction(const G4Step*) override;

    private:
    MolybdenumEventAction* event_action_;
};


#endif // MOLYBDENUMSTEPPINGACTION_HH
