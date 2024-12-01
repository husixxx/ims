#ifndef GLOBALS_H
#define GLOBALS_H

#include "simlib.h"

// Definice počtu facilities (nakládací místa)
#define NUM_LOADING_SLOTS 6


extern Queue loadQueue;                           // Sklad pro balíky čekající na nakládku                          // Fronta pro balíky čekající na kontrolu
extern Queue vehicleQueue;
extern Queue eVehicleQueue;
extern Facility controller;  // Facility pro kontrolu balíků
extern Stat fuelStat;
extern Stat co2Stat;
extern Stat distanceStat;
extern Stat packagesStat;
extern Stat energyStat;
extern Stat packagesChargeStat;
extern Stat packagesFuelStat;



#endif  // GLOBALS_H