#ifndef MOLYBDENUMTRACKINGACTION_HH
#define MOLYBDENUMTRACKINGACTION_HH

#include <map>
#include "G4Neutron.hh"
#include "G4Track.hh"
#include "G4TrackingManager.hh"
#include "G4Trajectory.hh"
#include "G4TrajectoryPoint.hh"
#include "G4UserTrackingAction.hh"
#include "MolybdenumEventAction.hh"


class MolybdenumTrackingAction final : public G4UserTrackingAction {
    public:
    explicit MolybdenumTrackingAction(MolybdenumEventAction*);
    ~MolybdenumTrackingAction() override;
    void PreUserTrackingAction(const G4Track*) override;
    void PostUserTrackingAction(const G4Track*) override;

    private:
    MolybdenumEventAction* event_action_;
};


#endif // MOLYBDENUMTRACKINGACTION_HH
