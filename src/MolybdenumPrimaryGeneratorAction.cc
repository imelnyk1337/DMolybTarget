#include "MolybdenumPrimaryGeneratorAction.hh"
#include "MolybdenumDetectorConstruction.hh"

MolybdenumPrimaryGeneratorAction::MolybdenumPrimaryGeneratorAction() :
    particle_energy_(0), beam_radius_(0), beam_current_(0), beam_max_theta_(0) {
    particle_source_     = new G4GeneralParticleSource();
    particle_name_       = "proton";
    particle_table_      = G4ParticleTable::GetParticleTable();
    particle_definition_ = particle_table_->FindParticle(particle_name_);
    particle_source_->SetParticleDefinition(particle_definition_);

    // G4cout << "Number of source: " << particle_source_->GetNumberofSource() << G4endl;
    const G4SingleParticleSource* current_source = particle_source_->GetCurrentSource();

    // set proton energy
    G4SPSEneDistribution* current_source_energy_distribution = current_source->GetEneDist();
    current_source_energy_distribution->SetEnergyDisType("Mono");
    current_source_energy_distribution->SetMonoEnergy(11. * MeV);
    current_source_energy_distribution->SetVerbosity(0);
    // set beam position
    G4SPSPosDistribution* current_source_position_distribution = current_source->GetPosDist();
    current_source_position_distribution->SetPosDisType("Beam");
    current_source_position_distribution->SetPosDisShape("Circle");
    constexpr G4double beam_position_z = MolybdenumDetectorConstruction::vacuum_window_position_z -
        MolybdenumDetectorConstruction::vacuum_window_half_length + 10. * mm;
    SetBeamStartPositionZ(beam_position_z);
    // G4cout << "Beam starting z position: " << GetBeamStartPositionZ() << G4endl;
    current_source_position_distribution->SetCentreCoords(G4ThreeVector(0., 0., GetBeamStartPositionZ()));
    current_source_position_distribution->SetRadius0(0. * mm);
    current_source_position_distribution->SetRadius(10. * mm); // 3. mm
    // set angular distribution to create a parallel beam
    G4SPSAngDistribution* current_source_angular_distribution = current_source->GetAngDist();
    current_source_angular_distribution->SetAngDistType("beam2d");
    current_source_angular_distribution->SetMaxTheta(0. * deg);
    current_source_angular_distribution->SetParticleMomentumDirection(G4ThreeVector(0., 0., -1.));
}

MolybdenumPrimaryGeneratorAction::~MolybdenumPrimaryGeneratorAction() { // I = q/ t ->
    delete particle_source_;
    delete particle_table_;
    delete particle_definition_;
}

void MolybdenumPrimaryGeneratorAction::SetBeamStartPositionZ(const G4double& position) {
    beam_start_position_z_ = position;
}

G4double MolybdenumPrimaryGeneratorAction::GetBeamStartPositionZ() const { return beam_start_position_z_; }


void MolybdenumPrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    constexpr G4double beam_current_amperes = 5.E-6; // 5 uA
    constexpr G4double event_time           = 1.E-9; // s;
    const G4double particle_charge          = particle_source_->GetParticleDefinition()->GetPDGCharge() * 1.6E-19;
    const auto number_of_particles = static_cast<int>(std::abs(beam_current_amperes * event_time / particle_charge));
    // G4cout << "=========== Number of protons per event: " << number_of_particles << G4endl;

    particle_source_->SetCurrentSourceIntensity(1);
    particle_source_->SetNumberOfParticles(number_of_particles);
    particle_source_->GeneratePrimaryVertex(event);
}
