#include "MolybdenumRunAction.hh"

MolybdenumRunAction::MolybdenumRunAction() {
    // create an analysis manager singleton instance
    auto* analysis_manager = G4AnalysisManager::Instance();
    // create a n-tuple and its columns
    analysis_manager->SetDefaultFileType("root");
    // G4cout << "The following output file type is using: " << std::string(analysis_manager->GetType()) << G4endl;
    analysis_manager->SetVerboseLevel(1);
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
