#ifndef GLOBALS_H
#define GLOBALS_H

#include "simlib.h"

// Definice počtu facilities (nakládací místa)
#define NUM_LOADING_SLOTS 6


extern Queue loadQueue;                           // Sklad pro balíky čekající na nakládku
extern Queue checkQueue;                             // Fronta pro balíky čekající na kontrolu
extern Queue vehicleQueue;
extern Queue eVehicleQueue;
extern Facility controller;  // Facility pro kontrolu balíků
struct SimulationStats {
    double totalFuelConsumed = 0.0; // Celková spotřeba benzínu (l)
    double totalCo2Emitted = 0.0;  // Celkové emise CO2 (kg)
    double totalDistanceTravelled = 0.0; // Celkově projeté kilometry
    int totalPackagesDelivered = 0; // Celkový počet doručených balíků
};
extern SimulationStats stats;


#endif  // GLOBALS_H