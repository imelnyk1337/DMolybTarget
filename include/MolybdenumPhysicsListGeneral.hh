#ifndef MOLYBDENUMPHYSICSLISTGENERAL_HH
#define MOLYBDENUMPHYSICSLISTGENERAL_HH

// #include "G4DecayPhysics.hh"
// #include "G4DeexPrecoParameters.hh"
// #include "G4Deuteron.hh"
// #include "G4Electron.hh"
#include "G4EmStandardPhysics_option3.hh"
// #include "G4Gamma.hh"
#include "G4HadronPhysicsQGSP_BIC_AllHP.hh"
#include "G4LossTableManager.hh"
// #include "G4Neutron.hh"
// #include "G4Nucleus.hh"
// #include "G4Positron.hh"
// #include "G4Proton.hh"
// #include "G4RadioactiveDecay.hh"
// #include "G4RadioactiveDecayPhysics.hh"
#include "G4VModularPhysicsList.hh"


class MolybdenumPhysicsListGeneral final : public G4VModularPhysicsList {
    public:
    MolybdenumPhysicsListGeneral();
    ~MolybdenumPhysicsListGeneral() override;
    // void ConstructParticle() override;
    // void ConstructProcess() override;
    //
    // private:
    // G4VPhysicsConstructor* electromagnetic_physics_list_;
    // G4VPhysicsConstructor* hadron_physics_list_;
};

#endif // MOLYBDENUMPHYSICSLISTGENERAL_HH
