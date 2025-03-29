#ifndef MOLYBDENUMRUN_HH
#define MOLYBDENUMRUN_HH

#include "G4Run.hh"
#include "MolybdenumAuxilaryUtilities.hh"
using isotopes::Isotope;

class MolybdenumRun final : public G4Run {
    public:
    MolybdenumRun();
    ~MolybdenumRun() override;

    void Merge(const G4Run*) override;
    void EndOfRun(G4int);

    void CountIsotope(const std::string&);
    void RegisterProcess(const G4String&, const G4String&);
    void RegisterIsotopeID(const G4int, const G4String&);
    void RegisterIsotopeParentID(const G4int, const G4int);
    G4String GetIsotopeByID(const G4int);
    void CountProtonsReachedTarget();

    private:
    std::map<G4String, G4int> isotopes_count_map_;
    std::map<G4String, G4int> activities_map_;
    std::map<G4String, std::map<G4String, G4int>> isotopes_production_processes_;
    std::map<G4int, G4String> isotopes_id_;
    G4int n_protons_;
    std::map<G4int, G4int> isotope_parent_ids_;
};

#endif // MOLYBDENUMRUN_HH
