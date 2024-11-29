#ifndef CONTROLLERWORKER_H
#define CONTROLLERWORKER_H

#include "Package.h"

class ControllerWorker : public Process {
public:
    void Behavior() override;  // Metoda pro zpracování balíků
};

#endif  // CONTROLLERWORKER_H
