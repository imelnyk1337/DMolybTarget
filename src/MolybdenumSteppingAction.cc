#include "MolybdenumSteppingAction.hh"
#include "G4HadronicProcess.hh"
#include "G4VProcess.hh"
#include "MolybdenumRun.hh"

MolybdenumSteppingAction::MolybdenumSteppingAction() = default;

MolybdenumSteppingAction::~MolybdenumSteppingAction() = default;

void MolybdenumSteppingAction::UserSteppingAction(const G4Step* step) {
    G4IonTable* ionTable = G4ParticleTable::GetParticleTable()->GetIonTable();

    auto* molybdenum_run = dynamic_cast<MolybdenumRun*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    const G4Track* track = step->GetTrack();
    const G4ParticleDefinition* particle_definition = track->GetDefinition();
    const G4String particle_type                    = particle_definition->GetParticleType();
    const G4String particle_name                    = particle_definition->GetParticleName();
    const G4String physical_volume_name             = track->GetVolume()->GetName();
    // now we got id of each nucleus and its physics name, it will help us to track nuclear reactions

    // working with unstable isotopes
    const G4bool is_nucleus = (particle_name != "proton") && (particle_name != "neutron") && (particle_name != "e-") &&
        (particle_name != "e+") && (particle_name != "gamma");

    if (is_nucleus && !(particle_definition->GetPDGStable()) && track->GetCurrentStepNumber() == 1 &&
        (physical_volume_name == "physical_molybdenum100_tablet" ||
         physical_volume_name == "physical_molybdenum98_tablet")) {

        molybdenum_run->RegisterIsotopeID(track->GetTrackID(), particle_name);

        const std::string name    = track->GetParticleDefinition()->GetParticleName();
        const G4VProcess* process = track->GetCreatorProcess();

        // if (name == "Tc99[142.683]")
        //     G4cout << track->GetParticleDefinition()->GetPDGSpin() << G4endl;


        // const G4VPhysicalVolume* volume     = track->GetVolume();
        // G4VProcess* process_nonconst        = const_cast<G4VProcess*>(process);
        // G4HadronicProcess* hadronic_process = dynamic_cast<G4HadronicProcess*>(process_nonconst);
        //
        // if (hadronic_process) {
        //     const G4Isotope* isotope = hadronic_process->GetTargetIsotope();
        //     G4cout << isotope->GetName() << G4endl;
        // }

        // G4cout << "New isotope produced: " << name << " (" << Z << ", " << A << ") with " << half_life << std::endl;
        // G4cout << "Track: " << track->GetParticleDefinition()->GetParticleName() << " created by "
        //        << process->GetProcessName() << " process in the " << volume->GetName()
        //        << ", number of secondaries in current step: " << step->GetNumberOfSecondariesInCurrentStep() <<
        //        G4endl;
        // const std::vector<const G4Track*>* secondaries_pointer = step->GetSecondaryInCurrentStep();

        // const G4double production_time = track->GetGlobalTime() * 1E-9; // seconds

        // G4cout << "Production time: " << production_time << G4endl;

        // for (std::size_t i = 0; i < secondaries_pointer->size(); ++i) {
        //     const G4Track* secondary_track                   = secondaries_pointer->at(i);
        //     const G4ParticleDefinition* secondary_definition = secondary_track->GetParticleDefinition();
        //     G4cout << "     Secondary #" << i << ": " << secondary_definition->GetParticleName()
        //            << " with K.E. = " << secondary_track->GetKineticEnergy() << G4endl;
        // }
        // track->GetParticleDefinition()->Get
        molybdenum_run->CountIsotope(name);
        molybdenum_run->RegisterProcess(process->GetProcessName(), name);
        // G4cout << "Produced " << name << " is registered;" << G4endl;
    }
}
