#include "MolybdenumActionInitialization.hh"
// #include "MolybdenumNRSteppingAction.hh"


MolybdenumActionInitialization::MolybdenumActionInitialization()  = default;
MolybdenumActionInitialization::~MolybdenumActionInitialization() = default;

void MolybdenumActionInitialization::Build() const {
    auto* primary_generator = new MolybdenumPrimaryGeneratorAction();
    SetUserAction(primary_generator);

    auto* run_action = new MolybdenumRunAction();
    SetUserAction(run_action);

    auto* event_action = new MolybdenumEventAction(run_action);
    SetUserAction(event_action);

    auto* stepping_action = new MolybdenumSteppingAction();
    SetUserAction(stepping_action);

    auto* stacking_action = new MolybdenumStackingAction();
    SetUserAction(stacking_action);

    // auto* tracking_action = new MolybdenumTrackingAction(event_action);
    // SetUserAction(tracking_action);
}

void MolybdenumActionInitialization::BuildForMaster() const {
    auto* run_action = new MolybdenumRunAction();
    SetUserAction(run_action);
}
