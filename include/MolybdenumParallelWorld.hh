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
#include "MolybdenumGhostNeutronSD.hh"
#include "MolybdenumGhostProtonSD0.hh"
#include "MolybdenumGhostProtonSD1.hh"

class MolybdenumParallelWorld final : public G4VUserParallelWorld {
    friend class MolybdenumDetectorConstruction;

    public:
    explicit MolybdenumParallelWorld(const G4String&);
    ~MolybdenumParallelWorld() override;
    void Construct() override;
    void ConstructSD() override;
    void BuildNeutronDetectionVolume();
    void BuildProtonLayeredDetectionVolume(const std::string&, G4double, G4bool);

    private:
    G4bool is_constructed_, neutron_detection_volume_visibility_;
    G4VSolid *solid_surface_ghost_world{}, *solid_proton_detector_cell{};
    G4LogicalVolume *logical_ghost_world{}, *logical_surface_ghost_world, *logical_proton_detector_cell{};
    G4VPhysicalVolume *physical_surface_ghost_world{}, *physical_proton_detector_cell{};
};

#endif // MOLYBDENUMPARALLELWORLD_HH
