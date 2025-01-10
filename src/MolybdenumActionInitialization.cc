#include "MolybdenumActionInitialization.hh"

MolybdenumActionInitialization::MolybdenumActionInitialization() = default;
MolybdenumActionInitialization::~MolybdenumActionInitialization() = default;

void MolybdenumActionInitialization::Build() const {
    MolybdenumPrimaryGeneratorAction* primary_generator = new MolybdenumPrimaryGeneratorAction();
    SetUserAction(primary_generator);
}

void MolybdenumActionInitialization::BuildForMaster() const {}