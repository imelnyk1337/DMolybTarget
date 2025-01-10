#include "AuxilaryUtilities.hh"

std::vector<G4double> functions::convert_rgba_to_percents(const std::vector<G4double>& rgba) {
    constexpr G4double max = 255.;
    std::vector percents   = {rgba[0] / max, rgba[1] / max, rgba[2] / max, rgba[3]};
    return percents;
}

