#include "MolybdenumGammaNuclearPhysics.hh"
#include "G4CascadeInterface.hh"
#include "G4Gamma.hh"
#include "G4HadronInelasticProcess.hh"
#include "G4LowEGammaNuclearModel.hh"
#include "G4PhotoNuclearCrossSection.hh"
#include "G4ProcessManager.hh"
#include "G4SystemOfUnits.hh"

MolybdenumGammaNuclearPhysics::MolybdenumGammaNuclearPhysics(const std::string& name = "gamma") :
    G4VPhysicsConstructor(name) {}

MolybdenumGammaNuclearPhysics::~MolybdenumGammaNuclearPhysics() = default;

void MolybdenumGammaNuclearPhysics::ConstructProcess() {
    auto* process = new G4HadronInelasticProcess("photonNuclear", G4Gamma::Definition());
    process->AddDataSet(new G4PhotoNuclearCrossSection());

    constexpr G4double Emax1 = 200 * MeV, Emax2 = 10 * GeV;

    if constexpr (Emax1 > 0.) { // model 1
        auto* model1 = new G4LowEGammaNuclearModel();
        model1->SetMaxEnergy(Emax1);
        process->RegisterMe(model1);
    }

    if constexpr (Emax2 > 0.) { // model 2
        auto* model2             = new G4CascadeInterface();
        constexpr G4double Emin2 = std::max(Emax1 - 1 * MeV, 0.);
        model2->SetMinEnergy(Emin2);
        model2->SetMaxEnergy(Emax2);
        process->RegisterMe(model2);
    }

    G4ProcessManager* pManager = G4Gamma::Gamma()->GetProcessManager();
    pManager->AddDiscreteProcess(process);
}
