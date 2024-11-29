#ifndef LOADERWORKER_H
#define LOADERWORKER_H

#include "globals.h"
#include "Package.h"
#include "Vehicle.h"  // Propojení s vozidlem

class LoaderWorker : public Process {
public:
    void Behavior() override;  // Metoda pro nakládku balíků do vozidel
};

#endif  // LOADERWORKER_H
