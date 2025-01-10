#include "MolybdenumPhysicsList.hh"

MolybdenumPhysicsList::MolybdenumPhysicsList() {
    // RegisterPhysics(new G4HadronPhysicsQGSP_BIC_HP());
    RegisterPhysics(new G4EmStandardPhysics_option3());
    RegisterPhysics(new G4HadronPhysicsQGSP_BIC_AllHP());
}

MolybdenumPhysicsList::~MolybdenumPhysicsList() = default;

