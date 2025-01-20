#ifndef MOLYBDENUMEVENTACTION_HH
#define MOLYBDENUMEVENTACTION_HH

#include "G4UserEventAction.hh"
#include "G4AnalysisManager.hh"
#include "MolybdenumRunAction.hh"

class MolybdenumEventAction final : public G4UserEventAction {
    public:
    explicit MolybdenumEventAction(MolybdenumRunAction*);
    ~MolybdenumEventAction() override;
    void EndOfEventAction(const G4Event*) override;
    private:
    MolybdenumRunAction* run_action_;

};
#endif // MOLYBDENUMEVENTACTION_HH
