#include "MolybdenumHadronInelasticPhysics.hh"

#include <G4NuclearLevelData.hh>

#include "G4AblaInterface.hh"
#include "G4BertiniProtonBuilder.hh"
#include "G4BinaryCascade.hh"
#include "G4CascadeInterface.hh"
#include "G4ChipsNeutronInelasticXS.hh"
#include "G4ChipsProtonInelasticXS.hh"
#include "G4DeexPrecoParameters.hh"
#include "G4Evaporation.hh"
#include "G4ExcitationHandler.hh"
#include "G4HadronInelasticProcess.hh"
#include "G4INCLXXInterface.hh"
#include "G4IonQMDPhysics.hh"
#include "G4Neutron.hh"
#include "G4NeutronHPInelastic.hh"
#include "G4NeutronInelasticXS.hh"
#include "G4NuclearLevelData.hh"
#include "G4ParticleHPInelasticXS.hh"
#include "G4ParticleInelasticXS.hh"
#include "G4PreCompoundModel.hh"
#include "G4ProcessManager.hh"
#include "G4Proton.hh"
#include "G4QMDReaction.hh"
#include "G4SystemOfUnits.hh"


MolybdenumHadronInelasticPhysics::MolybdenumHadronInelasticPhysics(const G4String& name = "hadronInelastic") :
    G4VPhysicsConstructor(name), verbose_level_(2){};

void MolybdenumHadronInelasticPhysics::ConstructProcess() {

    G4DeexPrecoParameters* deex = G4NuclearLevelData::GetInstance()->GetParameters();
    deex->SetCorrelatedGamma(false);
    deex->SetStoreAllLevels(true);
    deex->SetStoreICLevelData(true);
    deex->SetIsomerProduction(true);
    deex->SetInternalConversionFlag(true);
    deex->SetDiscreteExcitationFlag(true);
    deex->SetMaxLifeTime(1. * CLHEP::second);
    deex->SetDeexChannelsType(fEvaporation); // not the Hauser-Feshbach model, extended Weisskopf-Ewing model
    deex->SetVerbose(2);

    // Proton inelastic process
    auto* proton_inelastic = new G4HadronInelasticProcess("protonInelastic", G4Proton::ProtonDefinition());

    // Excitation handler
    auto* excitation_handler = new G4ExcitationHandler();
    excitation_handler->SetEvaporation(new G4Evaporation(), true);
    excitation_handler->SetPhotonEvaporation(nullptr);
    excitation_handler->SetDeexChannelsType(fEvaporation);

    // Pre-Compound model for de-excitation
    G4VPreCompoundModel* proton_pre_compound = new G4PreCompoundModel(excitation_handler);

    proton_pre_compound->SetExcitationHandler(excitation_handler);
    proton_pre_compound->SetVerboseLevel(verbose_level_);
    // Binary cascade model with attached pre-compound model
    G4VIntraNuclearTransportModel* proton_binary_cascade = new G4BinaryCascade(proton_pre_compound);
    proton_binary_cascade->SetVerboseLevel(verbose_level_);

    // Bertini cascade model
    // G4VIntraNuclearTransportModel* proton_bertini_cascade = new G4CascadeInterface();
    // proton_bertini_cascade->SetDeExcitation(proton_pre_compound);

    // INCLXX cascade model (+ ABLA de-excitation)
    // auto* proton_inclxx_cascade = new G4INCLXXInterface();
    // proton_inclxx_cascade->SetMinEnergy(0.);
    // proton_inclxx_cascade->SetMaxEnergy(3. * GeV);
    // G4VPreCompoundModel* abla_interface = new G4AblaInterface();
    // proton_inclxx_cascade->SetDeExcitation(abla_interface);

    // QMD reaction model
    // auto* proton_qmd_reaction = new G4QMDReaction();
    // proton_qmd_reaction->SetMinEnergy(0.);
    // proton_qmd_reaction->SetMaxEnergy(3. * GeV);
    // proton_qmd_reaction->SetVerboseLevel(verbose_level_);

    // Register the cascade model with the inelastic process for protons
    // proton_inelastic->RegisterMe(proton_bertini_cascade);
    proton_inelastic->RegisterMe(proton_binary_cascade);
    // proton_inelastic->RegisterMe(proton_qmd_reaction);
    // proton_inelastic->RegisterMe(proton_inclxx_cascade);

    // Create a XS dataset
    G4VCrossSectionDataSet* chips_proton_inelastic_xs = new G4ChipsProtonInelasticXS();
    G4VCrossSectionDataSet* proton_hp_inelastic_xs    = new G4ParticleHPInelasticXS(G4Proton::ProtonDefinition());
    G4VCrossSectionDataSet* proton_inelastic_xs       = new G4ParticleInelasticXS(G4Proton::ProtonDefinition());

    // Add XS dataset
    proton_inelastic->AddDataSet(proton_inelastic_xs);
    // proton_inelastic->AddDataSet(chips_proton_inelastic_xs);

    // Attach the process to the proton's process manager
    G4ProcessManager* proton_process_manager = G4Proton::ProtonDefinition()->GetProcessManager();
    if (proton_process_manager)
        proton_process_manager->AddDiscreteProcess(proton_inelastic);


    // ========================================================================================================================
    // =============================================== NEUTRONS
    // ========================================================================================================================

    // Neutron inelastic process
    auto* neutron_inelastic = new G4HadronInelasticProcess("neutronInelastic", G4Neutron::NeutronDefinition());

    // Low-energy HP model for neutrons (E < 20 MeV)
    auto* neutron_hp_model = new G4NeutronHPInelastic();
    neutron_hp_model->SetMinEnergy(0.);
    neutron_hp_model->SetMaxEnergy(20. * MeV);

    // Pre-Compound model for de-excitation
    G4VPreCompoundModel* neutron_pre_compound = new G4PreCompoundModel(excitation_handler);

    // Cascade model for neutrons above 20 MeV, using Pre-Compound for de-excitation
    G4VIntraNuclearTransportModel* neutron_binary_cascade = new G4BinaryCascade(neutron_pre_compound);
    neutron_binary_cascade->SetMinEnergy(19.9 * MeV);
    neutron_binary_cascade->SetMaxEnergy(5. * GeV);

    // Register both HP and BC models. Geant4 will chose the appropriate one by energy
    neutron_inelastic->RegisterMe(neutron_hp_model);
    neutron_inelastic->RegisterMe(neutron_binary_cascade);

    G4VCrossSectionDataSet* neutron_inelastic_xs = new G4NeutronInelasticXS();

    // Add XS dataset
    neutron_inelastic->AddDataSet(neutron_inelastic_xs);

    // Attach the proces to the neutron's process manager
    G4ProcessManager* neutron_process_manager = G4Neutron::NeutronDefinition()->GetProcessManager();
    if (neutron_process_manager)
        neutron_process_manager->AddDiscreteProcess(neutron_inelastic);
}

void MolybdenumHadronInelasticPhysics::SetVerboseLevel(const G4int value) {
    G4VPhysicsConstructor::SetVerboseLevel(value);
    verbose_level_ = value;
}
