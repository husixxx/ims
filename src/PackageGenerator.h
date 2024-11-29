#ifndef PACKAGEGENERATOR_H
#define PACKAGEGENERATOR_H

#include "simlib.h"
#include "Package.h"  // Propojení s balíky

class PackageGenerator : public Event {
public:
    void Behavior() override;  // Metoda pro generování balíků
};

#endif  // PACKAGEGENERATOR_H
