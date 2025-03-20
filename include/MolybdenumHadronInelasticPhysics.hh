#ifndef MOLYBDENUMHADRONINELASTICPHYSICS_HH
#define MOLYBDENUMHADRONINELASTICPHYSICS_HH

#include "G4VPhysicsConstructor.hh"

class MolybdenumHadronInelasticPhysics final : public G4VPhysicsConstructor {
    public:
    explicit MolybdenumHadronInelasticPhysics(const G4String&);
    ~MolybdenumHadronInelasticPhysics() override = default;
    void ConstructProcess() override;
    void ConstructParticle() override {};
    inline void SetVerboseLevel(const G4int);
    private:
    G4int verbose_level_;
};


#endif // MOLYBDENUMHADRONINELASTICPHYSICS_HH
