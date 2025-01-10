#ifndef MOLYBDENUMPRIMARYACTIONINITIALIZATION_HH
#define MOLYBDENUMPRIMARYACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "MolybdenumPrimaryGeneratorAction.hh"

class MolybdenumActionInitialization final : public G4VUserActionInitialization {
    public:
    MolybdenumActionInitialization();
    ~MolybdenumActionInitialization() override;

    void Build() const override;
    void BuildForMaster() const override;
};

#endif // MOLYBDENUMPRIMARYACTIONINITIALIZATION_HH
