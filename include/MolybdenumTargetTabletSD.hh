#ifndef MOLYBDENUMTARGETTABLETSD_HH
#define MOLYBDENUMTARGETTABLETSD_HH

#include "G4AnalysisManager.hh"
#include "G4Neutron.hh"
#include "G4ParticleDefinition.hh"
#include "G4Proton.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4VSensitiveDetector.hh"

class MolybdenumTargetTabletSD final : public G4VSensitiveDetector {
    public:
    explicit MolybdenumTargetTabletSD(const std::string& detector_name);
    ~MolybdenumTargetTabletSD() override;

    private:
    G4bool ProcessHits(G4Step*, G4TouchableHistory*) override;
    std::string detector_name_;
};


#endif // MOLYBDENUMTARGETTABLETSD_HH
