#ifndef MOLYBDENUMGHOSTSENSITIVEDETECTOR_HH
#define MOLYBDENUMGHOSTSENSITIVEDETECTOR_HH

#include "G4Gamma.hh"
#include "G4Neutron.hh"
#include "G4ParticleTable.hh"
#include "G4VSensitiveDetector.hh"

class MolybdenumGhostSensitiveDetector final : public G4VSensitiveDetector {
    public:
    explicit MolybdenumGhostSensitiveDetector(const std::string&);
    ~MolybdenumGhostSensitiveDetector() override;

    private:
    G4bool ProcessHits(G4Step*, G4TouchableHistory*) override;
    G4String detector_name_;
};

#endif // MOLYBDENUMGHOSTSENSITIVEDETECTOR_HH
