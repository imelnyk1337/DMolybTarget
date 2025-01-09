#ifndef MOLYBDENUMPRIMARYGENERATORACTION_HH
#define MOLYBDENUMPRIMARYGENERATORACTION_HH

#include "G4GeneralParticleSource.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleTable.hh"


class MolybdenumPrimaryGeneratorAction final : public G4VUserPrimaryGeneratorAction {

    public:
    MolybdenumPrimaryGeneratorAction();
    ~MolybdenumPrimaryGeneratorAction() override;

    private:
    G4GeneralParticleSource* particle_source_;
    G4ParticleDefinition* particle_def_;
    G4double particle_energy_; // 11 MeV
    G4double beam_current_; // 5 uA
    std::string beam_shape_; // Circle
    G4double beam_radius_;
    std::string beam_energy_distribution_type_; // Mono
    std::string beam_angular_distribution_type_; // iso
};

#endif // MOLYBDENUMPRIMARYGENERATORACTION_HH
