#ifndef MOLYBDENUMPHYSICSLIST_HH
#define MOLYBDENUMPHYSICSLIST_HH

#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronPhysicsQGSP_BIC_AllHP.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4VModularPhysicsList.hh"


class MolybdenumPhysicsList final : public G4VModularPhysicsList {
    public:
    MolybdenumPhysicsList();
    ~MolybdenumPhysicsList() override;
};

#endif // MOLYBDENUMPHYSICSLIST_HH
