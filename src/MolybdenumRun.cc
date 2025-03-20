#include "MolybdenumRun.hh"
#include "nlohmann/json.hpp"
#include "ranges"

using nlohmann::json;

MolybdenumRun::MolybdenumRun()  = default;
MolybdenumRun::~MolybdenumRun() = default;

void MolybdenumRun::Merge(const G4Run* run) {
    auto* local_run = dynamic_cast<const MolybdenumRun*>(run);

    std::map<G4String, G4int> local_isotope_count_map = local_run->isotopes_count_map_;
    for (std::map<G4String, G4int>::iterator it = local_isotope_count_map.begin(); it != local_isotope_count_map.end();
         ++it) {
        isotopes_count_map_[it->first] += it->second;
    }

    std::map<G4String, std::map<G4String, G4int>> local_production_processes_ =
        local_run->isotopes_production_processes_;
    for (std::map<G4String, std::map<G4String, G4int>>::iterator it0 = local_production_processes_.begin();
         it0 != local_production_processes_.end(); ++it0) {
        for (std::map<G4String, G4int>::iterator it1 = it0->second.begin(); it1 != it0->second.end(); ++it1) {
            isotopes_production_processes_[it0->first][it1->first] += it1->second;
        }
    }

    G4Run::Merge(run);
}

void MolybdenumRun::CountIsotope(const std::string& name) {
    if (isotopes_count_map_.contains(name)) {
        isotopes_count_map_[name]++;
    }
    else
        isotopes_count_map_[name] = 1;
}

// void MolybdenumRun::RegisterProcess(const std::string& process_name, const std::string& isotope_name) {
//     isotopes_production_processes_[process_name][isotope_name]++;
// }

void MolybdenumRun::RegisterProcess(const G4String& process_name, const G4String& isotope_name) {
    // std::cout << "Registering process: " << process_name << " for isotope: " << isotope_name << std::endl;
    if (isotopes_production_processes_.contains(process_name) &&
        isotopes_production_processes_[process_name].contains(isotope_name)) {
        isotopes_production_processes_[process_name][isotope_name]++;
    }
    else
        isotopes_production_processes_[process_name][isotope_name] = 1;

    // std::cout << "New count: " << isotopes_production_processes_[process_name][isotope_name] << std::endl;
}

void MolybdenumRun::RegisterIsotopeID(const G4int id, const G4String& particle_name) {
    isotopes_id_[id] = particle_name;
}

G4String MolybdenumRun::GetIsotopeByID(const G4int id) { return isotopes_id_[id]; }


void MolybdenumRun::EndOfRun(G4int run_number) {
    std::ofstream counts_file_output, processes_file_output;
    counts_file_output.open("/home/ihor/CLionProjects/DMolybTarget/datafiles/isotope_counts_" +
                            std::to_string(run_number) + ".json");
    processes_file_output.open("/home/ihor/CLionProjects/DMolybTarget/datafiles/processes_file_" +
                               std::to_string(run_number) + ".json");
    json counts_json, processes_json;
    for (const auto& [name, count] : isotopes_count_map_) {
        counts_json[name] = {{"count", count}};
    }
    for (const auto& process_name : std::ranges::views::keys(isotopes_production_processes_)) {
        for (const auto& isotope_name : isotopes_production_processes_[process_name] | std::views::keys) {
            processes_json[process_name][isotope_name] = isotopes_production_processes_[process_name][isotope_name];
            G4cout << "Process: " << process_name << G4endl;
            G4cout << "    Isotope: " << isotope_name << ": "
                   << isotopes_production_processes_[process_name][isotope_name] << G4endl;
        }
    }
    counts_file_output << counts_json;
    processes_file_output << processes_json;
    counts_file_output.close();
    processes_file_output.close();

    isotopes_count_map_.clear();
    isotopes_id_.clear();
    isotopes_production_processes_.clear();
}
