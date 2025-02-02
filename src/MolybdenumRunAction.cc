#include "MolybdenumRunAction.hh"

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
    analysis_manager->CreateNtupleDColumn("position_x");
    analysis_manager->CreateNtupleDColumn("position_y");
    analysis_manager->CreateNtupleDColumn("position_z");
    analysis_manager->CreateNtupleDColumn("momentum_x");
    analysis_manager->CreateNtupleDColumn("momentum_y");
    analysis_manager->CreateNtupleDColumn("momentum_z");
    analysis_manager->FinishNtuple(0);

    // ============= NEUTRONS SCORING AFTER LEAVING MOLYBDENUM TABLET ================
    analysis_manager->CreateNtuple("neutrons_1", "neutrons_1");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    analysis_manager->CreateNtupleDColumn("position_x");
    analysis_manager->CreateNtupleDColumn("position_y");
    analysis_manager->CreateNtupleDColumn("position_z");
    analysis_manager->CreateNtupleDColumn("momentum_x");
    analysis_manager->CreateNtupleDColumn("momentum_y");
    analysis_manager->CreateNtupleDColumn("momentum_z");
    analysis_manager->CreateNtupleDColumn("momentum_direction_x");
    analysis_manager->CreateNtupleDColumn("momentum_direction_y");
    analysis_manager->CreateNtupleDColumn("momentum_direction_z");
    analysis_manager->FinishNtuple(1);

    // ===================== GAMMAS FROM (p, gamma) REACTIONS =========================
    analysis_manager->CreateNtuple("gamma_1", "gamma_1");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    analysis_manager->CreateNtupleDColumn("position_x");
    analysis_manager->CreateNtupleDColumn("position_y");
    analysis_manager->CreateNtupleDColumn("position_z");
    analysis_manager->CreateNtupleDColumn("momentum_x");
    analysis_manager->CreateNtupleDColumn("momentum_y");
    analysis_manager->CreateNtupleDColumn("momentum_z");
    analysis_manager->CreateNtupleDColumn("momentum_direction_x");
    analysis_manager->CreateNtupleDColumn("momentum_direction_y");
    analysis_manager->CreateNtupleDColumn("momentum_direction_z");
    analysis_manager->FinishNtuple(2);

    // ====================== PROTONS AT THE ALUMINIUM VACUUM WINDOW =====================
    analysis_manager->CreateNtuple("protons_vw_0", "protons_vw_0");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    analysis_manager->CreateNtupleDColumn("momentum_x");
    analysis_manager->CreateNtupleDColumn("momentum_y");
    analysis_manager->CreateNtupleDColumn("momentum_z");
    analysis_manager->CreateNtupleDColumn("momentum_direction_x");
    analysis_manager->CreateNtupleDColumn("momentum_direction_y");
    analysis_manager->CreateNtupleDColumn("momentum_direction_z");
    analysis_manager->CreateNtupleDColumn("position_x");
    analysis_manager->CreateNtupleDColumn("position_y");
    analysis_manager->CreateNtupleDColumn("position_z");
    analysis_manager->FinishNtuple(3);

    // ========================= BORN PROTONS ======================================
    analysis_manager->CreateNtuple("protons_born", "protons_born");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    analysis_manager->CreateNtupleDColumn("position_x");
    analysis_manager->CreateNtupleDColumn("position_y");
    analysis_manager->CreateNtupleDColumn("position_z");
    analysis_manager->CreateNtupleDColumn("momentum_x");
    analysis_manager->CreateNtupleDColumn("momentum_y");
    analysis_manager->CreateNtupleDColumn("momentum_z");
    analysis_manager->FinishNtuple(4);

    // =================== PROTONS AT THE TARGET TABLET =======================
    // Enter target tablet
    analysis_manager->CreateNtuple("protons_tt_enter", "protons_tt_enter");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    analysis_manager->CreateNtupleDColumn("momentum_x");
    analysis_manager->CreateNtupleDColumn("momentum_y");
    analysis_manager->CreateNtupleDColumn("momentum_z");
    analysis_manager->CreateNtupleDColumn("momentum_direction_x");
    analysis_manager->CreateNtupleDColumn("momentum_direction_y");
    analysis_manager->CreateNtupleDColumn("momentum_direction_z");
    analysis_manager->CreateNtupleDColumn("position_x");
    analysis_manager->CreateNtupleDColumn("position_y");
    analysis_manager->CreateNtupleDColumn("position_z");
    analysis_manager->FinishNtuple(5);
    // Exit from target table
    analysis_manager->CreateNtuple("protons_tt_exit", "protons_tt_exit");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    analysis_manager->CreateNtupleDColumn("momentum_x");
    analysis_manager->CreateNtupleDColumn("momentum_y");
    analysis_manager->CreateNtupleDColumn("momentum_z");
    analysis_manager->CreateNtupleDColumn("momentum_direction_x");
    analysis_manager->CreateNtupleDColumn("momentum_direction_y");
    analysis_manager->CreateNtupleDColumn("momentum_direction_z");
    analysis_manager->CreateNtupleDColumn("position_x");
    analysis_manager->CreateNtupleDColumn("position_y");
    analysis_manager->CreateNtupleDColumn("position_z");
    analysis_manager->FinishNtuple(6);

    // =============== NEUTRONS AT THE TARGET TABLET =======================
    // Start (born) at the target tablet
    analysis_manager->CreateNtuple("neutrons_tt_start", "neutrons_tt_start");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    analysis_manager->CreateNtupleDColumn("momentum_x");
    analysis_manager->CreateNtupleDColumn("momentum_y");
    analysis_manager->CreateNtupleDColumn("momentum_z");
    analysis_manager->CreateNtupleDColumn("momentum_direction_x");
    analysis_manager->CreateNtupleDColumn("momentum_direction_y");
    analysis_manager->CreateNtupleDColumn("momentum_direction_z");
    analysis_manager->CreateNtupleDColumn("position_x");
    analysis_manager->CreateNtupleDColumn("position_y");
    analysis_manager->CreateNtupleDColumn("position_z");
    analysis_manager->FinishNtuple(7);

    analysis_manager->CreateNtuple("neutrons_tt_end", "neutrons_tt_end");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    analysis_manager->CreateNtupleDColumn("momentum_x");
    analysis_manager->CreateNtupleDColumn("momentum_y");
    analysis_manager->CreateNtupleDColumn("momentum_z");
    analysis_manager->CreateNtupleDColumn("momentum_direction_x");
    analysis_manager->CreateNtupleDColumn("momentum_direction_y");
    analysis_manager->CreateNtupleDColumn("momentum_direction_z");
    analysis_manager->CreateNtupleDColumn("position_x");
    analysis_manager->CreateNtupleDColumn("position_y");
    analysis_manager->CreateNtupleDColumn("position_z");
    analysis_manager->FinishNtuple(8);

    analysis_manager->CreateNtuple("protons_sd0", "protons_sd0");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    analysis_manager->CreateNtupleDColumn("momentum_x");
    analysis_manager->CreateNtupleDColumn("momentum_y");
    analysis_manager->CreateNtupleDColumn("momentum_z");
    analysis_manager->CreateNtupleDColumn("momentum_direction_x");
    analysis_manager->CreateNtupleDColumn("momentum_direction_y");
    analysis_manager->CreateNtupleDColumn("momentum_direction_z");
    analysis_manager->CreateNtupleDColumn("position_x");
    analysis_manager->CreateNtupleDColumn("position_y");
    analysis_manager->CreateNtupleDColumn("position_z");
    analysis_manager->FinishNtuple(9);

    analysis_manager->CreateNtuple("protons_sd1", "protons_sd1");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    analysis_manager->CreateNtupleDColumn("momentum_x");
    analysis_manager->CreateNtupleDColumn("momentum_y");
    analysis_manager->CreateNtupleDColumn("momentum_z");
    analysis_manager->CreateNtupleDColumn("momentum_direction_x");
    analysis_manager->CreateNtupleDColumn("momentum_direction_y");
    analysis_manager->CreateNtupleDColumn("momentum_direction_z");
    analysis_manager->CreateNtupleDColumn("position_x");
    analysis_manager->CreateNtupleDColumn("position_y");
    analysis_manager->CreateNtupleDColumn("position_z");
    analysis_manager->FinishNtuple(10);

    analysis_manager->CreateNtuple("protons_vw_1", "protons_vw_1");
    analysis_manager->CreateNtupleIColumn("run_id");
    analysis_manager->CreateNtupleIColumn("event_id");
    analysis_manager->CreateNtupleDColumn("kinetic_energy");
    analysis_manager->CreateNtupleDColumn("momentum_x");
    analysis_manager->CreateNtupleDColumn("momentum_y");
    analysis_manager->CreateNtupleDColumn("momentum_z");
    analysis_manager->CreateNtupleDColumn("momentum_direction_x");
    analysis_manager->CreateNtupleDColumn("momentum_direction_y");
    analysis_manager->CreateNtupleDColumn("momentum_direction_z");
    analysis_manager->CreateNtupleDColumn("position_x");
    analysis_manager->CreateNtupleDColumn("position_y");
    analysis_manager->CreateNtupleDColumn("position_z");
    analysis_manager->FinishNtuple(11);
}
MolybdenumRunAction::~MolybdenumRunAction() = default;

void MolybdenumRunAction::BeginOfRunAction(const G4Run* run) {
    const G4int run_id     = run->GetRunID();
    auto* analysis_manager = G4AnalysisManager::Instance();
    const std::string prefix_file_name =
        "/home/ihor/CLionProjects/DMolybTarget/root_files/MolybdenumProtonBombardmentRun";
    const std::string suffix_file_name = std::to_string(run_id);
    const std::string output_file_name = prefix_file_name + suffix_file_name;
    analysis_manager->OpenFile(output_file_name);
    analysis_manager->FillNtupleIColumn(0, 0, run_id);
}
void MolybdenumRunAction::EndOfRunAction(const G4Run*) {
    auto* analysis_manager = G4AnalysisManager::Instance();
    analysis_manager->CloseFile();
}
