#include "MolybdenumParallelWorld.hh"

#include "MolybdenumDetectorConstruction.hh"

MolybdenumParallelWorld::MolybdenumParallelWorld(const G4String& parallel_world_name) :
    G4VUserParallelWorld(parallel_world_name) {
    logical_surface_ghost_world          = nullptr;
    is_constructed_                      = false;
    neutron_detection_volume_visibility_ = true;
}

MolybdenumParallelWorld::~MolybdenumParallelWorld() = default;
//
void MolybdenumParallelWorld::BuildNeutronDetectionVolume(const G4bool visibility = true) {

    // solid_surface_ghost_world = new G4Box("ghost_box", 500. * mm, 500 * mm, 1. * nm);
    solid_surface_ghost_world =
        new G4Tubs("solid_neutron_detector", 0. * mm, 15. * mm, 1. * nm, 0. * rad, 2. * std::numbers::pi * rad);
    logical_surface_ghost_world = new G4LogicalVolume(solid_surface_ghost_world, nullptr, "ghost_surface");
    auto* logical_surface_ghost_world_vis_attr = new G4VisAttributes(visibility, G4Colour(0.0, .5, .5, 0.3));
    logical_surface_ghost_world_vis_attr->SetForceSolid(true);
    logical_surface_ghost_world->SetVisAttributes(logical_surface_ghost_world_vis_attr);

    constexpr G4double z_position = MolybdenumDetectorConstruction::molybdenum100_tablet_position_z;
    physical_surface_ghost_world =
        new G4PVPlacement(nullptr, G4ThreeVector(0., 0., z_position), logical_surface_ghost_world,
                          "physical_ghost_surface", logical_ghost_world, false, 0, false);
}

void MolybdenumParallelWorld::BuildProtonLayeredDetectionVolume(const std::string& volume_name,
                                                                const G4double position_z,
                                                                const G4bool visibility = false) {
    constexpr G4double proton_detector_px = 25. * mm;
    constexpr G4double proton_detector_py = 25. * mm;
    constexpr G4int n_rows = 100, n_cols = 100;
    constexpr G4double proton_detector_cell_px = proton_detector_px / n_cols;
    constexpr G4double proton_detector_cell_py = proton_detector_py / n_rows;


    const std::string solid_name = "solid_proton_detector_cell_" + volume_name;
    solid_proton_detector_cell   = new G4Box(solid_name, proton_detector_cell_px, proton_detector_cell_py, 1 * nm);

    const std::string logical_name = "logical_proton_detector_cell_" + volume_name;
    logical_proton_detector_cell   = new G4LogicalVolume(solid_proton_detector_cell, nullptr, logical_name);
    auto* logical_proton_detector_cell_vis_attr = new G4VisAttributes(visibility, G4Colour(0., .5, .5, .3));
    logical_proton_detector_cell_vis_attr->SetForceSolid(true);
    logical_proton_detector_cell->SetVisAttributes(logical_proton_detector_cell_vis_attr);

    const std::string physical_name = "physical_proton_detector_cell_" + volume_name;
    for (G4int i = 0; i < n_cols; ++i) {
        for (G4int j = 0; j < n_rows; ++j) {
            physical_proton_detector_cell = new G4PVPlacement(
                nullptr,
                G4ThreeVector(-proton_detector_px + (2 * i + 1) * proton_detector_cell_px,
                              -proton_detector_py + (2 * j + 1) * proton_detector_cell_py, position_z),
                logical_proton_detector_cell, physical_name, logical_ghost_world, true, i + j * n_cols, false);
        }
    }
}

void MolybdenumParallelWorld::Construct() {
    if (is_constructed_)
        return;
    is_constructed_                               = true;
    const G4VPhysicalVolume* physical_ghost_world = GetWorld();
    logical_ghost_world                           = physical_ghost_world->GetLogicalVolume();
    const auto* logical_ghost_world_vis_attr      = new G4VisAttributes(false);
    logical_ghost_world->SetVisAttributes(logical_ghost_world_vis_attr);

    BuildNeutronDetectionVolume(true);
    constexpr G4double proton_sd0_position = MolybdenumDetectorConstruction::molybdenum100_tablet_position_z +
        MolybdenumDetectorConstruction::molybdenum100_tablet_half_length;
    constexpr G4double proton_sd1_position = MolybdenumDetectorConstruction::vacuum_window_position_z -
        MolybdenumDetectorConstruction::vacuum_window_half_length;
    BuildProtonLayeredDetectionVolume("0", proton_sd0_position, false);
    BuildProtonLayeredDetectionVolume("1", proton_sd1_position, false);
    // BuildProtonLayeredDetectionVolume("2", 400. * mm);
    // BuildProtonLayeredDetectionVolume("3", 450. * mm);
}

void MolybdenumParallelWorld::ConstructSD() {

    G4SDManager* sensitive_detectors_manager = G4SDManager::GetSDMpointer();

    const std::string neutron_detector_name = "ghost_detector";
    auto* ghost_sensitive_detector          = new MolybdenumGhostNeutronSD(neutron_detector_name);
    if (logical_surface_ghost_world) {
        sensitive_detectors_manager->AddNewDetector(ghost_sensitive_detector);
        logical_surface_ghost_world->SetSensitiveDetector(ghost_sensitive_detector);
    }

    const std::string proton_detector0_name = "ghost_proton_detector0";
    auto* ghost_proton_sensitive_detector0  = new MolybdenumGhostProtonSD0(proton_detector0_name);
    sensitive_detectors_manager->AddNewDetector(ghost_proton_sensitive_detector0);
    SetSensitiveDetector("logical_proton_detector_cell_0", ghost_proton_sensitive_detector0);
    // logical_proton_detector_cell->SetSensitiveDetector(ghost_proton_sensitive_detector);
    // G4cout << "Sensitive detector is attached!" << G4endl;

    const std::string proton_detector1_name = "ghost_proton_detector1";
    auto* ghost_proton_sensitive_detector1  = new MolybdenumGhostProtonSD1(proton_detector1_name);
    sensitive_detectors_manager->AddNewDetector(ghost_proton_sensitive_detector1);
    SetSensitiveDetector("logical_proton_detector_cell_1", ghost_proton_sensitive_detector1);
    // logical_proton_detector_cell->SetSensitiveDetector(ghost_proton_sensitive_detector);
    // G4cout << "Sensitive detector is attached!" << G4endl;
}
