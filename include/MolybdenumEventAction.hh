#ifndef MOLYBDENUMEVENTACTION_HH
#define MOLYBDENUMEVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4AnalysisManager.hh"
#include "MolybdenumStackingAction.hh"

class MolybdenumEventAction final : public G4UserEventAction {
    public:
    explicit MolybdenumEventAction(MolybdenumStackingAction*);
    ~MolybdenumEventAction() override;
    void EndOfEventAction(const G4Event*) override;
    private:
    MolybdenumStackingAction* stacking_action_;

};
#endif // MOLYBDENUMEVENTACTION_HH
