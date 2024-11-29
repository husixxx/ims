#ifndef VEHICLE_H
#define VEHICLE_H

#include "simlib.h"
#include "Package.h"  // Propojení s třídou Package
#include "globals.h"   // Propojení se sdílenými frontami a store

class Vehicle : public Process {
public:
    int maxCapacity;  // Maximální kapacita vozidla (počet balíků)
    int currentLoad;  // Aktuální počet naložených balíků

    Vehicle(int capacity);
    void Behavior() override;  // Hlavní metoda pro chování vozidla (rozvoz)
    void LoadPackage(Package* pkg);  // Funkce pro přidání balíku do vozidla
};

#endif  // VEHICLE_H
