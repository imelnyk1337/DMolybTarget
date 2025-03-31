#ifndef MOLYBDENUMVACUUMWINDOWSD_HH
#define MOLYBDENUMVACUUMWINDOWSD_HH

#include "G4AnalysisManager.hh"
#include "G4Neutron.hh"
#include "G4Proton.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4VSensitiveDetector.hh"

class MolybdenumVacuumWindowSD final : public G4VSensitiveDetector {
    public:
    explicit MolybdenumVacuumWindowSD(const std::string&);
    ~MolybdenumVacuumWindowSD() override;

    private:
    G4bool ProcessHits(G4Step*, G4TouchableHistory*) override;
    std::string detector_name_;
};

#endif // MOLYBDENUMVACUUMWINDOWSD_HH
