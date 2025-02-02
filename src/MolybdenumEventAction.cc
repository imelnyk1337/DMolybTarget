#include "MolybdenumEventAction.hh"

#include <G4Event.hh>
#include <G4Track.hh>

MolybdenumEventAction::MolybdenumEventAction(MolybdenumRunAction* run_action) : run_action_(run_action) {
    G4AnalysisManager* analysis_manager = G4AnalysisManager::Instance();
}

MolybdenumEventAction::~MolybdenumEventAction() = default;

void MolybdenumEventAction::BeginOfEventAction(const G4Event* event) {
    event_track_pdg_map_.clear();
    event_track_name_map_.clear();
    activity_map_.clear();
}

void MolybdenumEventAction::EndOfEventAction(const G4Event* event) {

    auto* event_manager                = G4EventManager::GetEventManager();
    auto* current_event                = event_manager->GetConstCurrentEvent();
    const G4int event_id               = current_event->GetEventID();
    const G4double simulation_end_time = event_time * event_id;
    for (const auto& [Z, A] : std::views::keys(isotopes_map_)) {
        ComputeActivity(Z, A, simulation_end_time);
    }
}


void MolybdenumEventAction::AddTrackPDGtoMap(const G4Track* track) {
    event_track_pdg_map_[track->GetTrackID()] = track->GetParticleDefinition()->GetPDGEncoding();
}

G4int MolybdenumEventAction::GetTrackPDGfromMap(const G4int track_id) { return event_track_pdg_map_[track_id]; }

void MolybdenumEventAction::AddTrackNameToMap(const G4Track* track) {
    event_track_name_map_[track->GetTrackID()] = track->GetParticleDefinition()->GetParticleName();
}

std::string MolybdenumEventAction::GetTrackNameFromMap(const G4int track_id) { return event_track_name_map_[track_id]; }

void MolybdenumEventAction::RegisterIsotope(const G4int Z, const G4int A, const G4double time) {
    const auto key = std::make_pair(Z, A);
    if (!isotopes_map_.contains(key)) {
        isotopes_map_[key] = {0, time, 0};
    }
    isotopes_map_[key].count++;

    const G4ParticleDefinition* isotope = G4IonTable::GetIonTable()->GetIon(key.first, key.second, 0);
    if (isotope) {
        isotopes_map_[key].half_life = isotope->GetPDGLifeTime();
        G4cout << "(" << key.first << ", " << key.second << ") pdg life time: " << isotopes_map_[key].half_life
               << G4endl;
    }
}

void MolybdenumEventAction::ComputeActivity(const G4int Z, const G4int A, const G4double simulation_end_time) {
    const auto key                                 = std::make_pair(Z, A);
    const auto [count, production_time, half_life] = isotopes_map_[key]; // N_0, t_0, t_{1/2}
    const G4ParticleDefinition* isotope            = G4IonTable::GetIonTable()->GetIon(key.first, key.second, 0);
    G4double decay_constant                        = 0.;
    G4double activity                              = 0.;
    if (!isotope->GetPDGStable() || isotopes_map_[key].half_life > 0) {
        decay_constant         = std::log(2.) / half_life;
        const G4double count_t = count * std::exp(-decay_constant * (simulation_end_time - production_time)); // N(t)
        activity               = decay_constant * count_t;
        activity_map_[key]     = activity;
    }
    else {
        decay_constant     = -1.;
        activity           = -1.;
        activity_map_[key] = activity;
    }
    G4cout << "Isotope with Z = " << Z << ", A = " << A << ": " << activity << "; counts = " << isotopes_map_[key].count
           << "; lambda: " << decay_constant << G4endl;
}
