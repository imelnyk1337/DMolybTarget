#ifndef MOLYBDENUMEVENTACTION_HH
#define MOLYBDENUMEVENTACTION_HH

#include <fstream>
#include <map>
#include <nlohmann/json.hpp>
#include <ranges>
#include <utility>
#include "G4AnalysisManager.hh"
#include "G4IonTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4UserEventAction.hh"
#include "MolybdenumAuxilaryUtilities.hh"
#include "MolybdenumRunAction.hh"

using isotopes::Isotope;
using nlohmann::json;

class MolybdenumEventAction final : public G4UserEventAction {
    public:
    explicit MolybdenumEventAction(MolybdenumRunAction*);
    ~MolybdenumEventAction() override;

    void BeginOfEventAction(const G4Event*) override;
    void EndOfEventAction(const G4Event*) override;
};

#endif // MOLYBDENUMEVENTACTION_HH
