#ifndef MOLYBDENUMGAMMANUCLEARPHYSICS_HH
#define MOLYBDENUMGAMMANUCLEARPHYSICS_HH

#include "G4VPhysicsConstructor.hh"


class MolybdenumGammaNuclearPhysics final : public G4VPhysicsConstructor {
    public:
    explicit MolybdenumGammaNuclearPhysics(const std::string&);
    ~MolybdenumGammaNuclearPhysics() override;
    void ConstructParticle() override {};
    void ConstructProcess() override;
};

#endif // MOLYBDENUMGAMMANUCLEARPHYSICS_HH
