#ifndef MOLYBDENUMGHOSTPROTONSD1_HH
#define MOLYBDENUMGHOSTPROTONSD1_HH
#include <G4AnalysisManager.hh>
#include <G4Run.hh>
#include <G4RunManager.hh>
#include "G4ParticleTable.hh"
#include "G4Proton.hh"
#include "G4VSensitiveDetector.hh"

class MolybdenumGhostProtonSD1 final : public G4VSensitiveDetector {
    public:
    explicit MolybdenumGhostProtonSD1(const std::string&);
    ~MolybdenumGhostProtonSD1() override;

    private:
    G4bool ProcessHits(G4Step*, G4TouchableHistory*) override;
    G4String detector_name_;
};

#endif // MOLYBDENUMGHOSTPROTONSD1_HH
