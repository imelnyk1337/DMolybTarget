#include "MolybdenumPhysicsList.hh"

MolybdenumPhysicsList::MolybdenumPhysicsList() {
    RegisterPhysics(new G4EmStandardPhysics_option3());
    RegisterPhysics(new G4HadronInelasticQBBC_ABLA());
    RegisterPhysics(new G4HadronPhysicsQGSP_BERT());
}

MolybdenumPhysicsList::~MolybdenumPhysicsList() = default;

