#ifndef MOLYBDENUMRUNACTION_HH
#define MOLYBDENUMRUNACTION_HH

#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4UserRunAction.hh"
#include "MolybdenumRun.hh"

class MolybdenumRunAction final : public G4UserRunAction {
    public:
    MolybdenumRunAction();
    ~MolybdenumRunAction() override;

    G4Run* GenerateRun() override;
    void BeginOfRunAction(const G4Run*) override;
    void EndOfRunAction(const G4Run*) override;

    private:
    MolybdenumRun* run_;
};

#endif // MOLYBDENUMRUNACTION_HH
