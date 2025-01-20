#include "MolybdenumActionInitialization.hh"


MolybdenumActionInitialization::MolybdenumActionInitialization()  = default;
MolybdenumActionInitialization::~MolybdenumActionInitialization() = default;

void MolybdenumActionInitialization::Build() const {
    auto* primary_generator = new MolybdenumPrimaryGeneratorAction();
    SetUserAction(primary_generator);

    auto* run_action = new MolybdenumRunAction();
    SetUserAction(run_action);

    auto* event_action = new MolybdenumEventAction(run_action);
    SetUserAction(event_action);

    // auto* stepping_action = new MolybdenumSteppingAction(event_action);
    // SetUserAction(stepping_action);

    auto* stacking_action = new MolybdenumStackingAction(event_action);
    SetUserAction(stacking_action);
}

void MolybdenumActionInitialization::BuildForMaster() const {}
