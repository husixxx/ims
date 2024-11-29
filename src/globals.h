#ifndef GLOBALS_H
#define GLOBALS_H

#include "simlib.h"

// Definice počtu facilities (nakládací místa)
#define NUM_LOADING_SLOTS 2

// Globální objekty (facility, store a fronty)
extern Facility loadingFacility[NUM_LOADING_SLOTS];  // Místa pro nakládku balíků
extern Queue loadQueue;                           // Sklad pro balíky čekající na nakládku
extern Queue checkQueue;                             // Fronta pro balíky čekající na kontrolu
extern Queue vehicleQueue;                           // Fronta pro vozidla čekající na nakládku

#endif  // GLOBALS_H