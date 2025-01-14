#ifndef MOLYBDENUMRUNACTION_HH
#define MOLYBDENUMRUNACTION_HH

#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4UserRunAction.hh"

class MolybdenumRunAction final : public G4UserRunAction {
    public:
    MolybdenumRunAction();
    ~MolybdenumRunAction() override;

    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;
};

#endif // MOLYBDENUMRUNACTION_HH
