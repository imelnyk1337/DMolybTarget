#include <iostream>
#include "G4MTRunManager.hh"
#include "G4ParallelWorldPhysics.hh"
#include "G4RunManager.hh"
#include "G4RunManagerFactory.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VModularPhysicsList.hh"
#include "G4VUserActionInitialization.hh"
#include "G4VisExecutive.hh"
#include "G4VisManager.hh"
#include "MolybdenumActionInitialization.hh"
#include "MolybdenumDetectorConstruction.hh"
#include "MolybdenumPhysicsListGeneral.hh"

int main(const int argc, char** argv) {
#ifdef G4MULTITHREADED
    auto* run_manager = new G4MTRunManager();
#endif
    constexpr G4int n_threads = 10;
    run_manager->SetNumberOfThreads(n_threads);

    G4VUserDetectorConstruction* world_construction = new MolybdenumDetectorConstruction();
    const std::string parallel_world_name           = "NeutronScoringWorld";
    G4VUserParallelWorld* parallel_world            = new MolybdenumParallelWorld(parallel_world_name);
    world_construction->RegisterParallelWorld(parallel_world);
    run_manager->SetUserInitialization(world_construction);

    G4VModularPhysicsList* physics_list = new MolybdenumPhysicsListGeneral();
    physics_list->RegisterPhysics(new G4ParallelWorldPhysics("NeutronScoringWorld"));
    run_manager->SetUserInitialization(physics_list);

    G4VUserActionInitialization* action_initialization = new MolybdenumActionInitialization();
    run_manager->SetUserInitialization(action_initialization);

    // run_manager->Initialize();

    G4UIExecutive* ui_executive = nullptr;
    if (argc == 1) {
        ui_executive = new G4UIExecutive(argc, argv);
    }

    G4VisManager* vis_executive = new G4VisExecutive();
    vis_executive->Initialize();

    G4UImanager* ui_manager = G4UImanager::GetUIpointer();
    if (ui_executive) {
        ui_manager->ApplyCommand("/control/execute vis.mac");
        ui_executive->SessionStart();
    }
    else {
        const std::string command  = "/control/execute ";
        const std::string filename = argv[1];
        ui_manager->ApplyCommand(command + filename);
    }
    // ui_manager->ApplyCommand("/vis/open OGL");
    // // ui_manager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    // ui_manager->ApplyCommand("/vis/drawVolume");
    // ui_manager->ApplyCommand("/vis/viewer/autoRefresh true");
    // ui_manager->ApplyCommand("/vis/scene/add/trajectories smooth");
    // ui_manager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
    // // ui_manager->ApplyCommand("/vis/scene/add/axes");
    // ui_manager->ApplyCommand("/vis/modeling/trajectories/create/drawByParticleID 0");
    // ui_manager->ApplyCommand("/vis/scene/add/eventID");
    // // ui_manager->ApplyCommand("/vis/scene/add/scale 10 cm");
    // ui_manager->ApplyCommand("/process/had/neutron/timeLimit 100.0 microsecond");
    // ui_manager->ApplyCommand("/process/had/neutron/energyLimit 100.0 MeV");

    // delete run_manager;

    return 0;
}
