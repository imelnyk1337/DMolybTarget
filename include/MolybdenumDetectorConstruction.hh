#ifndef MOLYBDENUMDETECTORCONSTRUCTION_HH
#define MOLYBDENUMDETECTORCONSTRUCTION_HH

#include "AuxilaryUtilities.hh"
#include "G4Box.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVParameterised.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4RunManager.hh"
#include "G4SubtractionSolid.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VSolid.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VisAttributes.hh"

class MolybdenumDetectorConstruction final
    : public G4VUserDetectorConstruction {
  public:
    MolybdenumDetectorConstruction();
    ~MolybdenumDetectorConstruction() override;
    G4VPhysicalVolume *Construct() override;
    void DefineMaterials();
    void BuildWorld();
    void BuildTargetBodyRearPart();
    void BuildWaterCooler();
    void BuildTargetBodyFrontPart();
    void BuildCopperHolder();
    void BuildMolybdenumTablet();
    void BuildDegrader();
    void BuildTabletLocker();
    void BuildThreadedClamp();
    void BuildVacuumWindow();
    void BuildVacuumSpace();
    // void BuildMolybdenumTablet(G4bool is_double=false);

  private:
    // Solids

    // Solid world
    G4VSolid *solid_world;
    // Target body rear part
    G4VSolid *solid_target_body_rear_part;
    // Target body front part: an aluminium baffle
    G4VSolid *solid_target_body_front_part_baffle;
    // Target body front part: an aluminium holder with a hollow for the copper
    // target material holder
    G4VSolid *solid_target_body_front_part_hollow;
    // A union of the baffle and hollow
    G4VSolid *solid_target_body_front_part;

    G4VSolid *solid_water_cooler_alum;
    G4VSolid *solid_water_cooler_hollow;
    G4VSolid *solid_water_holder;
    G4VSolid *solid_water_flow;

    // solid_rear_part & solid_front_part should be united to solid_target_body
    // G4VSolid* solid_target_body = nullptr;

    G4VSolid *solid_copper_holder_baffle;
    G4VSolid *solid_copper_holder_hollow;
    G4VSolid *solid_copper_holder;

    G4VSolid *solid_molybdenum100_tablet;
    G4VSolid *solid_tablet_locker_solid;
    G4VSolid *solid_tablet_locker_padding;
    // solid_tablet_locker_solid & solid_tablet_locker_padding should be united
    // to solid_tablet_locker
    G4VSolid *solid_tablet_locker;
    G4VSolid *solid_threaded_clamp;
    G4VSolid *solid_helium_space;
    G4VSolid *solid_vacuum_window;
    G4VSolid *solid_vacuum_space;

    // Logical volumes

    // Logical world
    G4LogicalVolume *logical_world;
    // Target body rear part
    G4LogicalVolume *logical_target_body_rear_part;
    // Target body front part (a logical for the union of the baffle and hollow)
    G4LogicalVolume *logical_target_body_front_part;
    G4LogicalVolume *logical_water_cooler_alum;
    G4LogicalVolume *logical_water_flow;
    G4LogicalVolume *logical_copper_holder;

    G4LogicalVolume *logical_molybdenum100_tablet;
    G4LogicalVolume *logical_tablet_locker;
    G4LogicalVolume *logical_threaded_clamp;
    G4LogicalVolume *logical_helium_space;
    G4LogicalVolume *logical_vacuum_window;
    G4LogicalVolume *logical_vacuum_space;

    // Physical volumes

    // Physical world
    G4VPhysicalVolume *physical_world;
    // Target body rear part
    G4VPhysicalVolume *physical_target_body_rear_part;
    // Target body front part
    G4VPhysicalVolume *physical_target_body_front_part;

    G4VPhysicalVolume *physical_water_cooler_alum;
    G4VPhysicalVolume *physical_water_flow;
    G4VPhysicalVolume *physical_copper_holder;
    G4VPhysicalVolume *physical_molybdenum100_tablet;
    G4VPhysicalVolume *physical_molybdenum98_tablet;
    G4VPhysicalVolume *physical_tablet_locker;
    G4VPhysicalVolume *physical_threaded_clamp;
    G4VPhysicalVolume *physical_helium_space;
    G4VPhysicalVolume *physical_vacuum_window;
    G4VPhysicalVolume *physical_vacuum_space;

    // Materials
    G4Material *air_material;
    G4Material *aluminium_material;
    G4Material *copper_material;
    G4Material *helium_material;
    G4Material *water_material;
    G4Material *molybdenum100_material;
    G4Material *vacuum_material;

    // Materials' parameters

    // helium
    static constexpr G4double helium_pressure =
        27579.0292 * pascal; // about 4 psi
    static constexpr G4double helium_density = 4.7 * std::pow(10, -2) * g / cm3;
    static constexpr G4double helium_temperature =
        (273.15 + 10.) * kelvin; // about 10 deg C
    // water
    static constexpr G4double water_density = 1. * g / cm3;
    static constexpr G4double water_temperature = (273.15 + 16.) * kelvin;
    static constexpr G4double water_pressure =
        725. * std::pow(10, 3) * pascal; // 725 kPa

    // molybdenum-100 isotope (100Mo)
    static constexpr G4double molybdenum100_enriched_density = 10.22 * g / cm3;
    // -------------------------------------------------------------------------------------------
    static constexpr G4double molybdenum100_abundance = 92.2 * perCent;
    static constexpr G4double molybdenum100_atomic_mass = 99.9074682 * g / mole;
    // -------------------------------------------------------------------------------------------
    static constexpr G4double molybdenum98_abundance = 3.16 * perCent;
    static constexpr G4double molybdenum98_atomic_mass = 97.9054041 * g / mole;
    // -------------------------------------------------------------------------------------------
    static constexpr G4double molybdenum97_abundance = 0.8 * perCent;
    static constexpr G4double molybdenum97_atomic_mass = 96.9060171 * g / mole;
    // -------------------------------------------------------------------------------------------
    static constexpr G4double molybdenum96_abundance = 1.28 * perCent;
    static constexpr G4double molybdenum96_atomic_mass = 95.90467488 * g / mole;
    // -------------------------------------------------------------------------------------------
    static constexpr G4double molybdenum95_abundance = 1.11 * perCent;
    static constexpr G4double molybdenum95_atomic_mass = 94.90583748 * g / mole;
    // -------------------------------------------------------------------------------------------
    static constexpr G4double molybdenum94_abundance = 0.57 * perCent;
    static constexpr G4double molybdenum94_atomic_mass = 93.9050841 * g / mole;
    // -------------------------------------------------------------------------------------------
    static constexpr G4double molybdenum92_abundance = 0.88 * perCent;
    static constexpr G4double molybdenum92_atomic_mass = 91.9068071 * g / mole;
    // -------------------------------------------------------------------------------------------

    // Geometry parameters

    // Solid world
    static constexpr G4bool check_overlaps = true;

    static constexpr G4double world_px = 150. * mm, world_py = 150. * mm,
                              world_pz = 500. * mm;

    static constexpr G4double world_position_x = 0. * mm;
    static constexpr G4double world_position_y = 0. * mm;
    static constexpr G4double world_position_z = 0. * mm;
    G4ThreeVector world_position;

    // Target body rear part
    static constexpr G4double target_body_rear_part_radius_outer = 25.11 * mm;
    static constexpr G4double target_body_rear_part_radius_inner = 0. * mm;
    static constexpr G4double target_body_rear_part_half_length =
        (99.10 - 20.09 - 3.00 - 5.00) *
        mm; // fixed in the scheme: 3 mm for water part & 5 for copper holder
            // baffle
    static constexpr G4double target_body_rear_part_phi_start = 0. * rad;
    static constexpr G4double target_body_rear_part_phi_delta =
        2 * std::numbers::pi * rad;

    static constexpr G4double target_body_rear_part_position_x = 0. * mm;
    static constexpr G4double target_body_rear_part_position_y = 0. * mm;
    static constexpr G4double target_body_rear_part_position_z =
        target_body_rear_part_half_length;

    G4ThreeVector target_body_rear_part_position;

    // Water cooler
    static constexpr G4double water_cooler_alum_radius_inner = 0. * mm;
    static constexpr G4double water_cooler_alum_radius_outer =
        target_body_rear_part_radius_outer;
    static constexpr G4double water_cooler_half_length = 1.5 * mm;
    // -------------------------------------------------------------------------------------------
    static constexpr G4double water_cooler_hollow_radius_inner = 0. * mm;
    static constexpr G4double water_cooler_hollow_radius_outer =
        water_cooler_half_length;
    static constexpr G4double water_cooler_hollow_half_length =
        water_cooler_alum_radius_outer;
    static constexpr G4double water_cooler_hollow_phi_start = 0. * rad;
    static constexpr G4double water_cooler_hollow_phi_delta =
        2 * std::numbers::pi * rad;
    // -------------------------------------------------------------------------------------------

    static constexpr G4double water_cooler_hollow_translation_x = 0. * mm;
    static constexpr G4double water_cooler_hollow_translation_y = 0. * mm;
    static constexpr G4double water_cooler_hollow_translation_z = 0. * mm;
    G4RotationMatrix *water_cooler_hollow_rotation;
    G4ThreeVector water_cooler_hollow_translation;

    G4Transform3D *water_cooler_hollow_transform;
    // -------------------------------------------------------------------------------------------

    static constexpr G4double water_cooler_phi_start = 0. * rad;
    static constexpr G4double water_cooler_phi_delta =
        2 * std::numbers::pi * rad;

    static constexpr G4double water_cooler_position_x = 0. * mm;
    static constexpr G4double water_cooler_position_y = 0. * mm;
    static constexpr G4double water_cooler_position_z =
        2 * target_body_rear_part_half_length + water_cooler_half_length;

    G4ThreeVector water_cooler_position;
    // -------------------------------------------------------------------------------------------

    // Target body front part
    static constexpr G4double target_body_front_part_baffle_radius_outer =
        target_body_rear_part_radius_outer;
    static constexpr G4double target_body_front_part_baffle_radius_inner =
        0. * mm;
    static constexpr G4double target_body_front_part_baffle_half_length =
        2.5 * mm;

    static constexpr G4double target_body_front_part_hollow_radius_outer =
        target_body_front_part_baffle_radius_outer;
    static constexpr G4double target_body_front_part_hollow_radius_inner =
        20.91 * mm;
    static constexpr G4double target_body_front_part_hollow_half_length =
        20.09 * mm;

    static constexpr G4double target_body_front_part_hollow_translation_x =
        0. * mm;
    static constexpr G4double target_body_front_part_hollow_translation_y =
        0. * mm;
    static constexpr G4double target_body_front_part_hollow_translation_z =
        target_body_front_part_baffle_half_length +
        target_body_front_part_hollow_half_length;

    G4RotationMatrix *target_body_front_part_hollow_rotation;
    G4ThreeVector target_body_front_part_hollow_translation;
    G4Transform3D *target_body_front_part_hollow_transform;

    static constexpr G4double target_body_front_part_start_phi = 0. * rad;
    static constexpr G4double target_body_front_part_delta_phi =
        2 * std::numbers::pi * rad;

    static constexpr G4double target_body_front_part_position_x = 0.;
    static constexpr G4double target_body_front_part_position_y = 0.;

    static constexpr G4double target_body_front_part_position_z =
        2 * (target_body_rear_part_half_length + water_cooler_half_length) +
        target_body_front_part_baffle_half_length;

    G4ThreeVector target_body_front_part_position;

    // Copper holder
    static constexpr G4double copper_holder_baffle_radius_inner = 0. * mm;
    static constexpr G4double copper_holder_baffle_radius_outer =
        target_body_front_part_hollow_radius_inner;
    static constexpr G4double copper_holder_baffle_half_length = 1. * mm;
    static constexpr G4double copper_holder_baffle_phi_start = 0. * rad;
    static constexpr G4double copper_holder_baffle_phi_delta =
        2 * std::numbers::pi * rad;

    static constexpr G4double copper_holder_hollow_radius_inner = 15. * mm;
    static constexpr G4double copper_holder_hollow_radius_outer =
        copper_holder_baffle_radius_outer;
    static constexpr G4double copper_holder_hollow_half_length = 1.5 * mm;
    static constexpr G4double copper_holder_hollow_phi_start = 0. * rad;
    static constexpr G4double copper_holder_hollow_phi_delta =
        2 * std::numbers::pi * rad;

    static constexpr G4double copper_holder_hollow_translation_x = 0. * mm;
    static constexpr G4double copper_holder_hollow_translation_y = 0. * mm;
    static constexpr G4double copper_holder_hollow_translation_z =
        copper_holder_hollow_half_length + copper_holder_baffle_half_length;

    G4ThreeVector copper_holder_hollow_translation;
    G4RotationMatrix *copper_holder_hollow_rotation;
    G4Transform3D *copper_holder_hollow_transform;

    static constexpr G4double copper_holder_position_x = 0. * mm;
    static constexpr G4double copper_holder_position_y = 0. * mm;
    static constexpr G4double copper_holder_position_z =
        2 * (target_body_rear_part_half_length + water_cooler_half_length +
             target_body_front_part_baffle_half_length) +
        copper_holder_baffle_half_length;

    G4ThreeVector copper_holder_position;

    // Molybdenum target tablet
    static constexpr G4double molybdenum100_tablet_radius_outer =
        copper_holder_hollow_radius_outer;
    static constexpr G4double molybdenum100_tablet_radius_inner = 0. * mm;
    static constexpr G4double molybdenum100_tablet_half_length =
        copper_holder_hollow_half_length;
    static constexpr G4double molybdenum100_tablet_phi_start = 0. * rad;
    static constexpr G4double molybdenum100_tablet_phi_delta =
        2 * std::numbers::pi * rad;
    // -------------------------------------------------------------------------------------------
    static constexpr G4double molybdenum100_tablet_position_x = 0. * mm;
    static constexpr G4double molybdenum100_tablet_position_y = 0. * mm;
    static constexpr G4double molybdenum100_tablet_position_z =
        2 * (target_body_rear_part_half_length + water_cooler_half_length +
             target_body_front_part_baffle_half_length +
             copper_holder_baffle_half_length) +
        molybdenum100_tablet_half_length;

    G4ThreeVector molybdenum100_tablet_position = G4ThreeVector(
        molybdenum100_tablet_position_x, molybdenum100_tablet_position_y,
        molybdenum100_tablet_position_z);

    // Aluminium vacuum window
    static constexpr G4double vacuum_window_px = 30.5 * mm;
    static constexpr G4double vacuum_window_py = 30.5 * mm;
    static constexpr G4double vacuum_window_pz = 0.025 * mm; // 25 um
    // -------------------------------------------------------------------------------------------
    static constexpr G4double vacuum_window_position_x = 0. * mm;
    static constexpr G4double vacuum_window_position_y = 0. * mm;
    static constexpr G4double vacuum_window_position_z =
        2 * (target_body_rear_part_half_length + water_cooler_half_length +
             target_body_front_part_baffle_half_length +
             target_body_front_part_hollow_half_length) +
        vacuum_window_pz + 10. * mm;

    G4ThreeVector vacuum_window_position;

    // Vacuum cubic space
    static constexpr G4double vacuum_space_px = vacuum_window_px;
    static constexpr G4double vacuum_space_py = vacuum_window_py;
    static constexpr G4double vacuum_space_pz = world_px - vacuum_window_pz;

    static constexpr G4double vacuum_space_position_x = 0. * mm;
    static constexpr G4double vacuum_space_position_y = 0. * mm;
    static constexpr G4double vacuum_space_position_z =
        2 * (target_body_rear_part_half_length + water_cooler_half_length +
             target_body_front_part_baffle_half_length +
             target_body_front_part_hollow_half_length + vacuum_window_pz) +
        10. * mm + vacuum_space_pz;

    G4ThreeVector vacuum_space_position;

    // Tablet locker
    static constexpr G4double tablet_locker_solid_radius_outer = 20.91 * mm;
    static constexpr G4double tablet_locker_solid_radius_inner = 0. * mm;
    static constexpr G4double tablet_locker_solid_half_length = 5. * mm;
    static constexpr G4double tablet_locker_padding_radius_outer = 20.91 * mm;
    static constexpr G4double tablet_locker_padding_radius_inner =
        16.46 * mm; // should be reconsidered
    // static constexpr G4double tablet_locker_padding_half_length =
    // molybdenum98_tablet_half_length + molybdenum100_tablet_half_length;
};

#endif // MOLYBDENUMDETECTORCONSTRUCTION_HH
