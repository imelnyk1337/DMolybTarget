#include "MolybdenumPhysicsListGeneral.hh"

// #include <G4ProcessManager.hh>

#include "G4BaryonConstructor.hh"
#include "G4BosonConstructor.hh"
// #include "G4ChipsProtonInelasticXS.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4HadronElasticPhysicsXS.hh"
// #include "G4HadronInelasticQBBC.hh"
// #include "G4HadronPhysicsFTFP_BERT_HP.hh"
// #include "G4HadronPhysicsFTF_BIC.hh"
// #include "G4HadronPhysicsINCLXX.hh"
// #include "G4HadronPhysicsQGSP_BIC.hh"
// #include "G4HadronPhysicsQGSP_BIC_AllHP.hh"
// #include "G4HadronPhysicsQGSP_BIC_HP.hh"
// #include "G4HadronPhysicsQGSP_FTFP_BERT.hh"
#include "G4IonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
// #include "G4NeutronCaptureProcess.hh"
// #include "G4NeutronHPCapture.hh"
// #include "G4NuclideTable.hh"
#include "G4ShortLivedConstructor.hh"
// #include "MolybdenumGammaNuclearPhysics.hh"
// #include "G4HadronPhysicsQGSP"
// #include "G4HadronPhysicsShieldingLEND.hh"
// #include "G4HadronicParameters.hh"
// #include "G4DeexPrecoParameters.hh"
// #include "G4NuclearLevelData.hh"
// #include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
// #include "G4IonQMDPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "MolybdenumHadronInelasticPhysics.hh"


MolybdenumPhysicsListGeneral::MolybdenumPhysicsListGeneral() : G4VModularPhysicsList() {

    // G4PhysListUtil::InitialiseParameters();
    // G4LossTableManager::Instance();

    // G4NuclideTable::GetInstance()->SetMeanLifeThreshold(5. * 3600. * CLHEP::second);
    // G4NuclideTable::GetInstance()->SetLevelTolerance(.1 * CLHEP::eV);
    // G4DeexPrecoParameters* deex = G4NuclearLevelData::GetInstance()->GetParameters();
    // deex->SetCorrelatedGamma(false);
    // deex->SetStoreAllLevels(true);
    // deex->SetIsomerProduction(true);
    // deex->SetInternalConversionFlag(true);
    // deex->SetDiscreteExcitationFlag(true);
    // deex->SetLevelDensityFlag(true);
    // G4cout << "Level density flag: " << deex->GetLevelDensityFlag() << G4endl;
    // G4cout << "Isomer production: " << deex->IsomerProduction() << G4endl;

    // deex->SetMaxLifeTime(1. * CLHEP::second);
    // deex->SetLevelDensity(10.); // 0.075
    // deex->SetDeexModelType(3);


    // electromagnetic physics
    RegisterPhysics(new G4EmStandardPhysics_option4(0));
    //
    // hadron elastic physics
    RegisterPhysics(new G4HadronElasticPhysicsHP(1));
    // RegisterPhysics(new G4HadronElasticPhysicsXS(2));
    //
    // hadron inelastic physics
    // RegisterPhysics(new G4HadronPhysicsINCLXX(1));  // 2
    // RegisterPhysics(new G4HadronPhysicsQGSP_BIC_HP(1)); // 2
    // RegisterPhysics(new G4HadronPhysicsQGSP_BERT(1)); // 0
    // RegisterPhysics(new G4HadronPhysicsQGSP_BIC_AllHP(1));
    // RegisterPhysics(new G4HadronInelasticQBBC(1)); // 7
    // RegisterPhysics(new G4HadronPhysicsShieldingLEND(1));
    G4VPhysicsConstructor* custom_hadronic_physics = new MolybdenumHadronInelasticPhysics("hadronInelastic");
    custom_hadronic_physics->SetVerboseLevel(2);
    RegisterPhysics(custom_hadronic_physics);
    //
    //
    // // ion elastic physics
    // RegisterPhysics(new G4IonElasticPhysics(1));
    //
    //
    // // ion inelastic physics
    // RegisterPhysics(new G4IonPhysicsXS(1));
    //
    //
    // // stopping physics
    // RegisterPhysics(new G4StoppingPhysics(1));
    //
    //
    // gamma-nuclear physics
    // RegisterPhysics(new MolybdenumGammaNuclearPhysics("gamma"));
    //
    //
    // decay physics
    // RegisterPhysics(new G4DecayPhysics(1));
    //
    //
    // radioactive decay physics
    G4RadioactiveDecayPhysics* radioactive_decay_physics = new G4RadioactiveDecayPhysics(2);
    RegisterPhysics(radioactive_decay_physics);
}

MolybdenumPhysicsListGeneral::~MolybdenumPhysicsListGeneral() = default;

// MolybdenumPhysicsListGeneral::~MolybdenumPhysicsListGeneral() {
//     delete electromagnetic_physics_list_;
//     delete hadron_physics_list_;
// }
//
void MolybdenumPhysicsListGeneral::ConstructParticle() {
    G4VModularPhysicsList::ConstructParticle();
    G4BosonConstructor pBosonConstructor;
    G4BosonConstructor::ConstructParticle();

    G4LeptonConstructor pLeptonConstructor;
    G4LeptonConstructor::ConstructParticle();

    G4MesonConstructor pMesonConstructor;
    G4MesonConstructor::ConstructParticle();

    G4BaryonConstructor pBaryonConstructor;
    G4BaryonConstructor::ConstructParticle();

    G4IonConstructor pIonConstructor;
    G4IonConstructor::ConstructParticle();

    G4ShortLivedConstructor pShortLivedConstructor;
    G4ShortLivedConstructor::ConstructParticle();
}

// void MolybdenumPhysicsListGeneral::ConstructProcess() {
//     G4VModularPhysicsList::ConstructProcess();
//     // AddTransportation();
//     G4ProcessManager* process_manager = G4Neutron::Neutron()->GetProcessManager();
//     auto* neutron_capture_process     = new G4NeutronCaptureProcess();
//     neutron_capture_process->RegisterMe(new G4NeutronHPCapture());
//     process_manager->AddDiscreteProcess(neutron_capture_process);
// }
