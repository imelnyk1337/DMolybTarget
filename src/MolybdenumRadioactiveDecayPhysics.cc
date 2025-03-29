#include "MolybdenumRadioactiveDecayPhysics.hh"
#include "G4DeexPrecoParameters.hh"
#include "G4GenericIon.hh"
#include "G4NuclearLevelData.hh"
#include "G4NuclideTable.hh"
#include "G4Radioactivation.hh"
#include "G4Nucleus.hh"
MolybdenumRadioactiveDecayPhysics::MolybdenumRadioactiveDecayPhysics(const G4String& name) :
    G4VPhysicsConstructor(name) {
    G4DeexPrecoParameters* deexcitation = G4NuclearLevelData::GetInstance()->GetParameters();
    deexcitation->SetStoreICLevelData(true);
    deexcitation->SetMaxLifeTime(G4NuclideTable::GetInstance()->GetThresholdOfHalfLife() / std::log(2.));
    deexcitation->SetIsomerProduction(true);
    deexcitation->SetCorrelatedGamma(false);
}

void MolybdenumRadioactiveDecayPhysics::ConstructParticle() {
    G4GenericIon::GenericIon();
}

void MolybdenumRadioactiveDecayPhysics::ConstructProcess() {
    auto* radioactive_decay = new G4Radioactivation();
    radioactive_decay->SetARM(false);
    G4PhysicsListHelper::GetPhysicsListHelper()->RegisterProcess(radioactive_decay, G4GenericIon::GenericIon());
}
