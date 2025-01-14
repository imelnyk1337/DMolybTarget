#include "MolybdenumPhysicsListGeneral.hh"

MolybdenumPhysicsListGeneral::MolybdenumPhysicsListGeneral() : G4VModularPhysicsList() {
    RegisterPhysics(new G4EmStandardPhysics_option3());
    RegisterPhysics(new G4HadronPhysicsQGSP_BIC_AllHP());
    // RegisterPhysics(new G4HadronPhysicsFTFP_BERT_HP());

    G4LossTableManager::Instance();

    // EM physics list
    // electromagnetic_physics_list_ = new G4EmStandardPhysics_option3(1);
    // hadron_physics_list_          = new G4HadronPhysicsQGSP_BIC_AllHP(1);
}

MolybdenumPhysicsListGeneral::~MolybdenumPhysicsListGeneral() = default;

// MolybdenumPhysicsListGeneral::~MolybdenumPhysicsListGeneral() {
//     delete electromagnetic_physics_list_;
//     delete hadron_physics_list_;
// }
//
void MolybdenumPhysicsListGeneral::ConstructParticle() {
    G4VModularPhysicsList::ConstructParticle();
    // G4Proton::ProtonDefinition();
    // G4Neutron::NeutronDefinition();
    // G4Gamma::GammaDefinition();
    // G4Electron::ElectronDefinition();
    // G4Positron::PositronDefinition();
}

void MolybdenumPhysicsListGeneral::ConstructProcess() {
    // AddTransportation();
    G4VModularPhysicsList::ConstructProcess();
    // electromagnetic_physics_list_->ConstructProcess();
    // hadron_physics_list_->ConstructProcess();
}
