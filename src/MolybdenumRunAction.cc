#include "MolybdenumRunAction.hh"

#include "MolybdenumRun.hh"

MolybdenumRunAction::MolybdenumRunAction() {
    // create an analysis manager singleton instance
    auto* analysis_manager = G4AnalysisManager::Instance();
    // create a n-tuple and its columns
    analysis_manager->SetDefaultFileType("root");
    // G4cout << "The following output file type is using: " << std::string(analysis_manager->GetType()) << G4endl;
    analysis_manager->SetVerboseLevel(1);

    // =============== BORN NEUTRONS SCORING =================
    analysis_manager->CreateNtuple("neutrons_born", "neutrons_born");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    // analysis_manager->CreateNtupleDColumn("position_x");
    // analysis_manager->CreateNtupleDColumn("position_y");
    // analysis_manager->CreateNtupleDColumn("position_z");
    // analysis_manager->CreateNtupleDColumn("momentum_x");
    // analysis_manager->CreateNtupleDColumn("momentum_y");
    // analysis_manager->CreateNtupleDColumn("momentum_z");
    analysis_manager->FinishNtuple(0);

    // ============= NEUTRONS AT THE MIDDLE OF THE MOLYBDENUM100 TABLET ================
    analysis_manager->CreateNtuple("neutrons", "neutrons");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    // analysis_manager->CreateNtupleDColumn("position_x");
    // analysis_manager->CreateNtupleDColumn("position_y");
    // analysis_manager->CreateNtupleDColumn("position_z");
    // analysis_manager->CreateNtupleDColumn("momentum_x");
    // analysis_manager->CreateNtupleDColumn("momentum_y");
    // analysis_manager->CreateNtupleDColumn("momentum_z");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_x");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_y");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_z");
    analysis_manager->FinishNtuple(1);

    // ===================== GAMMAS =========================
    analysis_manager->CreateNtuple("gamma", "gamma");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    // analysis_manager->CreateNtupleDColumn("position_x");
    // analysis_manager->CreateNtupleDColumn("position_y");
    // analysis_manager->CreateNtupleDColumn("position_z");
    // analysis_manager->CreateNtupleDColumn("momentum_x");
    // analysis_manager->CreateNtupleDColumn("momentum_y");
    // analysis_manager->CreateNtupleDColumn("momentum_z");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_x");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_y");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_z");
    analysis_manager->FinishNtuple(2);

    // ========================= BORN PROTONS ======================================
    analysis_manager->CreateNtuple("protons_born", "protons_born");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    // analysis_manager->CreateNtupleDColumn("position_x");
    // analysis_manager->CreateNtupleDColumn("position_y");
    // analysis_manager->CreateNtupleDColumn("position_z");
    // analysis_manager->CreateNtupleDColumn("momentum_x");
    // analysis_manager->CreateNtupleDColumn("momentum_y");
    // analysis_manager->CreateNtupleDColumn("momentum_z");
    analysis_manager->FinishNtuple(3);


    // ========================= PROTONS SD0 ======================================
    analysis_manager->CreateNtuple("protons_sd0", "protons_sd0");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    // analysis_manager->CreateNtupleDColumn("momentum_x");
    // analysis_manager->CreateNtupleDColumn("momentum_y");
    // analysis_manager->CreateNtupleDColumn("momentum_z");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_x");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_y");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_z");
    // analysis_manager->CreateNtupleDColumn("position_x");
    // analysis_manager->CreateNtupleDColumn("position_y");
    // analysis_manager->CreateNtupleDColumn("position_z");
    analysis_manager->FinishNtuple(4);

    // ========================= PROTONS SD1 ======================================
    analysis_manager->CreateNtuple("protons_sd1", "protons_sd1");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    // analysis_manager->CreateNtupleDColumn("momentum_x");
    // analysis_manager->CreateNtupleDColumn("momentum_y");
    // analysis_manager->CreateNtupleDColumn("momentum_z");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_x");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_y");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_z");
    // analysis_manager->CreateNtupleDColumn("position_x");
    // analysis_manager->CreateNtupleDColumn("position_y");
    // analysis_manager->CreateNtupleDColumn("position_z");
    analysis_manager->FinishNtuple(5);

    // ========================= PROTONS ENTERING MO100 TABLET ======================================
    analysis_manager->CreateNtuple("protons_t", "protons_t");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    // analysis_manager->CreateNtupleDColumn("momentum_x");
    // analysis_manager->CreateNtupleDColumn("momentum_y");
    // analysis_manager->CreateNtupleDColumn("momentum_z");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_x");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_y");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_z");
    // analysis_manager->CreateNtupleDColumn("position_x");
    // analysis_manager->CreateNtupleDColumn("position_y");
    // analysis_manager->CreateNtupleDColumn("position_z");
    analysis_manager->FinishNtuple(6);

    // ========================= PROTONS ENTERING VACUUM WINDOW ======================================
    analysis_manager->CreateNtuple("protons_vwe", "protons_vwe");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    // analysis_manager->CreateNtupleDColumn("momentum_x");
    // analysis_manager->CreateNtupleDColumn("momentum_y");
    // analysis_manager->CreateNtupleDColumn("momentum_z");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_x");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_y");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_z");
    // analysis_manager->CreateNtupleDColumn("position_x");
    // analysis_manager->CreateNtupleDColumn("position_y");
    // analysis_manager->CreateNtupleDColumn("position_z");
    analysis_manager->FinishNtuple(7);

    // ========================= PROTONS ENTERING VACUUM WINDOW ======================================
    analysis_manager->CreateNtuple("protons_vwl", "protons_vwl");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    // analysis_manager->CreateNtupleDColumn("momentum_x");
    // analysis_manager->CreateNtupleDColumn("momentum_y");
    // analysis_manager->CreateNtupleDColumn("momentum_z");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_x");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_y");
    // analysis_manager->CreateNtupleDColumn("momentum_direction_z");
    // analysis_manager->CreateNtupleDColumn("position_x");
    // analysis_manager->CreateNtupleDColumn("position_y");
    // analysis_manager->CreateNtupleDColumn("position_z");
    analysis_manager->FinishNtuple(8);
}
MolybdenumRunAction::~MolybdenumRunAction() = default;

G4Run* MolybdenumRunAction::GenerateRun() {
    run_ = new MolybdenumRun();
    return run_;
}

void MolybdenumRunAction::BeginOfRunAction(const G4Run*) {
    const G4int run_id     = run_->GetRunID();
    auto* analysis_manager = G4AnalysisManager::Instance();
    const std::string prefix_file_name =
        "/home/ihor/CLionProjects/DMolybTarget/root_files/MolybdenumProtonBombardmentRun";
    const std::string suffix_file_name = std::to_string(run_id);
    const std::string output_file_name = prefix_file_name + suffix_file_name;
    analysis_manager->OpenFile(output_file_name);
    analysis_manager->FillNtupleIColumn(0, 0, run_id);
}
void MolybdenumRunAction::EndOfRunAction(const G4Run*) {
    const G4int run_number = run_->GetRunID();
    if (isMaster) {
        run_->EndOfRun(run_number);
    }
    auto* analysis_manager = G4AnalysisManager::Instance();
    analysis_manager->CloseFile();
}
