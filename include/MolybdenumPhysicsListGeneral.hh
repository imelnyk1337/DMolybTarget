#ifndef MOLYBDENUMPHYSICSLISTGENERAL_HH
#define MOLYBDENUMPHYSICSLISTGENERAL_HH

#include "G4VModularPhysicsList.hh"


class MolybdenumPhysicsListGeneral final : public G4VModularPhysicsList {
    public:
    // void RegisterPhysics(QBBC_ABLA* qbbc_abla);
    MolybdenumPhysicsListGeneral();
    ~MolybdenumPhysicsListGeneral() override;
    void ConstructParticle() override;
    void ConstructProcess() override;
    //
    // private:
    // G4VPhysicsConstructor* electromagnetic_physics_list_;
    // G4VPhysicsConstructor* hadron_physics_list_;
};

#endif // MOLYBDENUMPHYSICSLISTGENERAL_HH
