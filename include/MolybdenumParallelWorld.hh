#ifndef MOLYBDENUMPARALLELWORLD_HH
#define MOLYBDENUMPARALLELWORLD_HH

#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4ParallelWorldScoringProcess.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VSolid.hh"
#include "G4VUserParallelWorld.hh"
#include "G4VisAttributes.hh"
#include "MolybdenumGhostSensitiveDetector.hh"

class MolybdenumParallelWorld final : public G4VUserParallelWorld {
    public:
    explicit MolybdenumParallelWorld(const G4String&);
    ~MolybdenumParallelWorld() override;
    void Construct() override;
    void ConstructSD() override;

    private:
    G4bool is_constructed_;
    G4LogicalVolume* logical_surface_ghost_world{};
};

#endif // MOLYBDENUMPARALLELWORLD_HH
