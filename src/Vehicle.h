#ifndef VEHICLE_H
#define VEHICLE_H

#include "simlib.h"
#include "globals.h"
#include <vector>
#include <string>
#include <iostream>
#include "Package.h"

// Definice pro různé typy vozidel
enum VehicleType { COMBUSTION, ELECTRIC };

// Třída pro vozidla (auto nebo elektrické auto)
class Vehicle : public Process {
public:
    std::string id;                      // Identifikátor vozidla
    VehicleType vehicleType;             // Typ vozidla (spalovací nebo elektrické)
    double fuelConsumption;              // Spotřeba paliva (l/km pro spalovací, kWh/km pro elektrické)
    double batteryCapacity;              // Kapacita baterie pro elektrická vozidla (kWh)
    double batteryRemaining;             // Zbývající kapacita baterie pro elektrická vozidla (kWh)
    double maxCapacity;                  // Maximální kapacita balíků (např. 20 balíků)
    double currentLoad;                  // Aktuální počet naložených balíků
    double speed;                        // Rychlost vozidla (km/h)
    double distanceToDelivery;           // Vzdálenost k doručení
    double distanceToReturn;             // Vzdálenost zpět (do depa)
    double fuelRemaining;
    double fuelCapacity;

    std::vector<Package*> packages;      // Seznam balíků, které vozidlo vezme

    // Konstruktor
    Vehicle(std::string id, VehicleType type, double fuelConsumption, double batteryCapacity, 
            double maxCapacity, double speed, double fuelCapacity)
        : id(id), vehicleType(type), fuelConsumption(fuelConsumption), batteryCapacity(batteryCapacity),
          batteryRemaining(batteryCapacity), maxCapacity(maxCapacity), speed(speed),fuelRemaining(fuelCapacity) , currentLoad(0), fuelCapacity(fuelCapacity) {}

    // Chování vozidla (Behavior method)
    void Behavior() override;

    // Nabíjení baterie pro elektrická vozidla
    void ChargeBattery();
    void RefillFuel();

    // Kontrola, zda může vozidlo doručit balík (dostatečný dojezd pro e-auto)
    bool CanDeliver(double distance);

    // Načítání balíku do vozidla
    void LoadPackage(Package* p);

};

#endif  // VEHICLE_H
