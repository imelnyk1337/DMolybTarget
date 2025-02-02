#ifndef MOLYBDENUMEVENTACTION_HH
#define MOLYBDENUMEVENTACTION_HH

#include <map>
#include <ranges>
#include <utility>
#include "AuxilaryUtilities.hh"
#include "G4AnalysisManager.hh"
#include "G4IonTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4UserEventAction.hh"
#include "MolybdenumRunAction.hh"

using isotopes::Isotope;

class MolybdenumEventAction final : public G4UserEventAction {
    public:
    explicit MolybdenumEventAction(MolybdenumRunAction*);
    ~MolybdenumEventAction() override;

    void BeginOfEventAction(const G4Event*) override;
    void EndOfEventAction(const G4Event*) override;

    void AddTrackPDGtoMap(const G4Track*);
    G4int GetTrackPDGfromMap(const G4int);

    void AddTrackNameToMap(const G4Track*);
    std::string GetTrackNameFromMap(const G4int);

    void RegisterIsotope(const G4int, const G4int, const G4double);

    void ComputeActivity(const G4int, const G4int, const G4double);

    private:
    MolybdenumRunAction* run_action_;
    std::map<G4int, G4int> event_track_pdg_map_;
    std::map<G4int, std::string> event_track_name_map_;
    std::map<std::pair<G4int, G4int>, Isotope> isotopes_map_;
    std::map<std::pair<G4int, G4int>, G4double> activity_map_;
    static constexpr G4double event_time = 1.E-9 * s;
};

#endif // MOLYBDENUMEVENTACTION_HH
