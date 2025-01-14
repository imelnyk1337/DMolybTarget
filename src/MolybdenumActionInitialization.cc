#include "MolybdenumActionInitialization.hh"


MolybdenumActionInitialization::MolybdenumActionInitialization()  = default;
MolybdenumActionInitialization::~MolybdenumActionInitialization() = default;

void MolybdenumActionInitialization::Build() const {
    auto* primary_generator = new MolybdenumPrimaryGeneratorAction();
    SetUserAction(primary_generator);

    auto* run_action = new MolybdenumRunAction();
    SetUserAction(run_action);

    auto* stacking_action = new MolybdenumStackingAction();
    SetUserAction(stacking_action);

    auto* event_action = new MolybdenumEventAction(stacking_action);
    SetUserAction(event_action);
}

void MolybdenumActionInitialization::BuildForMaster() const {}
