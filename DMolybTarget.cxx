#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "MolybdenumDetectorConstruction.hh"
#include "MolybdenumActionInitialization.hh"
#include "MolybdenumPhysicsListGeneral.hh"

int main(const int argc, char** argv) {

    auto* run_manager = new G4RunManager();
    run_manager->SetUserInitialization(new MolybdenumDetectorConstruction());
    run_manager->SetUserInitialization(new MolybdenumPhysicsListGeneral());
    run_manager->SetUserInitialization(new MolybdenumActionInitialization());
    run_manager->Initialize();

    auto* ui_executive = new G4UIExecutive(argc, argv);

    G4VisManager* vis_executive = new G4VisExecutive();
    vis_executive->Initialize();

    G4UImanager* ui_manager = G4UImanager::GetUIpointer();
    ui_manager->ApplyCommand("/vis/open OGL");
    // ui_manager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    ui_manager->ApplyCommand("/vis/drawVolume");
    ui_manager->ApplyCommand("/vis/viewer/autoRefresh true");
    ui_manager->ApplyCommand("/vis/scene/add/trajectories smooth");
    ui_manager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
    // ui_manager->ApplyCommand("/vis/scene/add/axes");
    ui_manager->ApplyCommand("/vis/modeling/trajectories/create/drawByParticleID 0");
    ui_manager->ApplyCommand("/vis/scene/add/eventID");
    // ui_manager->ApplyCommand("/vis/scene/add/scale 10 cm");


    ui_executive->SessionStart();
    return 0;
}