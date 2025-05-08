#include "MolybdenumPhysicsListGeneral.hh"
#include "G4BaryonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4DecayPhysics.hh"
#include "G4DeexPrecoParameters.hh"
#include "G4EmParameters.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4IonConstructor.hh"
// #include "G4IonElasticPhysics.hh"
// #include "G4IonPhysicsPHP.hh"
// #include "G4IonPhysicsXS.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4NuclearLevelData.hh"
#include "G4NuclideTable.hh"
#include "G4PhysListUtil.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4ShortLivedConstructor.hh"
// #include "G4StoppingPhysics.hh"
// #include "MolybdenumGammaNuclearPhysics.hh"
#include "G4Evaporation.hh"
#include "G4ExcitationHandler.hh"
#include "G4NeutronCaptureProcess.hh"
#include "G4NeutronHPCapture.hh"
#include "G4ProcessManager.hh"
#include "MolybdenumHadronInelasticPhysics.hh"
#include "G4HadronInelasticQBBC_ABLA.hh"
// #include "HadronPhysicsQGSP_INCL_ABLA.hh"

MolybdenumPhysicsListGeneral::MolybdenumPhysicsListGeneral() : G4VModularPhysicsList() {

    // G4ParticleTable* particle_table = G4ParticleTable::GetParticleTable();
    // // particle_table->SetReadiness();
    // // particle_table->SetVerboseLevel(2);
    // G4IonTable* ion_table = particle_table->GetIonTable();
    // ion_table->CreateAllIon();
    // ion_table->CreateAllIsomer();

    G4PhysListUtil::InitialiseParameters();
    // G4LossTableManager::Instance();

    constexpr G4double mean_life = 1. * CLHEP::second;
    G4NuclideTable::GetInstance()->SetMeanLifeThreshold(mean_life);
    G4NuclideTable::GetInstance()->SetLevelTolerance(.1 * CLHEP::eV);

    G4EmParameters::Instance()->SetDefaults();
    G4EmParameters::Instance()->SetAugerCascade(true);
    G4EmParameters::Instance()->SetDeexcitationIgnoreCut(true);

    G4DeexPrecoParameters* deex = G4NuclearLevelData::GetInstance()->GetParameters();
    deex->SetCorrelatedGamma(false);
    deex->SetStoreAllLevels(true);
    deex->SetStoreICLevelData(true);
    deex->SetIsomerProduction(true);
    deex->SetInternalConversionFlag(true);
    deex->SetDiscreteExcitationFlag(false);
    deex->SetMaxLifeTime(mean_life);
    deex->SetDeexChannelsType(fGEM); // not the Hauser-Feshbach model, extended Weisskopf-Ewing model
    deex->SetVerbose(1);
    // deex->SetLevelDensity(0.075);


    // electromagnetic physics
    RegisterPhysics(new G4EmStandardPhysics_option4(0));
    //
    // hadron elastic physics
    RegisterPhysics(new G4HadronElasticPhysicsHP(0));
    // RegisterPhysics(new G4HadronElasticPhysicsXS(2));
    //
    // hadron inelastic physics
    // auto* hadron_inelastic_inclxx = new G4HadronPhysicsINCLXX(1); // also needed to try on 1E8 events
    // RegisterPhysics(hadron_inelastic_inclxx); // 24
    // RegisterPhysics(new G4HadronPhysicsQGSP_BIC_HP(1)); // 9
    // RegisterPhysics(new G4HadronPhysicsQGSP_BERT(1)); // 0
    // RegisterPhysics(new G4HadronPhysicsQGSP_BIC_AllHP(1)); // 0
    auto* hadron_inelastic_qbbc = new G4HadronInelasticQBBC(1); // the best solution
    RegisterPhysics(hadron_inelastic_qbbc); // 28
    // RegisterPhysics(new G4HadronInelasticQBBC_ABLA(1)); // 0
    // RegisterPhysics(new G4HadronPhysicsShieldingLEND(1)); // haven't tried yet
    // G4VPhysicsConstructor* custom_hadronic_physics = new MolybdenumHadronInelasticPhysics("hadronInelastic");
    // custom_hadronic_physics->SetVerboseLevel(2);
    // RegisterPhysics(custom_hadronic_physics);
    // RegisterPhysics(HadronPhysicsQGSP_INCL_ABLA(2));
    //
    //
    // // ion elastic physics
    // RegisterPhysics(new G4IonElasticPhysics(1));
    //
    //
    // // ion inelastic physics
    // RegisterPhysics(new G4IonPhysicsXS(1));
    // RegisterPhysics(new G4IonPhysicsPHP(1));
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
    RegisterPhysics(new G4DecayPhysics(1));
    //
    //
    // radioactive decay physics
    auto* radioactive_decay_physics = new G4RadioactiveDecayPhysics(1);
    // auto* radioactive_decay_physics = new MolybdenumRadioactiveDecayPhysics("radioactiveDecay");
    RegisterPhysics(radioactive_decay_physics);
}

MolybdenumPhysicsListGeneral::~MolybdenumPhysicsListGeneral() = default;

// MolybdenumPhysicsListGeneral::~MolybdenumPhysicsListGeneral() {
//     delete electromagnetic_physics_list_;
//     delete hadron_physics_list_;
// }
//
void MolybdenumPhysicsListGeneral::ConstructParticle() {
    // G4VModularPhysicsList::ConstructParticle();

    G4BosonConstructor boson_constructor;
    G4BosonConstructor::ConstructParticle();

    G4LeptonConstructor lepton_constructor;
    G4LeptonConstructor::ConstructParticle();

    G4MesonConstructor meson_constructor;
    G4MesonConstructor::ConstructParticle();

    G4BaryonConstructor baryon_constructor;
    G4BaryonConstructor::ConstructParticle();

    G4IonConstructor ion_constructor;
    G4IonConstructor::ConstructParticle();

    G4ShortLivedConstructor short_lived_constructor;
    G4ShortLivedConstructor::ConstructParticle();
}

void MolybdenumPhysicsListGeneral::ConstructProcess() {
    G4VModularPhysicsList::ConstructProcess();
    // AddTransportation();
    G4ProcessManager* process_manager = G4Neutron::Neutron()->GetProcessManager();
    auto* neutron_capture_process     = new G4NeutronCaptureProcess();
    neutron_capture_process->RegisterMe(new G4NeutronHPCapture());
    process_manager->AddDiscreteProcess(neutron_capture_process);
}
