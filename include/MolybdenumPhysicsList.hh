#ifndef MOLYBDENUMPHYSICSLIST_HH
#define MOLYBDENUMPHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4HadronInelasticQBBC_ABLA.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4RadioactiveDecay.hh"
#include "G4Radioactivation.hh"

class MolybdenumPhysicsList final : public G4VModularPhysicsList {
public:
    MolybdenumPhysicsList();
    ~MolybdenumPhysicsList() override;

};

#endif //MOLYBDENUMPHYSICSLIST_HH
