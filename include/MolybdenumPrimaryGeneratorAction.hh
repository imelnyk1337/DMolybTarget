#ifndef MOLYBDENUMPRIMARYGENERATORACTION_HH
#define MOLYBDENUMPRIMARYGENERATORACTION_HH

#include "G4GeneralParticleSource.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4SingleParticleSource.hh"
#include "G4SystemOfUnits.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "MolybdenumDetectorConstruction.hh"


class MolybdenumPrimaryGeneratorAction final : public G4VUserPrimaryGeneratorAction {
    friend class MolybdenumDetectorConstruction;

    public:
    MolybdenumPrimaryGeneratorAction();
    ~MolybdenumPrimaryGeneratorAction() override;
    void GeneratePrimaries(G4Event*) override;
    void SetBeamStartPositionZ(const G4double&);
    G4double GetBeamStartPositionZ() const;

    private:
    G4GeneralParticleSource* particle_source_;
    G4ParticleTable* particle_table_;
    G4ParticleDefinition* particle_definition_;
    std::string particle_name_;
    G4double particle_energy_; // 11 MeV
    std::string beam_position_distribution_type_; // Beam
    std::string beam_position_distribution_shape_; // Circle
    G4double beam_radius_;
    G4double beam_start_position_z_{};
    G4double beam_current_; // 5 uA
    std::string beam_energy_distribution_type_; // Mono
    std::string beam_angular_distribution_type_; // iso
    G4double beam_max_theta_; // 0. * rad -- collimated beam
};

#endif // MOLYBDENUMPRIMARYGENERATORACTION_HH
