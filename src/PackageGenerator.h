#ifndef PACKAGEGENERATOR_H
#define PACKAGEGENERATOR_H

#include "simlib.h"
#include "Package.h"  // Propojení s balíky
#include <cstdlib>  // Pro rand()
#include <ctime>  

class PackageGenerator : public Event {
public:
    void Behavior() override;  // Metoda pro generování balíků
private:
    int i = 0;  // Počítadlo balíků
};

#endif  // PACKAGEGENERATOR_H
