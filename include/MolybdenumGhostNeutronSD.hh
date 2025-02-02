#ifndef MOLYBDENUMGHOSTSENSITIVEDETECTOR_HH
#define MOLYBDENUMGHOSTSENSITIVEDETECTOR_HH

#include <G4AnalysisManager.hh>
#include <G4Run.hh>
#include <G4RunManager.hh>
#include "G4Gamma.hh"
#include "G4Neutron.hh"
#include "G4ParticleTable.hh"
#include "G4VSensitiveDetector.hh"

class MolybdenumGhostNeutronSD final : public G4VSensitiveDetector {
    public:
    explicit MolybdenumGhostNeutronSD(const std::string&);
    ~MolybdenumGhostNeutronSD() override;

    private:
    G4bool ProcessHits(G4Step*, G4TouchableHistory*) override;
    G4String detector_name_;
};

#endif // MOLYBDENUMGHOSTSENSITIVEDETECTOR_HH
