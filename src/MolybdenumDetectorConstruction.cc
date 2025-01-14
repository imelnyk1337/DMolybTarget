#include "MolybdenumDetectorConstruction.hh"

MolybdenumDetectorConstruction::MolybdenumDetectorConstruction() {
    // Solids

    // Solid world
    solid_world = nullptr;
    // Target body rear part
    solid_target_body_rear_part = nullptr;
    // Target body front part: an aluminium baffle
    solid_target_body_front_part_baffle = nullptr;
    // Target body front part: an aluminium holder with a hollow for the copper
    // target material holder
    solid_target_body_front_part_hollow = nullptr;
    // A union of the baffle and hollow
    solid_target_body_front_part = nullptr;

    solid_water_cooler_alum   = nullptr;
    solid_water_cooler_hollow = nullptr;
    solid_water_holder        = nullptr;
    solid_water_flow          = nullptr;

    // solid_rear_part & solid_front_part should be united to solid_target_body
    // G4VSolid* solid_target_body = nullptr;

    solid_copper_holder_baffle = nullptr;
    solid_copper_holder_hollow = nullptr;
    solid_copper_holder        = nullptr;

    solid_molybdenum100_tablet  = nullptr;
    solid_tablet_locker_solid   = nullptr;
    solid_tablet_locker_padding = nullptr;
    // solid_tablet_locker_solid & solid_tablet_locker_padding should be united
    // to solid_tablet_locker
    solid_tablet_locker  = nullptr;
    solid_threaded_clamp = nullptr;
    solid_helium_space   = nullptr;
    solid_vacuum_window  = nullptr;
    solid_vacuum_space   = nullptr;

    // Logical volumes

    // Logical world
    logical_world = nullptr;
    // Target body rear part
    logical_target_body_rear_part = nullptr;
    // Target body front part (a logical for the union of the baffle and hollow)
    logical_target_body_front_part = nullptr;
    logical_water_cooler_alum      = nullptr;
    logical_water_flow             = nullptr;
    logical_copper_holder          = nullptr;

    logical_molybdenum100_tablet = nullptr;
    logical_tablet_locker        = nullptr;
    logical_threaded_clamp       = nullptr;
    logical_helium_space         = nullptr;
    logical_vacuum_window        = nullptr;
    logical_vacuum_space         = nullptr;

    // Physical volumes

    // Physical world
    physical_world = nullptr;
    // Target body rear part
    physical_target_body_rear_part = nullptr;
    // Target body front part
    physical_target_body_front_part = nullptr;

    physical_water_cooler_alum    = nullptr;
    physical_water_flow           = nullptr;
    physical_copper_holder        = nullptr;
    physical_molybdenum100_tablet = nullptr;
    physical_molybdenum98_tablet  = nullptr;
    physical_tablet_locker        = nullptr;
    physical_threaded_clamp       = nullptr;
    physical_helium_space         = nullptr;
    physical_vacuum_window        = nullptr;
    physical_vacuum_space         = nullptr;

    // Materials
    air_material           = nullptr;
    aluminium_material     = nullptr;
    copper_material        = nullptr;
    helium_material        = nullptr;
    water_material         = nullptr;
    molybdenum100_material = nullptr;
    vacuum_material        = nullptr;

    // World
    world_position = G4ThreeVector(world_position_x, world_position_y, world_position_z);

    // Target body rear part
    target_body_rear_part_position = G4ThreeVector(target_body_rear_part_position_x, target_body_rear_part_position_y,
                                                   target_body_rear_part_position_z);

    // Water cooler
    water_cooler_hollow_rotation    = new G4RotationMatrix();
    water_cooler_hollow_translation = G4ThreeVector(
        water_cooler_hollow_translation_x, water_cooler_hollow_translation_y, water_cooler_hollow_translation_z);
    water_cooler_hollow_transform = nullptr;

    water_cooler_position = G4ThreeVector(water_cooler_position_x, water_cooler_position_y, water_cooler_position_z);

    // Target body front part
    target_body_front_part_hollow_rotation = new G4RotationMatrix();
    target_body_front_part_hollow_translation =
        G4ThreeVector(target_body_front_part_hollow_translation_x, target_body_front_part_hollow_translation_y,
                      target_body_front_part_hollow_translation_z);
    target_body_front_part_hollow_transform = nullptr;

    target_body_front_part_position = G4ThreeVector(
        target_body_front_part_position_x, target_body_front_part_position_y, target_body_front_part_position_z);

    // Copper holder
    copper_holder_hollow_translation = G4ThreeVector(
        copper_holder_hollow_translation_x, copper_holder_hollow_translation_y, copper_holder_hollow_translation_z);
    copper_holder_hollow_rotation  = new G4RotationMatrix();
    copper_holder_hollow_transform = nullptr;

    copper_holder_position =
        G4ThreeVector(copper_holder_position_x, copper_holder_position_y, copper_holder_position_z);

    // Molybdenum target tablet
    molybdenum100_tablet_position = G4ThreeVector(molybdenum100_tablet_position_x, molybdenum100_tablet_position_y,
                                                  molybdenum100_tablet_position_z);


    // Helium space
    helium_space_front_part_rotation = new G4RotationMatrix();
    helium_space_front_part_translation =
        G4ThreeVector(helium_space_front_part_translation_x, helium_space_front_part_translation_y,
                      helium_space_front_part_translation_z);
    helium_space_front_part_transform = nullptr;

    helium_space_position = G4ThreeVector(helium_space_position_x, helium_space_position_y, helium_space_position_z);

    // Aluminium vacuum window
    vacuum_window_position =
        G4ThreeVector(vacuum_window_position_x, vacuum_window_position_y, vacuum_window_position_z);

    // Vacuum cubic space
    vacuum_space_position = G4ThreeVector(vacuum_space_position_x, vacuum_space_position_y, vacuum_space_position_z);
}
MolybdenumDetectorConstruction::~MolybdenumDetectorConstruction() = default;

G4LogicalVolume* MolybdenumDetectorConstruction::GetMolybdenumLogicalVolume() const {
    return logical_molybdenum100_tablet;
}


void MolybdenumDetectorConstruction::DefineMaterials() {

    G4NistManager* nist_manager = G4NistManager::Instance();

    // ---- world material ----
    air_material = nist_manager->FindOrBuildMaterial("G4_AIR");

    // ---- aluminium for target body ----
    // aluminium_material = nist_manager->FindOrBuildMaterial("G4_Al");
    aluminium_material = new G4Material("aluminium_metal", 13, aluminium_atomic_mass, aluminium_density, kStateSolid);
    // aluminium_material->AddElement(nist_manager->FindOrBuildElement("Al"), 1);
    // ---- copper for target holder ----
    copper_material = new G4Material("copper_metal", 29, copper_atomic_mass, copper_density, kStateSolid);

    // ---- helium gas ----
    helium_material = new G4Material("helium_gas", 4, helium_atomic_mass, helium_density, kStateGas, helium_temperature, helium_pressure);

    // helium_material->AddElement(nist_manager->FindOrBuildElement("He"), 1);

    // ---- cooling water ----
    water_material = new G4Material("water", water_density, 2, kStateLiquid, water_temperature, water_pressure);
    water_material->AddElement(nist_manager->FindOrBuildElement("H"), 2);
    water_material->AddElement(nist_manager->FindOrBuildElement("O"), 1);

    // ---- molybdenum-100 ----
    auto* molybdenum100 = new G4Isotope("100Mo", 42, 100, molybdenum100_atomic_mass); // 1 g/mole == 1 Da
    auto* molybdenum98  = new G4Isotope("98Mo", 42, 98, molybdenum98_atomic_mass);
    auto* molybdenum97  = new G4Isotope("97Mo", 42, 97, molybdenum97_atomic_mass);
    auto* molybdenum96  = new G4Isotope("96Mo", 42, 96, molybdenum96_atomic_mass);
    auto* molybdenum95  = new G4Isotope("95Mo", 42, 95, molybdenum95_atomic_mass);
    auto* molybdenum94  = new G4Isotope("94Mo", 42, 94, molybdenum94_atomic_mass);
    auto* molybdenum92  = new G4Isotope("92Mo", 42, 92, molybdenum92_atomic_mass);

    auto* molybdenum100_enriched = new G4Element("100Mo_enriched", "100Mo_92_2", 7);
    molybdenum100_enriched->AddIsotope(molybdenum100, molybdenum100_abundance);
    molybdenum100_enriched->AddIsotope(molybdenum98, molybdenum98_abundance);
    molybdenum100_enriched->AddIsotope(molybdenum97, molybdenum97_abundance);
    molybdenum100_enriched->AddIsotope(molybdenum96, molybdenum96_abundance);
    molybdenum100_enriched->AddIsotope(molybdenum95, molybdenum95_abundance);
    molybdenum100_enriched->AddIsotope(molybdenum94, molybdenum94_abundance);
    molybdenum100_enriched->AddIsotope(molybdenum92, molybdenum92_abundance);

    molybdenum100_material = new G4Material("100Mo2C", molybdenum100_enriched_density, 1, kStateSolid);
    molybdenum100_material->AddElement(molybdenum100_enriched, 1);

    vacuum_material = new G4Material("vacuum", vacuum_atomic_number, vacuum_atomic_mass, vacuum_density, kStateGas,
                                     vacuum_temperature, vacuum_pressure);
}

void MolybdenumDetectorConstruction::BuildWorld() {
    solid_world                = new G4Box("solid_world", world_px, world_py, world_pz);
    logical_world              = new G4LogicalVolume(solid_world, air_material, "solid_world");
    const auto* world_vis_attr = new G4VisAttributes(false);
    logical_world->SetVisAttributes(world_vis_attr);
    physical_world =
        new G4PVPlacement(nullptr, world_position, logical_world, "physical_world", nullptr, false, 0, check_overlaps);
}

void MolybdenumDetectorConstruction::BuildTargetBodyRearPart() {
    // Target body rear part

    // A solid for target body rear part
    solid_target_body_rear_part = new G4Tubs("solid_target_body_rear_part", target_body_rear_part_radius_inner,
                                             target_body_rear_part_radius_outer, target_body_rear_part_half_length,
                                             target_body_rear_part_phi_start, target_body_rear_part_phi_delta);

    // A logical volume for the target body rear part
    logical_target_body_rear_part =
        new G4LogicalVolume(solid_target_body_rear_part, aluminium_material, "logical_target_body_rear_part");

    // Visual attributes for the logical volume of the target body rear part
    auto* target_body_rear_part_vis_attr = new G4VisAttributes(true);
    const std::vector<G4double> target_body_rear_part_colours =
        functions::convert_rgba_to_percents(std::vector{165., 169., 180., 0.7});
    target_body_rear_part_vis_attr->SetColour(target_body_rear_part_colours[0], target_body_rear_part_colours[1],
                                              target_body_rear_part_colours[2], target_body_rear_part_colours[3]);
    logical_target_body_rear_part->SetVisAttributes(target_body_rear_part_vis_attr);

    // A physical volume for the target body rear part
    physical_target_body_rear_part =
        new G4PVPlacement(nullptr, target_body_rear_part_position, logical_target_body_rear_part,
                          "physical_target_body_rear_part", logical_world, false, 0, check_overlaps);
}

void MolybdenumDetectorConstruction::BuildWaterCooler() {

    // An aluminium body for the pipe of HPLC (deionized) cooling water
    solid_water_cooler_alum =
        new G4Tubs("solid_water_cooler_alum", water_cooler_alum_radius_inner, water_cooler_alum_radius_outer,
                   water_cooler_half_length, water_cooler_phi_start, water_cooler_phi_delta);
    // A pipe for water: a tube where the water flows through
    solid_water_cooler_hollow =
        new G4Tubs("solid_water_cooler_hollow", water_cooler_hollow_radius_inner, water_cooler_hollow_radius_outer,
                   water_cooler_hollow_half_length, water_cooler_hollow_phi_start, water_cooler_hollow_phi_delta);

    water_cooler_hollow_rotation->rotateX(std::numbers::pi / 2 * rad);
    water_cooler_hollow_transform = new G4Transform3D(*water_cooler_hollow_rotation, water_cooler_hollow_translation);
    // An actual placeholder for the water
    solid_water_holder = new G4SubtractionSolid("solid_water_holder", solid_water_cooler_alum,
                                                solid_water_cooler_hollow, *water_cooler_hollow_transform);

    logical_water_cooler_alum =
        new G4LogicalVolume(solid_water_holder, aluminium_material, "logical_water_cooler_alum");

    auto* water_cooler_alum_vis_attr = new G4VisAttributes(true);
    const std::vector<G4double> water_cooler_alum_colours =
        functions::convert_rgba_to_percents(std::vector{165., 169., 180., 0.7});
    water_cooler_alum_vis_attr->SetColour(water_cooler_alum_colours[0], water_cooler_alum_colours[1],
                                          water_cooler_alum_colours[2], water_cooler_alum_colours[3]);
    logical_water_cooler_alum->SetVisAttributes(water_cooler_alum_vis_attr);

    physical_water_cooler_alum =
        new G4PVPlacement(nullptr, water_cooler_position, logical_water_cooler_alum, "physical_water_cooler_alum",
                          logical_world, false, 0, check_overlaps);

    // Now I have to create the water itself
    G4RotationMatrix* solid_water_flow_rotation = new G4RotationMatrix();
    solid_water_flow_rotation->rotateX(std::numbers::pi / 2 * rad);
    solid_water_flow =
        new G4DisplacedSolid("solid_water_flow", solid_water_cooler_hollow, solid_water_flow_rotation, G4ThreeVector());

    logical_water_flow        = new G4LogicalVolume(solid_water_flow, water_material, "logical_water_flow");
    auto* water_flow_vis_attr = new G4VisAttributes(true);
    const std::vector<G4double> water_flow_colours = functions::convert_rgba_to_percents(std::vector{0., 0., 255., .5});
    water_flow_vis_attr->SetColour(water_flow_colours[0], water_flow_colours[1], water_flow_colours[2],
                                   water_flow_colours[3]);
    logical_water_flow->SetVisAttributes(water_flow_vis_attr);
    // A physical volume for the water flow
    physical_water_flow = new G4PVPlacement(nullptr, water_cooler_position, logical_water_flow, "physical_water_flow",
                                            logical_world, false, 0, check_overlaps);
}

void MolybdenumDetectorConstruction::BuildTargetBodyFrontPart() {
    // Target body front part

    // A solid for target body front part: an aluminium baffle
    solid_target_body_front_part_baffle =
        new G4Tubs("solid_target_body_front_part_baffle", target_body_front_part_baffle_radius_inner,
                   target_body_front_part_baffle_radius_outer, target_body_front_part_baffle_half_length,
                   target_body_front_part_start_phi, target_body_front_part_delta_phi);

    // A solid for target body front part: an aluminium holder with a hollow for
    // the copper target material holder
    solid_target_body_front_part_hollow =
        new G4Tubs("solid_target_body_front_part_hollow", target_body_front_part_hollow_radius_inner,
                   target_body_front_part_hollow_radius_outer, target_body_front_part_hollow_half_length,
                   target_body_front_part_start_phi, target_body_front_part_delta_phi);
    // A solid for target body front part: a union of the baffle and hollow
    target_body_front_part_hollow_transform =
        new G4Transform3D(*target_body_front_part_hollow_rotation, target_body_front_part_hollow_translation);
    solid_target_body_front_part =
        new G4UnionSolid("solid_target_body_front_part", solid_target_body_front_part_baffle,
                         solid_target_body_front_part_hollow, *target_body_front_part_hollow_transform);

    // A logical for target body front part
    logical_target_body_front_part =
        new G4LogicalVolume(solid_target_body_front_part, aluminium_material, "logical_target_body_front_part");
    // Visual attributes for the logical target body front part
    auto* target_body_front_part_vis_attr = new G4VisAttributes(true);
    const std::vector<G4double> target_body_front_part_colours =
        functions::convert_rgba_to_percents(std::vector{165., 169., 180., 0.7});
    target_body_front_part_vis_attr->SetColour(target_body_front_part_colours[0], target_body_front_part_colours[1],
                                               target_body_front_part_colours[2], target_body_front_part_colours[3]);
    logical_target_body_front_part->SetVisAttributes(target_body_front_part_vis_attr);

    // A physical volume for the target body front part
    physical_target_body_front_part =
        new G4PVPlacement(nullptr, target_body_front_part_position, logical_target_body_front_part,
                          "physical_target_body_front_part", logical_world, false, 0, check_overlaps);
}

void MolybdenumDetectorConstruction::BuildCopperHolder() {
    solid_copper_holder_baffle =
        new G4Tubs("solid_copper_holder_baffle", copper_holder_baffle_radius_inner, copper_holder_baffle_radius_outer,
                   copper_holder_baffle_half_length, copper_holder_baffle_phi_start, copper_holder_baffle_phi_delta);

    solid_copper_holder_hollow =
        new G4Tubs("solid_copper_holder_hollow", copper_holder_hollow_radius_inner, copper_holder_hollow_radius_outer,
                   copper_holder_hollow_half_length, copper_holder_hollow_phi_start, copper_holder_hollow_phi_delta);

    copper_holder_hollow_rotation->rotateX(0. * deg);
    copper_holder_hollow_transform =
        new G4Transform3D(*copper_holder_hollow_rotation, copper_holder_hollow_translation);

    solid_copper_holder = new G4UnionSolid("solid_copper_holder", solid_copper_holder_baffle,
                                           solid_copper_holder_hollow, *copper_holder_hollow_transform);

    logical_copper_holder = new G4LogicalVolume(solid_copper_holder, copper_material, "logical_copper_holder");

    auto* copper_holder_vis_attr = new G4VisAttributes(true);
    const std::vector<G4double> copper_holder_colors =
        functions::convert_rgba_to_percents(std::vector{184., 115., 51., 0.8});
    copper_holder_vis_attr->SetColour(copper_holder_colors[0], copper_holder_colors[1], copper_holder_colors[2],
                                      copper_holder_colors[3]);

    logical_copper_holder->SetVisAttributes(copper_holder_vis_attr);

    physical_copper_holder = new G4PVPlacement(nullptr, copper_holder_position, logical_copper_holder,
                                               "physical_copper_holder", logical_world, false, 0, check_overlaps);
}

void MolybdenumDetectorConstruction::BuildMolybdenumTablet() {
    solid_molybdenum100_tablet =
        new G4Tubs("solid_molybdenum100_tablet", molybdenum100_tablet_radius_inner, molybdenum100_tablet_radius_outer,
                   molybdenum100_tablet_half_length, molybdenum100_tablet_phi_start, molybdenum100_tablet_phi_delta);

    logical_molybdenum100_tablet =
        new G4LogicalVolume(solid_molybdenum100_tablet, molybdenum100_material, "logical_molybdenum100_tablet");

    auto* molybdenum100_vis_attr = new G4VisAttributes(true);
    const std::vector<G4double> molybdenum100_colours =
        functions::convert_rgba_to_percents(std::vector{187., 187., 187., 1.});
    molybdenum100_vis_attr->SetColour(molybdenum100_colours[0], molybdenum100_colours[1], molybdenum100_colours[2],
                                      molybdenum100_colours[3]);

    logical_molybdenum100_tablet->SetVisAttributes(molybdenum100_vis_attr);

    physical_molybdenum100_tablet =
        new G4PVPlacement(nullptr, molybdenum100_tablet_position, logical_molybdenum100_tablet,
                          "physical_molybdenum100_tablet", logical_world, false, 0, check_overlaps);
}

void MolybdenumDetectorConstruction::BuildHeliumSpace() {
    solid_helium_space_rear_part  = new G4Tubs("solid_helium_space_rear_part", helium_space_rear_part_radius_inner,
                                               helium_space_rear_part_radius_outer, helium_space_rear_part_half_length,
                                               helium_space_phi_start, helium_space_phi_delta);
    solid_helium_space_front_part = new G4Tubs(
        "solid_helium_space_front_part", helium_space_front_part_radius_inner, helium_space_front_part_radius_outer,
        helium_space_front_part_half_length, helium_space_phi_start, helium_space_phi_delta);
    helium_space_front_part_rotation->rotateX(0. * deg);
    helium_space_front_part_transform =
        new G4Transform3D(*helium_space_front_part_rotation, helium_space_front_part_translation);
    solid_helium_space = new G4UnionSolid("solid_helium_space", solid_helium_space_rear_part,
                                          solid_helium_space_front_part, *helium_space_front_part_transform);

    logical_helium_space        = new G4LogicalVolume(solid_helium_space, helium_material, "logical_helium_space");
    auto* helium_space_vis_attr = new G4VisAttributes(true);
    const std::vector<G4double> helium_space_colors =
        functions::convert_rgba_to_percents(std::vector{163., 197., 226., 0.3});
    helium_space_vis_attr->SetColour(helium_space_colors[0], helium_space_colors[1], helium_space_colors[2],
                                     helium_space_colors[3]);
    logical_helium_space->SetVisAttributes(helium_space_vis_attr);

    physical_helium_space = new G4PVPlacement(nullptr, helium_space_position, logical_helium_space,
                                              "physical_helium_space", logical_world, false, 0, check_overlaps);
}

void MolybdenumDetectorConstruction::BuildVacuumWindow() {
    solid_vacuum_window = new G4Tubs("solid_vacuum_window", vacuum_window_radius_inner, vacuum_window_radius_outer,
                                     vacuum_window_half_length, vacuum_window_phi_start, vacuum_window_phi_delta);

    logical_vacuum_window = new G4LogicalVolume(solid_vacuum_window, aluminium_material, "logical_vacuum_window");
    auto* vacuum_window_vis_attr = new G4VisAttributes(true);
    const std::vector<G4double> vacuum_window_colours =
        functions::convert_rgba_to_percents(std::vector{165., 169., 180., .6});
    vacuum_window_vis_attr->SetColour(vacuum_window_colours[0], vacuum_window_colours[1], vacuum_window_colours[2],
                                      vacuum_window_colours[3]);
    logical_vacuum_window->SetVisAttributes(vacuum_window_vis_attr);

    physical_vacuum_window = new G4PVPlacement(nullptr, vacuum_window_position, logical_vacuum_window,
                                               "physical_vacuum_window", logical_world, false, 0, check_overlaps);
}

void MolybdenumDetectorConstruction::BuildVacuumSpace() {
    solid_vacuum_space = new G4Tubs("solid_vacuum_space", vacuum_space_radius_inner, vacuum_space_radius_outer,
                                    vacuum_space_half_length, vacuum_space_phi_start, vacuum_space_phi_delta);

    logical_vacuum_space        = new G4LogicalVolume(solid_vacuum_space, vacuum_material, "logical_vacuum_space");
    auto* vacuum_space_vis_attr = new G4VisAttributes(true);
    const std::vector<G4double> vacuum_space_colours =
        functions::convert_rgba_to_percents(std::vector{171., 176., 224., .1});
    vacuum_space_vis_attr->SetColour(vacuum_space_colours[0], vacuum_space_colours[1], vacuum_space_colours[2],
                                     vacuum_space_colours[3]);
    logical_vacuum_space->SetVisAttributes(vacuum_space_vis_attr);

    physical_vacuum_space = new G4PVPlacement(nullptr, vacuum_space_position, logical_vacuum_space,
                                              "physical_vacuum_space", logical_world, false, 0, check_overlaps);
}

G4VPhysicalVolume* MolybdenumDetectorConstruction::Construct() {
    DefineMaterials();
    BuildWorld();
    BuildTargetBodyRearPart();
    BuildWaterCooler();
    BuildTargetBodyFrontPart();
    BuildCopperHolder();
    BuildMolybdenumTablet();
    BuildHeliumSpace();
    BuildVacuumWindow();
    BuildVacuumSpace();
    return physical_world;
}
