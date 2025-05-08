#include "MolybdenumRun.hh"

#include <G4HadronicProcess.hh>
#include <G4Proton.hh>

#include "nlohmann/json.hpp"
#include "ranges"

using nlohmann::json;

MolybdenumRun::MolybdenumRun() { n_protons_ = 0; };
MolybdenumRun::~MolybdenumRun() = default;

void MolybdenumRun::Merge(const G4Run* run) {
    auto* local_run = dynamic_cast<const MolybdenumRun*>(run);

    n_protons_ += local_run->n_protons_;

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

void MolybdenumRun::CountProtonsReachedTarget() { n_protons_++; }

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

void MolybdenumRun::RegisterIsotopeParentID(const G4int isotope_id, const G4int parent_id) {
    isotope_parent_ids_[isotope_id] = parent_id;
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

    constexpr G4double real_exp_n_protons = 6.3 * 10E-6 * 280. / (1.6 * 10E-19);
    G4cout << "****** PROTONS INFO ****** " << '\n'
           << "Totally, " << n_protons_ << " protons reached the molybdenum target" << G4endl;
    G4cout << "Number of protons delivered during 280 sec of proton bombardment with current of 6.3 uA in a real experiment: "
           << real_exp_n_protons << G4endl;
    G4double scaling_factor = real_exp_n_protons / n_protons_;
    G4double decay_constant = 3.21E-5;
    G4cout << "Scaling factor = real / sim = " << scaling_factor << G4endl;
    G4double activity = scaling_factor * decay_constant * isotopes_count_map_["Tc99[142.683]"];
    G4cout << "Tc99m activity = " << activity / 1.E6 << " MBq" << G4endl;

    counts_file_output << counts_json;
    processes_file_output << processes_json;
    counts_file_output.close();
    processes_file_output.close();

    isotopes_count_map_.clear();
    isotopes_id_.clear();
    isotopes_production_processes_.clear();

    // const G4ProcessManager* proton_process_manager = G4Proton::Proton()->GetProcessManager();
    // G4VProcess* proton_inelastic = proton_process_manager->GetProcess("protonInelastic");
    // G4HadronicProcess* proton_hadronic_inelastic = dynamic_cast<G4HadronicProcess*>(proton_inelastic);
    // // proton_hadronic_inelastic->GetMicroscopicCrossSection()

}
