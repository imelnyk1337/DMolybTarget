#ifndef AUXILARYUTILITIES_HH
#define AUXILARYUTILITIES_HH

#include <vector>
#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4Types.hh"

namespace functions {
    std::vector<G4double> convert_rgba_to_percents(const std::vector<G4double>&);
    void fill_ntuple(const G4int, const G4StepPoint*);
} // namespace functions

namespace isotopes {
    struct Isotope {
        std::string name;
        G4int Z;
        G4int A;
        G4int count;
        G4double half_life;
        std::string volume;
    };
} // namespace isotopes

#endif // AUXILARYUTILITIES_HH
