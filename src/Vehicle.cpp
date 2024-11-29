#include "Vehicle.h"
#include <iostream>

Vehicle::Vehicle(int capacity) : maxCapacity(capacity), currentLoad(0) {}

void Vehicle::Behavior() {
    while (true) {
        // Vozidlo čeká na nakládku balíků
        if (currentLoad < maxCapacity) {
            std::cout << "Vozidlo čeká na balíky, aktuálně má " << currentLoad << " balíků.\n";
            Wait(1);  // Čekání na nakládku
            continue;
        }

        // Vozidlo je plné, začíná rozvoz
        std::cout << "Vozidlo je plné, začíná rozvoz balíků.\n";

        // Simulace cesty na místo určení
        double travelTime = Exponential(10);  // Čas potřebný pro rozvoz balíku
        Wait(travelTime);  // Čekání na dobu cesty

        std::cout << "Vozidlo doručilo balíky a vrací se pro nové.\n";

        // Po doručení balíků se vozidlo vrací a připraví se na další nakládku
        currentLoad = 0;  // Resetování kapacity vozidla
    }
}

void Vehicle::LoadPackage(Package* pkg) {
    currentLoad++;
    std::cout << "Balík " << pkg->id << " naložen do vozidla.\n";
}
