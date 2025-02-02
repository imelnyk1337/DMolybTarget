#ifndef MOLYBDENUMGHOSTPROTONSD0_HH
#define MOLYBDENUMGHOSTPROTONSD0_HH
#include <G4AnalysisManager.hh>
#include <G4Run.hh>
#include <G4RunManager.hh>
#include "G4ParticleTable.hh"
#include "G4Proton.hh"
#include "G4VSensitiveDetector.hh"

class MolybdenumGhostProtonSD0 final : public G4VSensitiveDetector {
    public:
    explicit MolybdenumGhostProtonSD0(const std::string&);
    ~MolybdenumGhostProtonSD0() override;

    private:
    G4bool ProcessHits(G4Step*, G4TouchableHistory*) override;
    G4String detector_name_;
};


#endif // MOLYBDENUMGHOSTPROTONSD0_HH
