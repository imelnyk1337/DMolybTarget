#ifndef MOLYBDENUMRADIOACTIVEDECAYPHYSICS_HH
#define MOLYBDENUMRADIOACTIVEDECAYPHYSICS_HH

#include "G4VPhysicsConstructor.hh"

class MolybdenumRadioactiveDecayPhysics final : public G4VPhysicsConstructor {
    public:
    explicit MolybdenumRadioactiveDecayPhysics(const G4String&);
    ~MolybdenumRadioactiveDecayPhysics() override = default;

    void ConstructParticle() override;
    void ConstructProcess() override;
};

#endif // MOLYBDENUMRADIOACTIVEDECAYPHYSICS_HH
