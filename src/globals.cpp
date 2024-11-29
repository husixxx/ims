#include "globals.h"

// Inicializace globálních objektů
Facility loadingFacility[NUM_LOADING_SLOTS];  // Pole pro facilities
Queue loadQueue;                           // Store pro čekající balíky
Queue checkQueue;                             // Fronta pro balíky čekající na kontrolu
Queue vehicleQueue;                           // Fronta pro vozidla čekající na nakládku
