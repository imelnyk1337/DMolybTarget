#include "MolybdenumParallelWorld.hh"

MolybdenumParallelWorld::MolybdenumParallelWorld(const G4String& parallel_world_name) :
    G4VUserParallelWorld(parallel_world_name) {
    logical_surface_ghost_world = nullptr;
    is_constructed_             = false;
}

MolybdenumParallelWorld::~MolybdenumParallelWorld() = default;

void MolybdenumParallelWorld::Construct() {
    // if (is_constructed_) return;
    is_constructed_ = true;

    const G4VPhysicalVolume* physical_ghost_world = GetWorld();
    G4LogicalVolume* logical_ghost_world          = physical_ghost_world->GetLogicalVolume();
    const auto* logical_ghost_world_vis_attr      = new G4VisAttributes(false);
    logical_ghost_world->SetVisAttributes(logical_ghost_world_vis_attr);

    G4VSolid* solid_surface_ghost_world = new G4Box("ghost_box", 500. * mm, 500 * mm, 1. * nm);
    logical_surface_ghost_world         = new G4LogicalVolume(solid_surface_ghost_world, nullptr, "ghost_surface");
    auto* logical_surface_ghost_world_vis_attr = new G4VisAttributes(true, G4Colour(0.0, .5, .5, 0.3));
    logical_surface_ghost_world_vis_attr->SetForceSolid(true);
    logical_surface_ghost_world->SetVisAttributes(logical_surface_ghost_world_vis_attr);

    auto* physical_surface_ghost_world =
        new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 80. * mm), logical_surface_ghost_world,
                          "physical_ghost_surface", logical_ghost_world, false, 0, false);
}

void MolybdenumParallelWorld::ConstructSD() {
    const std::string detector_name          = "ghost_detector";
    auto* ghost_sensitive_detector           = new MolybdenumGhostSensitiveDetector(detector_name);
    G4SDManager* sensitive_detectors_manager = G4SDManager::GetSDMpointer();
    sensitive_detectors_manager->AddNewDetector(ghost_sensitive_detector);
    // SetSensitiveDetector("ghost_surface", ghost_sensitive_detector);
    logical_surface_ghost_world->SetSensitiveDetector(ghost_sensitive_detector);
    G4cout << "Sensitive detector is attached!" << G4endl;
}
